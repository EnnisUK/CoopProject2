// Fill out your copyright notice in the Description page of Project Settings.


#include "Mechanics/WeightPlate.h"

#include "Mechanics/TriggerActor.h"
#include "Systems/GlobalFunctionsInterface.h"

// Sets default values
AWeightPlate::AWeightPlate()
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

	M_TriggerShape = CreateDefaultSubobject<UStaticMeshComponent>("TriggerShape");
	M_TriggerShape->SetupAttachment(RootComponent);
	M_TriggerShape->SetIsReplicated(true);

}

// Called when the game starts or when spawned
void AWeightPlate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeightPlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		
	
		TArray<AActor*> OverlappingActors;
		AActor* TriggerActor = nullptr;
		M_TriggerShape->GetOverlappingActors(OverlappingActors);

		for (int ActorIdx = 0; ActorIdx < OverlappingActors.Num(); ActorIdx++)
		{
			AActor* A = OverlappingActors[ActorIdx];
			if (A->ActorHasTag("WeightActor"))
			{
				TriggerActor = A;
				
				break;
			}
		
		}
		if (TriggerActor)
		{
			ATriggerActor* WeightedActor = Cast<ATriggerActor>(TriggerActor);

			M_CurrentWeight +=  WeightedActor->M_Weight;

			if (M_CurrentWeight >= M_ActorToTrigger->M_WeightNeeded)
			{
				bool bTrigger = false;
				if (M_ActorToTrigger->Implements<UGlobalFunctionsInterface>() && !bTrigger)
				{
					bTrigger = true;
					IGlobalFunctionsInterface::Execute_WeightTrigger(M_ActorToTrigger);
				}
				
			}
		}
	}

}

void AWeightPlate::WeightTrigger_Implementation()
{
}

