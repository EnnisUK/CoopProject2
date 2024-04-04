// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Rendering/RenderingCommon.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ColourMode"))
	EColorVisionDeficiency M_ColourMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Field Of View"))
	float M_FOV;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "FPS Index"))
	int M_FPSIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Brightness"))
	float M_Gamma;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Player Location"))
	FVector M_PlayerLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Mouse Sens"))
	float M_MouseSens;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Resolution"))
	FIntPoint M_Resolution;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "MicDevice"))
	FString M_SelctedMic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "InvertedSens?"))
	float M_InvertedSensX;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "InvertedSens?"))
	float M_InvertedSensY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "MicVolume"))
	float M_MicVolume;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "AmountOfPlayers"))
	int32 M_AmountOfPlayers;
	
};
