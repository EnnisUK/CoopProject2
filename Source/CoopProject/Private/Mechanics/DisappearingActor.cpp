// Fill out your copyright notice in the Description page of Project Settings.


#include "Mechanics/DisappearingActor.h"

#include "Net/UnrealNetwork.h"


// Sets default values
ADisappearingActor::ADisappearingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	
	M_Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = M_Root;

	M_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	M_Mesh->SetIsReplicated(true);
	M_Mesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> Material(TEXT("/Game/Mats/M_HiddenActor"));
    if (Material.Object)
    {
	    M_Material = Material.Object;
    	M_Mesh->SetMaterial(0, M_Material);
    }
	M_HitBoxCollision = ECollisionEnabled::QueryAndPhysics;
	M_HitBox = CreateDefaultSubobject<UBoxComponent>("HitBox");
	M_HitBox->SetupAttachment(RootComponent);
	M_HitBox->SetCollisionEnabled(M_HitBoxCollision);
	

	

}

// Called when the game starts or when spawned
void ADisappearingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADisappearingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADisappearingActor::OnRep_IsHidden()
{
	M_Mesh->SetHiddenInGame(M_bIsHidden);
}

void ADisappearingActor::OnRep_SetCollision()
{
	M_HitBox->SetCollisionEnabled(M_HitBoxCollision);
}

void ADisappearingActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADisappearingActor, M_bIsHidden);
	DOREPLIFETIME(ADisappearingActor, M_HitBoxCollision);
}


void ADisappearingActor::ShowActor()
{
	if (HasAuthority())
	{
		ServerRPC_ShowActor();
	}
	
}

void ADisappearingActor::ServerRPC_HideActor_Implementation()
{
	M_LightsOverlapping++;
	M_LightsOverlapping = FMath::Clamp(M_LightsOverlapping, 0, 2);
	if (M_LightsOverlapping >= M_LightsNeeded && !M_bIsHidden)
	{
		M_bIsHidden = true;
		M_Mesh->SetHiddenInGame(M_bIsHidden);
		M_HitBoxCollision = ECollisionEnabled::NoCollision;
		M_HitBox->SetCollisionEnabled(M_HitBoxCollision);
		
	}
	
}

void ADisappearingActor::HideActor()
{
	if (HasAuthority())
	{
		ServerRPC_HideActor();
	}
	
}

void ADisappearingActor::ServerRPC_ShowActor_Implementation()
{
	M_LightsOverlapping--;
	M_LightsOverlapping = FMath::Clamp(M_LightsOverlapping, 0, 2);
	if (M_bIsHidden && M_LightsOverlapping < M_LightsNeeded)
	{
		M_bIsHidden = false;
		M_Mesh->SetHiddenInGame(M_bIsHidden);
		M_HitBoxCollision = ECollisionEnabled::QueryAndPhysics;
		M_HitBox->SetCollisionEnabled(M_HitBoxCollision);
	}
	
}

