// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/BaseThrowable.h"
#include <Kismet/KismetMathLibrary.h>

#include "Character/PlayerEntity.h"
#include "Camera/CameraComponent.h"
#include <Kismet/KismetSystemLibrary.h>
#include "Components/AudioComponent.h"
#include "Components/SkeletalMeshComponent.h"
// Sets default values
ABaseThrowable::ABaseThrowable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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



}

// Called when the game starts or when spawned
void ABaseThrowable::BeginPlay()
{
	Super::BeginPlay();

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

	//AdjustAxeReturn()

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

}

void ABaseThrowable::RecallLaunched()
{
}

void ABaseThrowable::LaunchAxe()
{
}

void ABaseThrowable::Catch(USceneComponent* newParent)
{
}

void ABaseThrowable::HandleImpact(FVector Normal, FVector Location)
{
}

void ABaseThrowable::LodgeAxe()
{
}

void ABaseThrowable::AdjustAxeReturnLocation()
{
}
void ABaseThrowable::AxeLodgePull(float pull)
{
	// Implementation here
}

void ABaseThrowable::ReturnPosition(float rot1, float rot2, float vectorCurve, float speedCurve, USkeletalMeshComponent* skeleton)
{
	// Implementation here
}

void ABaseThrowable::ReturnSpin(float TimelineSpeed)
{
	// Implementation here
}

void ABaseThrowable::ReturnSpinAfterTime(float newPitch)
{
	// Implementation here
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
	// Implementation here
	return FVector();
}

void ABaseThrowable::SnapToStart()
{
	// Implementation here
}

float ABaseThrowable::AdjustAxeReturnTimelineSpeed()
{
	return 0.0f;
	// Implementation here
}


