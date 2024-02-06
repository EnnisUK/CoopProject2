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
	

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

