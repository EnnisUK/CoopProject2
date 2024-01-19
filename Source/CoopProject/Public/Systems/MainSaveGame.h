// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MainSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class COOPPROJECT_API UMainSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	//Variables

	UMainSaveGame();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "MasterVolume"))
	float M_MasterVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "SFXVolume"))
	float M_SFXVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "MusicVolume"))
	float M_MusicVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ShowFPS?"))
	bool M_bShowFPS;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ControllerSens"))
	float M_ControllerSens;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ColourBlindSens"))
	float M_ColourBlindSens;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ColourMode"))
	//EColorVisionDeficiency M_ColourMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Brightness"))
	float M_Gamma;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Player Location"))
	FVector M_PlayerLocation;
	
};
