// Fill out your copyright notice in the Description page of Project Settings.


#include "PickaxeProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Dwarf_Game_DES310/PlayerClasses/Base_Player.h"

// Sets default values
APickaxeProjectile::APickaxeProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PickMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName(TEXT("Pick Movement")));


}

// Called when the game starts or when spawned
void APickaxeProjectile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APickaxeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickaxeProjectile::SnapToStart()
{
	mv_CameraLoc += mv_ThrowDir * 250; // snaps the axe to the centre of the screen

	FVector newLocation = mv_CameraLoc - m_PivotPoint->GetRelativeLocation();  // gets the new location for the axe
	this->SetActorLocationAndRotation(newLocation, mr_CameraRot, false, 0, ETeleportType::None);
}

FVector APickaxeProjectile::AdjustAxeImpactLocation()
{
	return FVector();
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

	SetActorLocation(Location + Z); // sets the actors location based on the offset in the z axis
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

	mv_ReturnTargetLocations = FMath::Lerp(mv_InitLoc, targetLoc, speedCurve); // sets the return target to be the lerp between the initial target and the speed curve

	FRotator newRotation = FRotator(mr_CameraRot.Pitch, mr_CameraRot.Yaw, mr_CameraRot.Roll + mf_ReturnTilt); // gets the cameras rotation with a offset in the roll for the return tilt

	FRotator lerpRot = FMath::Lerp(mr_InitRot, newRotation, rot1);
	FRotator finalRotation = FMath::Lerp(lerpRot, socketRotation, rot2); 

	SetActorLocationAndRotation(mv_ReturnTargetLocations, finalRotation); // sets the actors location and final rotation 
}

void APickaxeProjectile::ReturnSpin(float TimelineSpeed)
{
}

void APickaxeProjectile::ReturnSpineAfterTime(float newPitch)
{
}

float APickaxeProjectile::AdjustAxeImpactPitch()
{
	return 0.0f;
}

float APickaxeProjectile::GetClampedAxeDistanceFromChar(USkeletalMeshComponent* skeleton)
{
	return 0.0f;
}

FVector APickaxeProjectile::CalculateImpulseDirection()
{
	return FVector();
}

float APickaxeProjectile::AdjustAxeReturnTimelineSpeed(float OptimalDistance, float AxeReturnSpeed)
{
	return 0.0f;
}

void APickaxeProjectile::ThrowAxe()
{
	mr_CameraRot = playerRef->camera->GetComponentRotation();
	mv_CameraLoc = playerRef->camera->GetComponentLocation();
	mv_ThrowDir = playerRef->camera->GetForwardVector();

	mb_Thrown = true;
}

void APickaxeProjectile::RecallLaunched()
{
	mf_Z_Adjustment = 10.f;
}

void APickaxeProjectile::LaunchAxe()
{
	PickMovement->Velocity = mv_ThrowDir * mf_AxeThrowSpeed; // calculates the movement speed
	PickMovement->Activate(); // activates the movement component

	AxeState = AxeStates::Launched; // sets the axe state to launched

	PickMovement->ProjectileGravityScale = 0.f; // disables the gravity of the projectile
}

void APickaxeProjectile::Catch(USceneComponent* newParent)
{

	FAttachmentTransformRules attachRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true); // tells the axe how to attach back to the player. 
	AttachToComponent(newParent, attachRules, "HandSocket"); // this attaches the weapon to the player on the handSocket

	mb_Thrown = false;

	AxeState = AxeStates::Idle;
}

void APickaxeProjectile::HandleImpact(FVector ImpactNormal, FVector ImpactLocation)
{
	mv_ImapctLoc = ImpactLocation;
	m_ImpactNormal = ImpactNormal;

	PickMovement->Deactivate(); // stops the movement of the pickaxe
}

void APickaxeProjectile::LodgeAxe()
{
	m_PivotPoint->SetRelativeRotation(FRotator(0, 0, 0));
	SetActorRotation(mr_CameraRot);

	float newRotation = AdjustAxeImpactPitch(); // calculates a new axe angle so the handle is not lodged
	m_LodgePoint->SetRelativeRotation(FRotator(newRotation, 0, FMath::RandRange(-3.0, 8.0))); // sets the lodge points angle

	FVector newLocation = AdjustAxeImpactLocation();
	SetActorLocation(newLocation);

	AxeState = AxeStates::Lodged;

}
