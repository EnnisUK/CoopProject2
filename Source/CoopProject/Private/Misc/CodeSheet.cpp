// Fill out your copyright notice in the Description page of Project Settings.


#include "Misc/CodeSheet.h"

#include "Kismet/KismetMaterialLibrary.h"
#include "Net/UnrealNetwork.h"


void ACodeSheet::BeginPlay()
{
	Super::BeginPlay();
	
}




void ACodeSheet::OnRep_ChangeInstance()
{
	GEngine->AddOnScreenDebugMessage(-1,2,FColor::Yellow, TEXT("Called OnRep"));
}

void ACodeSheet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACodeSheet, M_ParentMaterial);
	
	
}
