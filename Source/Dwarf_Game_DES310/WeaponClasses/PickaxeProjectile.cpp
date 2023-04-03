// Fill out your copyright notice in the Description page of Project Settings.


#include "PickaxeProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Dwarf_Game_DES310/PlayerClasses/Base_Player.h"
#include <Kismet/KismetMathLibrary.h>


// Sets default values
APickaxeProjectile::APickaxeProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PickMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName(TEXT("Pick Movement")));


	m_AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	m_AudioComponent->bAutoActivate = false;
	m_AudioComponent->SetupAttachment(RootComponent);
	m_AudioComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	mf_AxeThrowSpeed = 2000.f;
	mf_MaxDistance = 30000.f;
	mf_AxeReturnScale = 1.f;
	mf_ReturnTilt = 60.f;
	mf_ReturnSpinRate = 0.35f;

}

// Called when the game starts or when spawned
void APickaxeProjectile::BeginPlay()
{
	Super::BeginPlay();
	if (PickMovement)
	{
		PickMovement->Deactivate();
		PickMovement->ProjectileGravityScale = 0;
		PickMovement->SetVelocityInLocalSpace(FVector());
	}
}

// Called every frame
void APickaxeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickaxeProjectile::SnapToStart()
{
	mv_CameraLoc += (mv_ThrowDir * 250); // snaps the axe to the centre of the screen

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Camera %f %f %f"), mr_CameraRot.Pitch, mr_CameraRot.Yaw, mr_CameraRot.Roll));
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Pivot %f %f %f"), m_PivotPoint->GetRelativeLocation().X, m_PivotPoint->GetRelativeLocation().Y, m_PivotPoint->GetRelativeLocation().Z));

	//this->SetActorRotation(m_PivotPoint->GetRelativeRotation(), ETeleportType::None);
	//this->SetActorLocationAndRotation()
	//SetActorRotation(mr_CameraRot); 
	this->SetActorLocationAndRotation(m_PivotPoint->GetComponentLocation(), mr_CameraRot, false, 0, ETeleportType::None);
}

FVector APickaxeProjectile::AdjustAxeImpactLocation()
{

	FVector finalVector;

	FRotator tempRot = UKismetMathLibrary::MakeRotationFromAxes(mv_ImpactNormal.ForwardVector, FVector(), FVector());

	float pitch = tempRot.Pitch;

	if (pitch > 0)  // checks if the pitch is greater than 0
	{
		pitch = 90 - pitch;  // if so it sets the pitch to be 90 - pitch
	}
	else
	{
		pitch = 90; // otherwise it is 90 
	}
	pitch /= 90.f; // divides the pitch by 90
	pitch *= 10.f; // multiplies it by 10

	mf_Z_Adjustment = pitch;// sets the z_Adjustment to be the new pitch value

	mv_ImpactLoc += FVector(0, 0, pitch); // adds the pitch to the impact location 

	finalVector = GetActorLocation() - m_LodgePoint->GetComponentTransform().GetLocation();  // subtracts the lodgepoints world location from the actors location

	finalVector = mv_ImpactLoc + finalVector; // adds the result of the finalvector to the impact normal 

	return finalVector; // returns the final result
}



void APickaxeProjectile::AdjustAxeReturnLocation()
{
	mv_AxeLocationLastTick = mv_ReturnTargetLocations;

	float ZAdj = mf_Z_Adjustment;
	ZAdj /= 10.f;
	ZAdj = 1 - ZAdj;
	ZAdj *= 30.f;
	ZAdj += 20.f;

	FVector Location = GetActorLocation();  // gets the actors current location

	FVector Z = FVector(0, 0, ZAdj);  // creates the adjustment for the z axis

	FVector finalLocation = UKismetMathLibrary::Add_VectorVector(Location, Z);

	SetActorLocation(finalLocation); // sets the actors location based on the offset in the z axis
}

void APickaxeProjectile::AxeLodgePull(float pull)
{
	FRotator lodgeRot;

	lodgeRot.Pitch = m_LodgePoint->GetRelativeRotation().Pitch + (pull * -40);
	lodgeRot.Roll = m_LodgePoint->GetRelativeRotation().Roll;
	lodgeRot.Yaw = m_LodgePoint->GetRelativeRotation().Yaw;

	m_LodgePoint->SetRelativeRotation(lodgeRot);
}

void APickaxeProjectile::ReturnPosition(float rot1, float rot2, float vectorCurve, float speedCurve, USkeletalMeshComponent* skeleton)
{
	float newScalar = mf_DistanceFromChar / mf_AxeReturnScale;
	newScalar = vectorCurve * newScalar;

	FVector targetLoc = playerRef->camera->GetRightVector(); // gets the right vector of the camera thta is viewing it

	FVector socketLocation = skeleton->GetSocketLocation("HandSocket"); // gets the location of where the axe should be lodged into the model
	FRotator socketRotation = skeleton->GetSocketRotation("HandSocket");

	targetLoc += socketLocation; // adds the sockets location to the target location

	mv_ReturnTargetLocations = UKismetMathLibrary::VLerp(mv_InitLoc, targetLoc, speedCurve); // sets the return target to be the lerp between the initial target and the speed curve

	FRotator newRotation = FRotator(mr_CameraRot.Pitch, mr_CameraRot.Yaw, mr_CameraRot.Roll + mf_ReturnTilt); // gets the cameras rotation with a offset in the roll for the return tilt

	FRotator lerpRot = UKismetMathLibrary::RLerp(mr_InitRot, newRotation, rot1, true);
	FRotator finalRotation = UKismetMathLibrary::RLerp(lerpRot, socketRotation, rot2, true);


	SetActorLocationAndRotation(mv_ReturnTargetLocations, finalRotation); // sets the actors location and final rotation 
}

void APickaxeProjectile::ReturnSpin(float TimelineSpeed)
{
	float duration;
	float timer;
	duration = 1 / TimelineSpeed;

	mi_ReturnSpins = UKismetMathLibrary::Round(duration / mf_ReturnSpinRate); // this sets how many times the axe should spin on return

	//used for calculating the return length 
	mf_SpinLength = duration - 0.055f;
	mf_SpinLength /= UKismetMathLibrary::Conv_IntToFloat(mi_ReturnSpins);
	mf_SpinLength = 1 / mf_SpinLength;

	
	timer = duration - 0.87f;
	duration -= 0.87f;

	FLatentActionInfo actionInfo;


	FTimerHandle timerHandle;

	GetWorld()->GetTimerManager().SetTimer(timerHandle, [&]()
		{
			// insert audio here
		}, duration, false);

}

void APickaxeProjectile::ReturnSpinAfterTime(float newPitch)
{
	m_PivotPoint->SetRelativeRotation(FRotator(newPitch * 360.0f, 0.0f, 0.0f));
}

float APickaxeProjectile::AdjustAxeImpactPitch()
{
	float InclineSurface = FMath::RandRange(-30, -55);
	float RegularRange = FMath::RandRange(-5, 25);

	FRotator rot = UKismetMathLibrary::MakeRotationFromAxes(mv_ImpactNormal.ForwardVector, FVector(), FVector());
	if (rot.Pitch > 0)
	{
		return RegularRange - rot.Pitch;
	}
	else
	{
		return InclineSurface - rot.Pitch;
	}
	return 0.0f;
}

float APickaxeProjectile::GetClampedAxeDistanceFromChar(USkeletalMeshComponent* skeleton)
{
	FVector socketLoc = skeleton->GetSocketLocation("HandSocket"); // gets the location of the hand socket

	FVector finalVector = GetActorLocation() - socketLoc; // gets the final vector from the hand socket and the actors current position 

	return UKismetMathLibrary::FClamp(finalVector.Length(), 0, mf_MaxDistance);
}

FVector APickaxeProjectile::CalculateImpulseDirection()
{
	FVector vel = GetVelocity();
	vel.Normalize(0.0001);

	return vel;
}

float APickaxeProjectile::AdjustAxeReturnTimelineSpeed()
{
	float finalValue;

	finalValue = mf_OptimalDis * mf_AxeReturnSpeed;

	if (mf_DistanceFromChar > 0)
		finalValue /= mf_DistanceFromChar;

	return UKismetMathLibrary::FClamp(finalValue, 0.4f, 7.0f);
}

void APickaxeProjectile::InitVariables(UProjectileMovementComponent* projectileMovement, USceneComponent* pivotPoint, USceneComponent* lodgePoint, UCameraComponent* camera)
{
	m_PivotPoint = pivotPoint;
	m_LodgePoint = lodgePoint;
	m_Camera = camera;

}


void APickaxeProjectile::InitialiseReturnVariables()
{
	mf_DistanceFromChar = GetClampedAxeDistanceFromChar(playerRef->GetMesh());

	AdjustAxeReturnLocation();

	mv_InitLoc = GetActorLocation();
	mr_InitRot = GetActorRotation();

	mr_CameraRot = playerRef->camera->GetComponentRotation();

	m_LodgePoint->SetRelativeRotation(FRotator::ZeroRotator);
}

void APickaxeProjectile::InitialiseReturnTrace()
{
	mv_AxeLocationLastTick = mv_ReturnTargetLocations;
}

bool APickaxeProjectile::LineTraceMethod(FHitResult& OutHit)
{
	FVector start = GetActorLocation();
	FVector end = GetVelocity();

	end.Normalize(0.0001f);
	end *= mf_ThrowTraceDis;
	end = GetActorLocation() + end;

	FCollisionQueryParams parameters;



	return GetWorld()->LineTraceSingleByChannel(OutHit, start, end, ECC_Visibility, parameters);
}

bool APickaxeProjectile::InitSphereTrace(FHitResult& OutHit)
{
	FVector start = mv_ReturnTargetLocations;
	FVector end = mv_AxeLocationLastTick;

	TArray<AActor*> ignoreActors;

	ignoreActors.Add(this); 
	ignoreActors.Add(playerRef); 

	return UKismetSystemLibrary::SphereTraceSingle(GetWorld(), start, end, 25.0f, ETraceTypeQuery::TraceTypeQuery1, false, ignoreActors, EDrawDebugTrace::None, OutHit, true);
}

void APickaxeProjectile::ThrowAxe()
{
	mr_CameraRot = m_Camera->GetComponentRotation();
	mv_CameraLoc = m_Camera->GetComponentLocation();
	mv_ThrowDir = m_Camera->GetForwardVector();
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("throw %f %f %f"), mv_ThrowDir.X, mv_ThrowDir.Y, mv_ThrowDir.Z));

	mb_Thrown = true;


	SnapToStart();
	LaunchAxe();

}

void APickaxeProjectile::RecallLaunched()
{
	mf_Z_Adjustment = 10.f;
}

void APickaxeProjectile::LaunchAxe()
{
	if (PickMovement)
	{
		PickMovement->Velocity = mv_ThrowDir * mf_AxeThrowSpeed; // calculates the movement speed
		PickMovement->Activate(); // activates the movement component

		AxeState = AxeStates::Launched; // sets the axe state to launched

		PickMovement->ProjectileGravityScale = 0.f; // disables the gravity of the projectile	
	}
}

void APickaxeProjectile::Catch(USceneComponent* newParent)
{
	FAttachmentTransformRules attachRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true); // tells the axe how to attach back to the player. 
	AttachToComponent(newParent, attachRules, "HandSocket"); // this attaches the weapon to the player on the handSocket

	mb_Thrown = false;
	AxeState = AxeStates::Idle;
}

void APickaxeProjectile::HandleImpact(FVector ImpactNormal, FVector ImpactLocation)
{
	mv_ImpactLoc = ImpactLocation;
	mv_ImpactNormal = ImpactNormal;

	PickMovement->Deactivate(); // stops the movement of the pickaxe
}

void APickaxeProjectile::LodgeAxe()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("LDGE")));
	m_PivotPoint->SetRelativeRotation(FRotator(0, 0, 0));
	SetActorRotation(mr_CameraRot);

	float newRotation = AdjustAxeImpactPitch(); // calculates a new axe angle so the handle is not lodged
	m_LodgePoint->SetRelativeRotation(FRotator(newRotation, 0, FMath::RandRange(-3.0, 8.0))); // sets the lodge points angle

	FVector newLocation = AdjustAxeImpactLocation();
	SetActorLocation(newLocation);

	AxeState = AxeStates::Lodged;

}
