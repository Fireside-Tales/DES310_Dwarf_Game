// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/BaseThrowable.h"
#include <Kismet/KismetMathLibrary.h>

#include "Character/PlayerEntity.h"
#include "Camera/CameraComponent.h"
#include <Kismet/KismetSystemLibrary.h>
#include "Components/AudioComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABaseThrowable::ABaseThrowable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AudioComponent = CreateOptionalDefaultSubobject<UAudioComponent>(FName("Audio Component"));
	RootComponent = AudioComponent;

	PivotPoint = CreateOptionalDefaultSubobject<USceneComponent>(FName("Pivot Point"));
	PivotPoint->SetupAttachment(AudioComponent);

	LodgePoint = CreateOptionalDefaultSubobject<USceneComponent>(FName("Lodge Point"));
	LodgePoint->SetupAttachment(PivotPoint);

	Mesh = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(FName("Mesh"));
	Mesh->SetupAttachment(LodgePoint);

	ProjectileMovement = CreateOptionalDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	DamageComponent = CreateOptionalDefaultSubobject<UDamageComponent>(FName("Damage"));

	AxeThrowSpeed = 4000;
	MaxDistance = 30000;
	AxeReturnScale = 1.f;
	ReturnTilt = 60.f;
	ReturnSpinRate = 0.35f;
}

// Called when the game starts or when spawned
void ABaseThrowable::BeginPlay()
{
	Super::BeginPlay();
	if (ProjectileMovement)
	{
		ProjectileMovement->Deactivate();
		ProjectileMovement->ProjectileGravityScale = 0;
		ProjectileMovement->SetVelocityInLocalSpace(FVector());
	}
}

// Called every frame
void ABaseThrowable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseThrowable::OnOverLapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// do damage stuff here
}

void ABaseThrowable::InitialiseReturnVariables()
{
	DistanceFromChar = GetClampedAxeDistanceFromChar(PlayerRef->GetMesh());
	AdjustAxeReturnLocation();
	InitLoc = GetActorLocation();
	InitRot = GetActorRotation();
	CameraRot = PlayerRef->GetCamera()->GetComponentRotation();
	LodgePoint->SetRelativeRotation(FRotator::ZeroRotator);
}

void ABaseThrowable::InitialiseReturnTrace()
{
	AxeLocationLastTick = ReturnTargetLocations;
}

bool ABaseThrowable::LineTraceMethod(FHitResult& OutHit)
{
	FVector Start = GetActorLocation();
	FVector End = GetVelocity();

	End.Normalize(0.000001f);
	End *= ThrowTraceDis;
	End = GetActorLocation() + End;

	FCollisionQueryParams params;

	params.AddIgnoredActor(this);
	params.AddIgnoredActor(PlayerRef);

	return GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, params);
}

bool ABaseThrowable::InitSphereTrace(FHitResult& OutHit)
{
	FVector Start = ReturnTargetLocations;
	FVector End = AxeLocationLastTick;

	TArray<AActor*> ignoreActors;
	ignoreActors.Add(this);
	ignoreActors.Add(PlayerRef);

	return UKismetSystemLibrary::SphereTraceSingle(GetWorld(), Start, End, 5.0f, ETraceTypeQuery::TraceTypeQuery1, false, ignoreActors, EDrawDebugTrace::None, OutHit, true);
}

void ABaseThrowable::ThrowAxe()
{
	CameraLoc = PlayerRef->GetCamera()->GetComponentLocation();
	CameraRot = PlayerRef->GetCamera()->GetComponentRotation();
	ThrowDir = CameraRot.Vector();
	isThrown = true;
	SnapToStart();
	LaunchAxe();
}

void ABaseThrowable::RecallLaunched()
{
	Z_Adjustment = 10;
}

void ABaseThrowable::LaunchAxe()
{
	if (ProjectileMovement)
	{
		ProjectileMovement->Velocity = ThrowDir * AxeThrowSpeed;
		ProjectileMovement->Activate();
		AxeState = EAxeStates::Launched;
		ProjectileMovement->ProjectileGravityScale = 0.0f;
	}
}

void ABaseThrowable::Catch(USceneComponent* newParent)
{
	FAttachmentTransformRules attachRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true); // tells the axe how to attach back to the player. 
	AttachToComponent(newParent, attachRules, "HandSocket");
	isThrown = false;
	AxeState = EAxeStates::Idle;
}

void ABaseThrowable::HandleImpact(FVector Normal, FVector Location)
{
	ImpactLoc = Location;
	ImpactNormal = Normal;
	ProjectileMovement->Deactivate();
}

void ABaseThrowable::LodgeAxe()
{
	PivotPoint->SetRelativeRotation(FRotator());
	SetActorRotation(CameraRot);
	LodgePoint->SetRelativeRotation(FRotator(AdjustAxeImpactPitch(), 0, FMath::RandRange(-3.0, 8.0)));
	SetActorLocation(AdjustAxeImpactLocation());
	AxeState = EAxeStates::Lodged;
}

void ABaseThrowable::AdjustAxeReturnLocation()
{
	AxeLocationLastTick = ReturnTargetLocations;
	float Z = (((1 - (Z_Adjustment / 10)) * 30) + 20);
	SetActorLocation(UKismetMathLibrary::Add_VectorVector(GetActorLocation(), FVector(0, 0, Z)));
}
void ABaseThrowable::AxeLodgePull(float pull)
{
	LodgePoint->SetRelativeRotation(LodgePoint->GetRelativeRotation() + FRotator(pull * -40, 0, 0));
}

void ABaseThrowable::ReturnPosition(float rot1, float rot2, float vectorCurve, float speedCurve, USkeletalMeshComponent* skeleton)
{
	float newScalar = vectorCurve * (DistanceFromChar / AxeReturnScale);
	FVector socketLocation = skeleton->GetSocketLocation("HandSocket"); // gets the location of where the axe should be lodged into the model
	FRotator socketRotation = skeleton->GetSocketRotation("HandSocket");

	ReturnTargetLocations = UKismetMathLibrary::VLerp(InitLoc, PlayerRef->GetCamera()->GetRightVector() + socketLocation, speedCurve);
	FRotator newRot = FRotator(CameraRot.Pitch, CameraRot.Yaw, CameraRot.Roll + ReturnTilt);
	FRotator lerpRot = UKismetMathLibrary::RLerp(InitRot, newRot, rot1, true);
	FRotator finalRotation = UKismetMathLibrary::RLerp(lerpRot, socketRotation, rot2, true);
	SetActorLocationAndRotation(ReturnTargetLocations, finalRotation); // sets the actors location and final rotation 
}

void ABaseThrowable::ReturnSpin(float TimelineSpeed)
{
	float duration = 1 / TimelineSpeed;
	float timer = duration - 0.87f;

	ReturnSpins = UKismetMathLibrary::Round(duration / ReturnSpinRate);
	SpinLength = 1 / ((duration - 0.055f) / UKismetMathLibrary::Conv_IntToFloat(ReturnSpins));
	duration -= 0.87f;

	FTimerHandle timerHandle;
	GetWorld()->GetTimerManager().SetTimer(timerHandle, [&]()
		{
		}, duration, false);
}

void ABaseThrowable::ReturnSpinAfterTime(float newPitch)
{
	PivotPoint->SetRelativeRotation(FRotator(newPitch * 360, 0, 0));
}

float ABaseThrowable::GetClampedAxeDistanceFromChar(USkeletalMeshComponent* skeleton)
{
	FVector socketLoc = skeleton->GetSocketLocation("HandSocket");
	FVector finalVector = GetActorLocation() - socketLoc; // gets the final vector from the hand socket and the actors current position 
	return UKismetMathLibrary::FClamp(finalVector.Length(), 0, MaxDistance);
}

FVector ABaseThrowable::CalculateImpulseDirection()
{
	return FVector(); 	// Implementation here
}

FVector ABaseThrowable::AdjustAxeImpactLocation()
{
	FRotator tempRot = UKismetMathLibrary::MakeRotationFromAxes(ImpactNormal.ForwardVector, FVector(), FVector());
	float	pitch = tempRot.Pitch > 0 ? 10 * (1 - tempRot.Pitch / 90) : 10; // checks if the tempRotPitch is geater than 0, if so it will be a decimal value below 10 other wise it is set to 10

	Z_Adjustment = pitch; // makes the z adjustment the value of pitch
	ImpactLoc += FVector(0, 0, pitch); // assigns the impact loc to have the pithc value assigned to Z

	FVector finalLoc = ImpactLoc - (GetActorLocation() - LodgePoint->GetComponentLocation()); // gets the final location based on the subtraction of the lodge point location from the actors and then subtracts tat from the impact location

	return finalLoc;
}

void ABaseThrowable::SnapToStart()
{
	CameraLoc += (ThrowDir * 250);

	SetActorLocationAndRotation(PivotPoint->GetComponentLocation(), CameraRot, false, 0, ETeleportType::None);
}

float ABaseThrowable::AdjustAxeReturnTimelineSpeed()
{
	float finalValue = OptimalDis * AxeReturnSpeed;
	if (finalValue > 0)
		finalValue /= DistanceFromChar;
	return UKismetMathLibrary::FClamp(finalValue, 0.4f, 7.0f);
}

float ABaseThrowable::AdjustAxeImpactPitch()
{
	float InclineSurface = FMath::RandRange(-30, -55);
	float RegularRange = FMath::RandRange(-5, 25);
	FRotator rot = UKismetMathLibrary::MakeRotationFromAxes(ImpactNormal.ForwardVector, FVector(), FVector());
	return rot.Pitch = rot.Pitch > 0 ? RegularRange - rot.Pitch : InclineSurface - rot.Pitch;
}
