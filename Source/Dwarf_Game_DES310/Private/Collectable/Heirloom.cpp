// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable/Heirloom.h"
#include "Character/PlayerEntity.h"

// Sets default values
AHeirloom::AHeirloom()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HeirloomPivot = CreateOptionalDefaultSubobject<USceneComponent>(TEXT("Heirloom Pivot"));
	HeirloomPivot->SetupAttachment(GetMesh());

	GetMesh()->OnComponentBeginOverlap.AddDynamic(this, &AHeirloom::OnOverlapBegin); 
}

// Called when the game starts or when spawned
void AHeirloom::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AHeirloom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHeirloom::SnapToPlayer(APlayerEntity* player)
{
	if (player)
	{
		FAttachmentTransformRules heirloomAttachRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);
		HeirloomPivot->AttachToComponent(player->GetMesh(), heirloomAttachRules, "Heirloom Socket");//Attaches the heirloom on the player
		PlayerRef = player;
	}
}

void AHeirloom::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerEntity* player = Cast<APlayerEntity>(OtherActor);
	if (player && PlayerRef)
	{
		SnapToPlayer(player);
	}
}

