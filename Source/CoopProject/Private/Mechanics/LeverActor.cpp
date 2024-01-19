// Fill out your copyright notice in the Description page of Project Settings.


#include "Mechanics/LeverActor.h"

#include "BaseClasses/PlayerBaseClass.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ALeverActor::ALeverActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(true);

	M_RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(M_RootComponent);

	M_SphereComponent = CreateDefaultSubobject<USphereComponent>("HitBox");
	M_SphereComponent->SetupAttachment(RootComponent);
	M_SphereComponent->SetIsReplicated(true);
	M_SphereComponent->SetCollisionProfileName(FName("OverlapAllDynamic"));
	M_SphereComponent->SetSphereRadius(100);
	
	
	M_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	M_Mesh->SetupAttachment(RootComponent);
	M_Mesh->SetIsReplicated(true);
	M_Mesh->SetCollisionProfileName(FName("OverlapAllDynamic"));

}

// Called when the game starts or when spawned
void ALeverActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALeverActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALeverActor, M_bActivatedLever);
}

// Called every frame
void ALeverActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		
		
		TArray<AActor*> OverlappingActor;
		M_SphereComponent->GetOverlappingActors(OverlappingActor, APlayerBaseClass::StaticClass());

		if (!OverlappingActor.IsEmpty())
		{
			if (!M_bActivatedLever)
			{
				M_bActivatedLever = true;
				OnRep_ActivatedLever();
				M_ActivatedLever.Broadcast();
			
			}
		}
	}

}

void ALeverActor::OnRep_ActivatedLever()
{
	if (HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1,2,FColor::Red, TEXT("Called Rep Function From Server"));
	
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1,2,FColor::Red, TEXT("Called Rep Function From Client"));
	}

	
}

