// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdvancedFriendsGameInstance.h"
#include "Components/Slider.h"
#include "Rendering/RenderingCommon.h"
#include "Systems/MainSaveGame.h"
#include "GameFramework/GameUserSettings.h"
#include "Rendering/RenderingCommon.h"

#include "GenericPlatform/GenericWindow.h"
#include "AFGI_MainInstance.generated.h"

/**
 * 
 */
UCLASS()
class COOPPROJECT_API UAFGI_MainInstance : public UAdvancedFriendsGameInstance
{
	GENERATED_BODY()

public:	
    	
    	virtual void Init() override;
    
    	//Save Functions && Variables
    	UFUNCTION(BlueprintCallable)
    	void SaveGame();
    	
    	UFUNCTION(BlueprintCallable)
    	void LoadGame();
    
    	UPROPERTY(EditAnywhere, meta = (DisplayName = "SlotName"))
    	FString M_SlotName = "Slot1";
    
    	UMainSaveGame* M_SaveGame;



	//Settings Variables

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "MouseSens"))
	float M_MouseSens;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "MasterVolume"))
	float M_MasterVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Field Of View"))
	float M_FOV;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "SFXVolume"))
	float M_SFXVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "MusicVolume"))
	float M_MusicVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ShowFPS?"))
	bool M_bShowFPS;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "UseVsync?"))
	bool M_bUseVsync;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "InvertedY?"))
    bool M_bUseInvertedMouseY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "InvertedX?"))
	bool M_bUseInvertedMouseX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ControllerSens"))
	float M_ControllerSens;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ColourBlindSens"))
	float M_ColourBlindSens;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ColourMode"))
	EColorVisionDeficiency M_ColourMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Brightness"))
	float M_Gamma;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "FrameRate"))
	float M_FrameRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Window Mode"))
	TEnumAsByte<EWindowMode::Type> M_WindowMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Player Location"))
	FVector M_PlayerLocation;

	UPROPERTY( BlueprintReadOnly, meta = (DisplayName = "Local Controller"))
	APlayerController* M_LocalController;

	UFUNCTION(BlueprintPure)
	APlayerController* GetLocalController(APlayerController* LocalController);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Resolution"))
	FIntPoint M_Resolution;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Resolution Index"))
	int M_ResolutionIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Shading Index"))
	int M_ShadingIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "View Distance Index"))
	int M_ViewDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Anti-Aliasing Index"))
	int M_AntiAliasing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Post Processing Index"))
	int M_PostProcessing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "FPS Index"))
	int M_FPSIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Shadow Quality Index"))
	int M_ShadowIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Texture Quality Index"))
	int M_TextureIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Global Illumination Quality Index"))
	int M_GlobalIlluminationQuality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Effects Index"))
	int M_EffectsIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Foliage Quality Index"))
	int M_FoliageIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Colour Correction Slider"))
	USlider* M_ColourCorrectionSlider;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Brightness Slider"))
	USlider* M_BrightnessSlider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "FOV Slider"))
	USlider* M_FOVSlider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Mouse Sens Slider"))
	USlider* M_MouseSensSlider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (DisplayName = "PlayerUserSettings"))
	UGameUserSettings* M_UserSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "FPSWidgetRef"))
	UUserWidget* M_FPSWidget;

	FString M_ResolutionX;

	FString M_ResolutionY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "MicDevice"))
	FString M_SelctedMic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "MicVolume"))
	float M_MicVolume;

	UPROPERTY(BlueprintReadOnly)
	FString M_Message;
	
	
	
	// Settings Functions

	UFUNCTION(BlueprintCallable)
	void SetDefaultSettings();

	void ShowFPS();

	void SetScreenRes();

	UFUNCTION(BlueprintCallable)
	void ApplySettings();

	UFUNCTION(BlueprintCallable)
	void ChangeScreenIndex(int NewIndex);
	
	UFUNCTION(BlueprintCallable)
	void ChangeFPS(int NewIndex);

	
	
};
