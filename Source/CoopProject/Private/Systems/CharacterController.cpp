// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/CharacterController.h"

#include "OnlineSubsystem.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

void ACharacterController::BeginPlay()
{
	Super::BeginPlay();

	this->SetShowMouseCursor(false);
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);

	FTimerHandle CheckPingTimer;

	GetWorldTimerManager().SetTimer(CheckPingTimer, this, &ACharacterController::CheckPing, 20, true);

	CheckPing();
	
}

void ACharacterController::CheckPing()
{
	M_PlayerState = Cast<AMainPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
	if (M_PlayerState)
	{
		GEngine->AddOnScreenDebugMessage(-1,2,FColor::Yellow, TEXT("Player State Valid"));
		if (M_PlayerState->GetCompressedPing() * 4 > M_HighPingThreshold) // Ping is compressed; it's ping / 4
		{
			M_ShowWifi.Broadcast();
			GEngine->AddOnScreenDebugMessage(-1,2,FColor::Yellow, TEXT("Show Wifi Broadcast"));
		}
		else
		{
			M_HideWifi.Broadcast();
			GEngine->AddOnScreenDebugMessage(-1,2,FColor::Yellow, TEXT("Hide Wifi Broadcast"));
		}
			
	}
	

	

	
}


