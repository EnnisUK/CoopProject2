// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable/CollectableKey.h"

#include "BaseClasses/PlayerBaseClass.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ACollectableKey::ACollectableKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	bReplicates = true;
	SetReplicateMovement(true);

	M_RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(M_RootComponent);

	M_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	M_Mesh->SetupAttachment(RootComponent);
	M_Mesh->SetIsReplicated(true);
	M_Mesh->SetCollisionProfileName(FName("OverlapAllDynamic"));

	M_SphereCollision = CreateDefaultSubobject<USphereComponent>("HitBox");
	M_SphereCollision->SetupAttachment(RootComponent);
	M_SphereCollision->SetIsReplicated(true);
	M_SphereCollision->SetCollisionProfileName(FName("OverlapAllDynamic"));
	M_SphereCollision->SetSphereRadius(100);

	M_CollectedAudio = CreateDefaultSubobject<UAudioComponent>("CollectedAudio");
	M_CollectedAudio->SetupAttachment(RootComponent);
	M_CollectedAudio->SetAutoActivate(false);
	
	M_RotateSpeed = 100;
}

void ACollectableKey::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACollectableKey, M_bIsCollected);
}

void ACollectableKey::CheckOverlap()
{
	if (HasAuthority())
	{
		
		
		TArray<AActor*> OverlappingActor;
		M_SphereCollision->GetOverlappingActors(OverlappingActor, APlayerBaseClass::StaticClass());

		if (!OverlappingActor.IsEmpty())
		{
			if (!M_bIsCollected)
			{
				M_bIsCollected = true;
				OnRep_CollectedKey();

			
			}
		}
	}
}


// Called when the game starts or when spawned
void ACollectableKey::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle CheckOverlap;

	
	
	GetWorldTimerManager().SetTimer(CheckOverlap, this, &ACollectableKey::CheckOverlap, 0.1, true);
	
}

// Called every frame
void ACollectableKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		M_Mesh->AddRelativeRotation(FRotator(0,M_RotateSpeed * DeltaTime ,0));
	}
}

void ACollectableKey::OnRep_CollectedKey()
{
	if (HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1,2,FColor::Red, TEXT("Called Rep Function From Server"));
	
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1,2,FColor::Red, TEXT("Called Rep Function From Client"));
	}

	M_Mesh->SetVisibility(!M_bIsCollected);

	if (M_CollectedAudio)
	{
		M_CollectedAudio->Play();
	}
	
}

