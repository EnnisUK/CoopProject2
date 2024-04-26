// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/MainGameInstance.h"

#include "BaseClasses/PlayerBaseClass.h"
#include "Kismet/GameplayStatics.h"
#include "Systems/MainSaveGame.h"


UMainGameInstance::UMainGameInstance()
{
	
}

void UMainGameInstance::Init()
{
	Super::Init();

	LoadGame();

	
}

void UMainGameInstance::SaveGame()
{

	APlayerBaseClass* Player = Cast<APlayerBaseClass>(GetFirstLocalPlayerController());
	if (Player)
	{
		M_PlayerLocation = Player->GetActorLocation();
	}
	
	if (UGameplayStatics::DoesSaveGameExist(M_SlotName, 0))
	{
		M_SaveGame = Cast<UMainSaveGame>(UGameplayStatics::LoadGameFromSlot(M_SlotName, 0));
		check(M_SaveGame);

		M_SaveGame->M_MasterVolume = M_MasterVolume;
		M_SaveGame->M_SFXVolume = M_SFXVolume;
		M_SaveGame->M_MusicVolume = M_MusicVolume;
		M_SaveGame->M_bShowFPS = M_bShowFPS;
		M_SaveGame->M_ControllerSens = M_ControllerSens;
		M_SaveGame->M_ColourBlindSens = M_ColourBlindSens;
		
		//M_SaveGame->M_ColourMode = M_ColourMode;
		M_SaveGame->M_Gamma = M_Gamma;
		if (Player)
		{
			M_SaveGame->M_PlayerLocation = M_PlayerLocation;
		}
		

		if (UGameplayStatics::SaveGameToSlot(M_SaveGame, M_SlotName, 0))
		{
			GEngine->AddOnScreenDebugMessage(-1,2,FColor::Green, TEXT("Saved Game"));
		}
		
		
	}
}

void UMainGameInstance::LoadGame()
{
	
	if	(UGameplayStatics::DoesSaveGameExist(M_SlotName, 0))
	{
		M_SaveGame = Cast<UMainSaveGame>(UGameplayStatics::LoadGameFromSlot(M_SlotName, 0));
		check(M_SaveGame);
		
	}
	else
	{
		M_SaveGame = Cast<UMainSaveGame> (UGameplayStatics::CreateSaveGameObject(UMainSaveGame::StaticClass()));
		UGameplayStatics::SaveGameToSlot(M_SaveGame, M_SlotName, 0);
		check(M_SaveGame);
	}

	M_MasterVolume = M_SaveGame->M_MasterVolume;
	M_SFXVolume = M_SaveGame->M_SFXVolume;
	M_MusicVolume = M_SaveGame->M_MusicVolume;
	M_bShowFPS = M_SaveGame->M_bShowFPS;
	M_ControllerSens = M_SaveGame->M_ControllerSens;
	M_ColourBlindSens = M_SaveGame->M_ColourBlindSens;
	//M_ColourMode = M_SaveGame->M_ColourMode;
	M_Gamma = M_SaveGame->M_Gamma;
	M_PlayerLocation = M_SaveGame->M_PlayerLocation;

	GEngine->AddOnScreenDebugMessage(-1,2,FColor::Green, TEXT("Loaded Game"));

}


