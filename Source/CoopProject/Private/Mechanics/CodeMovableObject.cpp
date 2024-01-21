// Fill out your copyright notice in the Description page of Project Settings.


#include "Mechanics/CodeMovableObject.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Mechanics/Lantern.h"
#include "Net/UnrealNetwork.h"

void ACodeMovableObject::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACodeMovableObject, M_CorrectCode);
	DOREPLIFETIME(ACodeMovableObject, M_RandomNumbersString);
	DOREPLIFETIME(ACodeMovableObject, M_InputCode);
	DOREPLIFETIME(ACodeMovableObject, M_Colour1);
	DOREPLIFETIME(ACodeMovableObject, M_Colour2);
	DOREPLIFETIME(ACodeMovableObject, M_Colour3);
	DOREPLIFETIME(ACodeMovableObject, M_Colour4);
	DOREPLIFETIME(ACodeMovableObject, M_Colour5);
	DOREPLIFETIME(ACodeMovableObject, M_Colour6);
	DOREPLIFETIME(ACodeMovableObject, M_Colour7);
	DOREPLIFETIME(ACodeMovableObject, M_Colour8);
	
}

ACodeMovableObject::ACodeMovableObject()
{
	
}

void ACodeMovableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACodeMovableObject::OnRep_ChangeColour()
{
	
}

void ACodeMovableObject::OnRep_UpdateInputCode()
{
}

void ACodeMovableObject::ResetLamps_Implementation()
{
	TArray<AActor*> OutActors;
	 UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALantern::StaticClass(), OutActors);

	for (AActor* Actor : OutActors)
	{
		ALantern* Lantern = Cast<ALantern>(Actor);
		if (Lantern)
		{
			Lantern->ResetLampsLights();
		}
		
		
	
	}
	M_InputCode = "";
	M_ResetPuzzle.Broadcast();
}
