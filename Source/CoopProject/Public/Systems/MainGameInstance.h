// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Rendering/RenderingCommon.h"
#include "MainGameInstance.generated.h"

class UMainSaveGame;
class APlayerBaseClass;

UCLASS()
class COOPPROJECT_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	
	UMainGameInstance();
	
	virtual void Init() override;

	//Save Functions && Variables
	UFUNCTION(BlueprintCallable)
	void SaveGame();
	
	UFUNCTION(BlueprintCallable)
	void LoadGame();

	UPROPERTY(EditAnywhere, meta = (DisplayName = "SlotName"))
	FString M_SlotName = "Slot1";

	UMainSaveGame* M_SaveGame;

	// Settings Functions






	//Settings Variables

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
