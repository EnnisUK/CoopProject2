// Fill out your copyright notice in the Description page of Project Settings.


#include "Misc/CodeSheet.h"

#include "Kismet/KismetMaterialLibrary.h"
#include "Net/UnrealNetwork.h"


void ACodeSheet::BeginPlay()
{
	Super::BeginPlay();

	
	FTimerHandle Timer;

	if (HasAuthority())
	{
		GetWorldTimerManager().SetTimer(Timer, this, &ACodeSheet::NetMulticast_ChangeColour, 3);
	}
	
	
}

void ACodeSheet::ChangeColour()
{
	M_Instace2 = M_Instace3;
	
}

void ACodeSheet::NetMulticast_ChangeColour_Implementation()
{
	GetStaticMeshComponent()->SetMaterial(0, M_Instace2);
}

void ACodeSheet::OnRep_ChangeInstance()
{
	GEngine->AddOnScreenDebugMessage(-1,2,FColor::Yellow, TEXT("Called OnRep"));
}

void ACodeSheet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACodeSheet, M_Instace1);
	DOREPLIFETIME(ACodeSheet, M_Instace2);
	DOREPLIFETIME(ACodeSheet, M_Instace3);
	
}
