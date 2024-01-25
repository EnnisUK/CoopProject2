// Fill out your copyright notice in the Description page of Project Settings.


#include "Mechanics/HiddenSymbols.h"

// Sets default values
AHiddenSymbols::AHiddenSymbols()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	bAlwaysRelevant = true;
	SetActorHiddenInGame(true);

}

// Called when the game starts or when spawned
void AHiddenSymbols::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHiddenSymbols::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHiddenSymbols::SetSymbolVisibilty(bool bVisible)
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Blue, TEXT("SetVis"));
	SetActorHiddenInGame(bVisible);
}

