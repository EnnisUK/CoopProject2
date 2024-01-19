// Fill out your copyright notice in the Description page of Project Settings.


#include "Misc/WinArea.h"

#include "BaseClasses/PlayerBaseClass.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AWinArea::AWinArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	
	M_WinArea = CreateDefaultSubobject<UBoxComponent>("Win Zone");
	M_WinArea->SetupAttachment(RootComponent);
	M_WinArea->SetIsReplicated(true);
	M_WinArea->SetCollisionProfileName("OverlapAllDynamic");
	M_WinArea->SetBoxExtent(FVector(100,100,10));

	SetRootComponent(M_WinArea);

	M_bWinCondition = false;
}

// Called when the game starts or when spawned
void AWinArea::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AWinArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		if (!M_bWinCondition)
		{
			
		
			TArray<AActor*> OverlappedActor;
			M_WinArea->GetOverlappingActors(OverlappedActor, APlayerBaseClass::StaticClass());

			M_bWinCondition = (OverlappedActor.Num() == 2);
			if (M_bWinCondition)
			{
			MulticastRPCWin();
			}
		}
	}

}

void AWinArea::MulticastRPCWin_Implementation()
{
		M_OnWinCondition.Broadcast();
	
}




