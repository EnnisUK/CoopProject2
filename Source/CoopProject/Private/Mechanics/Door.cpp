// Fill out your copyright notice in the Description page of Project Settings.


#include "Mechanics/Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(true);

	M_RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	RootComponent = M_RootComponent;

	M_DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>("DoorMesh");
	M_DoorMesh->SetupAttachment(RootComponent);
	M_DoorMesh->SetIsReplicated(true);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CellMesh(TEXT("/Game/Assets/Cell/Meshes/Architecture/Dungeon/SM_Cell_Door"));
    if (CellMesh.Object)
    {
	    M_DoorMesh->SetStaticMesh(CellMesh.Object);
    }

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	M_StartRotation = GetActorRotation();
	M_TargetRot = GetActorRotation() + FRotator(0,90,0);
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::ButtonActivateInteract(bool Activate)
{
	
	if (Activate)
	{
		
		M_ActivatedButtons++;
	}
	else
	{
		M_ActivatedButtons--;
	}

	if (M_ActivatedButtons == M_NeededButtons)
	{
		M_ActivateDoor = true;
	}
	else
	{
		M_ActivateDoor = false;
	}
	GetWorldTimerManager().SetTimer(M_RotateDoor, this, &ADoor::ActivateDoor, 0.01, true);
	
}

void ADoor::ActivateDoor()
{
	
	if (M_ActivateDoor)
	{
		
		if (GetActorRotation() != M_TargetRot)
		{
			FRotator NewRot = FMath::RInterpTo(GetActorRotation(), M_TargetRot, GetWorld()->DeltaTimeSeconds, 0.5);
			SetActorRotation(NewRot);
		}
		else
		{
			GetWorldTimerManager().ClearTimer(M_RotateDoor);
		}
		
	}
	else
	{
		
		
		if (GetActorRotation() != M_TargetRot)
		{
			FRotator NewRot = FMath::RInterpTo(GetActorRotation(), M_StartRotation, GetWorld()->DeltaTimeSeconds, 0.5);
			SetActorRotation(NewRot);
		}
		else
		{
			GetWorldTimerManager().ClearTimer(M_RotateDoor);
		}
	}
}

