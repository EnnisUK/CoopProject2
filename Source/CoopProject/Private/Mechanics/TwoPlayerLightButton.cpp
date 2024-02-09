// Fill out your copyright notice in the Description page of Project Settings.


#include "Mechanics/TwoPlayerLightButton.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ATwoPlayerLightButton::ATwoPlayerLightButton()
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

void ATwoPlayerLightButton::ActivateCrystal()
{
	if (!M_bIsActive)
	{
		
	
	M_NeededLightPulses++;
	M_CrystalMesh->SetMaterial(0, M_CrystalHalfOn);
	M_CrystalMaterial = M_CrystalHalfOn;
	FTimerHandle ResetTimerHandle;
	GetWorldTimerManager().SetTimer(ResetTimerHandle, this, &ATwoPlayerLightButton::ResetCrystal, 15, false);
	
		if (M_NeededLightPulses == 2)
		{
			M_bIsActive = true;
			GetWorldTimerManager().ClearTimer(ResetTimerHandle);
			M_CrystalMesh->SetMaterial(0, M_CrystalOn);
			M_CrystalMaterial = M_CrystalOn;
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
	}
}

void ATwoPlayerLightButton::ResetCrystal()
{
	if (!M_bIsActive)
	{
		M_NeededLightPulses = 0;
		M_CrystalMesh->SetMaterial(0, M_CrystalOff);
		M_CrystalMaterial = M_CrystalOff;
	}

	
}

// Called when the game starts or when spawned
void ATwoPlayerLightButton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATwoPlayerLightButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ATwoPlayerLightButton::Interact_Implementation()
{
}

void ATwoPlayerLightButton::OnRep_UpdateMaterial()
{
	M_CrystalMesh->SetMaterial(0, M_CrystalMaterial);
}


void ATwoPlayerLightButton::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATwoPlayerLightButton, M_CrystalMaterial);
}

