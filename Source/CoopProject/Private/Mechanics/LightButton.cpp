// Fill out your copyright notice in the Description page of Project Settings.


#include "Mechanics/LightButton.h"

// Sets default values
ALightButton::ALightButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Super::BeginPlay();

	bReplicates = true;

	M_Root = CreateDefaultSubobject<USceneComponent>("RootComponent");
	RootComponent = M_Root;

	M_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	M_Mesh->SetIsReplicated(true);
	M_Mesh->SetupAttachment(RootComponent);
	

}

void ALightButton::ActivateCrystal()
{
	if (!M_bIsActive)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Orange, TEXT("Activated"));
		M_bIsActive = true;
		if (M_ActorsToActivate.Num() > 0)
		{
			for (AActor* TA : M_ActorsToActivate)
			{
				if (TA->Implements<UGlobalFunctionsInterface>())
				{
					IGlobalFunctionsInterface::Execute_ButtonActivateInteract(TA, M_bIsActive);
				}
		
			}
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Orange, TEXT("Activated"));
		M_bIsActive = false;

		if (M_ActorsToActivate.Num() > 0)
		{
			for (AActor* TA : M_ActorsToActivate)
			{
				if (TA->Implements<UGlobalFunctionsInterface>())
				{
					IGlobalFunctionsInterface::Execute_ButtonActivateInteract(TA, M_bIsActive);
				}
		
			}
		}
	}


	
	
}

// Called when the game starts or when spawned
void ALightButton::BeginPlay()
{
	
	
}

// Called every frame
void ALightButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALightButton::Interact_Implementation()
{
}

