// Fill out your copyright notice in the Description page of Project Settings.


#include "Mechanics/PressurePlate.h"

#include "Kismet/KismetSystemLibrary.h"

// Sets default values
APressurePlate::APressurePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	M_bActivated = false;

	bReplicates = true;
	SetReplicateMovement(true);

	M_Transporter = CreateDefaultSubobject<UTransporterComponent>("Transporter");
	M_Transporter->SetIsReplicated(true);
	M_Transporter->M_MoveTime = 0.25f;
	
	M_RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(M_RootComponent);

	M_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	M_Mesh->SetupAttachment(RootComponent);
	M_Mesh->SetIsReplicated(true);

	/*const auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/Stylized_Egypt/Meshes/building/SM_building_part_08"));

	if (MeshAsset.Succeeded())
	{
		M_Mesh->SetStaticMesh(MeshAsset.Object);
		M_Mesh->SetRelativeScale3D(FVector(4,4, 0.5));
		M_Mesh->SetRelativeLocation(FVector(0, 0, 7.2));
	}

	M_TriggerShape = CreateDefaultSubobject<UStaticMeshComponent>("TriggerShape");
	M_TriggerShape->SetupAttachment(RootComponent);
	M_TriggerShape->SetIsReplicated(true);

	const auto TriggerMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/StarterContent/Shapes/Shape_Cylinder"));

    if (TriggerMeshAsset.Succeeded())
    {
	    M_TriggerShape->SetStaticMesh(TriggerMeshAsset.Object);
    	M_TriggerShape->SetRelativeScale3D(FVector(3.3,3.3, 0.2));
    	M_TriggerShape->SetRelativeLocation(FVector(0, 0, 10));
    }*/


	
}



// Called when the game starts or when spawned
void APressurePlate::BeginPlay()
{
	Super::BeginPlay();

	M_TriggerShape->SetVisibility(false);
	M_TriggerShape->SetCollisionProfileName(FName("OverlapAll"));

	const FVector Point2 = GetActorLocation() + FVector(0,0, -10);
	M_Transporter->SetPoints(GetActorLocation(), Point2);

	GetWorldTimerManager().SetTimer(M_OverlapActorsTimer, this, &APressurePlate::CheckOverlappingActors, 0.1, true);
}

// Called every frame
void APressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APressurePlate::CheckOverlappingActors()
{
	if (HasAuthority())
	{
		
	
		TArray<AActor*> OverlappingActors;
		AActor* TriggerActor = nullptr;
		M_TriggerShape->GetOverlappingActors(OverlappingActors);

		for (int ActorIdx = 0; ActorIdx < OverlappingActors.Num(); ActorIdx++)
		{
			AActor* A = OverlappingActors[ActorIdx];
			if (A->ActorHasTag("TriggerActor"))
			{
				TriggerActor = A;
				break;
			}
		
		}
		if (TriggerActor)
		{
			if (!M_bActivated)
			{
				M_bActivated = true;
				GEngine->AddOnScreenDebugMessage(-1,2,FColor::Red, TEXT("Activated"));
				M_OnActivated.Broadcast();
			}
		}
		else
		{
			if (M_bActivated)
			{
				M_bActivated = false;
				GEngine->AddOnScreenDebugMessage(-1,2,FColor::Red, TEXT("Deactivated"));
				M_OnDeactivated.Broadcast();
			}
		}
	}
}

