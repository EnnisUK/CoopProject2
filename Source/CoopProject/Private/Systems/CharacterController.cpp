// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/CharacterController.h"

#include "PlayerVoiceChatActor.h"
#include "AdvancedVoiceLibrary.h"
#include "OnlineSubsystem.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"

ACharacterController::ACharacterController()
{
}

void ACharacterController::BeginPlay()
{
	Super::BeginPlay();

	this->SetShowMouseCursor(false);
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);

	FTimerHandle CheckPingTimer;

	GetWorldTimerManager().SetTimer(CheckPingTimer, this, &ACharacterController::CheckPing, 20, true);

	CheckPing();
	
	
	
}

void ACharacterController::PushToTalk(bool TurnOnMic)
{
	if (TurnOnMic)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Mic On, called from CharacterCon"));
		UUniversalVoiceChat::VoiceChatStartSpeak(false, true, 0, false);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Mic Off, called from CharacterCon"));
		UUniversalVoiceChat::VoiceChatStopSpeak();
	}
	
	
}

void ACharacterController::CheckPing()
{
	M_PlayerState = Cast<AMainPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
	if (M_PlayerState)
	{
		if (M_PlayerState->GetCompressedPing() * 4 > M_HighPingThreshold) // Ping is compressed; it's ping / 4
		{
			M_ShowWifi.Broadcast();
		}
		else
		{
			M_HideWifi.Broadcast();
		}
			
	}
	

	

	
}


