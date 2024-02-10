// Fill out your copyright notice in the Description page of Project Settings.


#include "Mechanics/WeightPlate.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
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

	M_Transporter = CreateDefaultSubobject<UTransporterComponent>("Transporter");
	M_Transporter->SetIsReplicated(true);
	M_Transporter->M_MoveTime = 0.25f;

	M_TriggerShape = CreateDefaultSubobject<UStaticMeshComponent>("TriggerShape");
	M_TriggerShape->SetupAttachment(RootComponent);
	M_TriggerShape->SetIsReplicated(true);

}

// Called when the game starts or when spawned
void AWeightPlate::BeginPlay()
{
	Super::BeginPlay();

	const FVector Point2 = GetActorLocation() + FVector(0,0, -20);
	M_Transporter->SetPoints(GetActorLocation(), Point2);

	M_TriggerShape->SetVisibility(false);
	M_TriggerShape->SetCollisionProfileName(FName("OverlapAll"));
	
}

void AWeightPlate::Print(FString Message)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Orange, Message);
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
				M_WeightedActor = Cast<ATriggerActor>(TriggerActor);
				break;
			}
		
		}
		if (TriggerActor)
		{
			if (!bTrigger)
			{
				bTrigger = true;
				GEngine->AddOnScreenDebugMessage(-1,2,FColor::Red, TEXT("Activated"));
				M_OnActivated.Broadcast();
				if (M_ActorToTrigger)
				{
					M_ActorToTrigger->M_CurrentWeight +=  M_WeightedActor->M_Weight;
					M_ActorToTrigger->M_CurrentWeight = UKismetMathLibrary::ClampInt64(M_ActorToTrigger->M_CurrentWeight, 0, 5000);
					if (M_ActorToTrigger->M_CurrentWeight >= M_ActorToTrigger->M_WeightNeeded)
					{
						GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Purple, TEXT("Passed Weight Check"));
						M_ActorToTrigger->M_ActivateActor.Broadcast();
					}
				}
				
			}
		}
		else
		{
			if (bTrigger)
			{
				bTrigger = false;
				M_ActorToTrigger->M_CurrentWeight -= M_WeightedActor->M_Weight;
				M_ActorToTrigger->M_CurrentWeight = UKismetMathLibrary::ClampInt64(M_ActorToTrigger->M_CurrentWeight, 0, 5000);
				M_ActorToTrigger->M_ResetActor.Broadcast();
				M_OnDeactivated.Broadcast();
			}
		}
		
	}
}





