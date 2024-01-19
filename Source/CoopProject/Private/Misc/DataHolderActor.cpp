// Fill out your copyright notice in the Description page of Project Settings.


#include "Misc/DataHolderActor.h"

// Sets default values
ADataHolderActor::ADataHolderActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADataHolderActor::BeginPlay()
{
	Super::BeginPlay();

	
FirstPlayerController();
	
}

// Called every frame
void ADataHolderActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADataHolderActor::FirstPlayerController()
{
	FTimerHandle CheckValidTimer;
	if (!FirstController)
	{
		FirstController = GetGameInstance()->GetFirstLocalPlayerController(GetWorld());
		GetWorldTimerManager().SetTimer(CheckValidTimer, this, &ADataHolderActor::FirstPlayerController, 0.1, true);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(CheckValidTimer);
	}
	
}



