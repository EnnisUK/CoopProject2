// Fill out your copyright notice in the Description page of Project Settings.


#include "Mechanics/WeightPlate.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
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

	M_TriggerBox = CreateDefaultSubobject<UBoxComponent>("TriggerBox");
	M_TriggerBox->SetupAttachment(RootComponent);
	M_TriggerBox->SetIsReplicated(true);

}

// Called when the game starts or when spawned
void AWeightPlate::BeginPlay()
{
	Super::BeginPlay();

	M_TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AWeightPlate::OnEndOverlap);
	
}

// Called every frame
void AWeightPlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		
	
		TArray<AActor*> OverlappingActors;
		AActor* TriggerActor = nullptr;
		M_TriggerBox->GetOverlappingActors(OverlappingActors);

		for (int ActorIdx = 0; ActorIdx < OverlappingActors.Num(); ActorIdx++)
		{
			AActor* A = OverlappingActors[ActorIdx];
			if (A->ActorHasTag("WeightActor"))
			{
				TriggerActor = A;
				break;
			}
			
		
		}
		
		if (TriggerActor && bTrigger == false)
		{
			bTrigger = true;
			ATriggerActor* WeightedActor = Cast<ATriggerActor>(TriggerActor);

			M_ActorToTrigger->M_CurrentWeight +=  WeightedActor->M_Weight;
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Black,UKismetStringLibrary::Conv_IntToString(WeightedActor->M_Weight));
			
			M_ActorToTrigger->M_CurrentWeight = UKismetMathLibrary::ClampInt64(M_ActorToTrigger->M_CurrentWeight, 0, 5000);

			if (M_ActorToTrigger->M_CurrentWeight >= M_ActorToTrigger->M_WeightNeeded)
			{
				
				if (M_ActorToTrigger->Implements<UGlobalFunctionsInterface>())
				{
						
						M_ActorToTrigger->M_ActivateActor.Broadcast();
			
				}
				
			}
		}
	}

}

void AWeightPlate::OnEndOverlap(UPrimitiveComponent* OtherComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (OtherActor->GetClass()->IsChildOf(ATriggerActor::StaticClass()))
	{
		ATriggerActor* TriggerActor = Cast<ATriggerActor>(OtherActor);
		M_ActorToTrigger->M_CurrentWeight -= TriggerActor->M_Weight;
		M_ActorToTrigger->M_CurrentWeight = UKismetMathLibrary::ClampInt64(M_ActorToTrigger->M_CurrentWeight, 0, 5000);
		M_ActorToTrigger->M_ResetActor.Broadcast();
		bTrigger = false;
	}
}

void AWeightPlate::WeightTrigger_Implementation()
{
	
}

