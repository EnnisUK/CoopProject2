// Fill out your copyright notice in the Description page of Project Settings.


#include "Mechanics/LightButton.h"

#include "Net/UnrealNetwork.h"

// Sets default values
ALightButton::ALightButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	bReplicates = true;

	M_Root = CreateDefaultSubobject<USceneComponent>("RootComponent");
	RootComponent = M_Root;

	M_CrystalMesh = CreateDefaultSubobject<UStaticMeshComponent>("CrystalMesh");
	M_CrystalMesh->SetIsReplicated(true);
	M_CrystalMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CrystalMesh(TEXT("/Game/Assets/Crystal/Crystal"));

    if (CrystalMesh.Object)
    {
	    M_CrystalMesh->SetStaticMesh(CrystalMesh.Object);
    }

	M_StandMesh = CreateDefaultSubobject<UStaticMeshComponent>("StandMesh");
	M_StandMesh->SetIsReplicated(true);
	M_StandMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StandMesh(TEXT("/Game/Assets/Stand/OrientalGraveStone"));

	if (StandMesh.Object)
	{
		M_StandMesh->SetStaticMesh(StandMesh.Object);
	}
	

}

void ALightButton::ActivateCrystal()
{
	if (!M_bIsActive)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Purple, TEXT("Called from LightButton.CPP/ ActivateCrystal = true"));
		M_bIsActive = true;
		M_CrystalMesh->SetMaterial(0, M_CrystalOn);
		if (M_ActorsToActivate.Num() > 0)
		{
			for (AActor* TA : M_ActorsToActivate)
			{
				if (IGlobalFunctionsInterface* GlobalInterface = Cast<IGlobalFunctionsInterface>(TA))
				{
					GlobalInterface->ButtonActivateInteract(true);
				}
		
			}
		}
	}
	else
	{
		M_bIsActive = false;
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Purple, TEXT("Called from LightButton.CPP/ ActivateCrystal = false"));
		M_CrystalMesh->SetMaterial(0, M_CrystalOff);
		
		if (M_ActorsToActivate.Num() > 0)
		{
			for (AActor* TA : M_ActorsToActivate)
			{
				if (IGlobalFunctionsInterface* GlobalInterface = Cast<IGlobalFunctionsInterface>(TA))
				{
					GlobalInterface->ButtonActivateInteract(false);
				}
		
			}
		}
	}


	
	
}

// Called when the game starts or when spawned
void ALightButton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALightButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALightButton::Interact_Implementation()
{
}

void ALightButton::OnRep_bIsActive()
{
	if (M_bIsActive)
	{
		M_CrystalMesh->SetMaterial(0, M_CrystalOn);
	}
	else
	{
		M_CrystalMesh->SetMaterial(0, M_CrystalOff);
	}
}

void ALightButton::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALightButton, M_bIsActive);
}

