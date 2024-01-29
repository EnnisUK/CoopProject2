// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/AFGI_MainInstance.h"

#include "BaseClasses/PlayerBaseClass.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

void UAFGI_MainInstance::Init()
{
	Super::Init();

	LoadGame();

	M_UserSettings = UGameUserSettings::GetGameUserSettings();
	
}

void UAFGI_MainInstance::SaveGame()
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
		M_SaveGame->M_ColourMode = M_ColourMode;
		M_SaveGame->M_Gamma = M_Gamma;
		M_SaveGame->M_FOV = M_FOV;
		M_SaveGame->M_FPSIndex = M_FPSIndex;
		M_SaveGame->M_MouseSens = M_MouseSens;
		M_SaveGame->M_bUseInvertedMouseY = M_bUseInvertedMouseY;
		M_SaveGame->M_bUseInvertedMouseX = M_bUseInvertedMouseX;
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

void UAFGI_MainInstance::LoadGame()
{
	APlayerBaseClass* Player = Cast<APlayerBaseClass>(GetFirstLocalPlayerController());
	
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
	M_ColourMode = M_SaveGame->M_ColourMode;
	M_Gamma = M_SaveGame->M_Gamma;
	M_FOV = M_SaveGame->M_FOV;
	M_FPSIndex = M_SaveGame->M_FPSIndex;
	M_MouseSens = M_SaveGame->M_MouseSens;
	M_bUseInvertedMouseY = M_SaveGame->M_bUseInvertedMouseY;
	M_bUseInvertedMouseX = M_SaveGame->M_bUseInvertedMouseX;
	if (Player)
	{
		M_PlayerLocation = M_SaveGame->M_PlayerLocation;
	}
	

	GEngine->AddOnScreenDebugMessage(-1,2,FColor::Green, TEXT("Loaded Game"));

}

APlayerController* UAFGI_MainInstance::GetLocalController(APlayerController* LocalController)
{
	LocalController = GetFirstLocalPlayerController(GetWorld());
	return LocalController;
}

void UAFGI_MainInstance::SetDefaultSettings()
{
	M_WindowMode = M_UserSettings->GetLastConfirmedFullscreenMode();

	M_FrameRate = M_UserSettings->GetFrameRateLimit();

	M_bUseVsync = M_UserSettings->IsVSyncEnabled();

	M_Resolution = M_UserSettings->GetLastConfirmedScreenResolution();

	M_ShadingIndex = M_UserSettings->GetShadingQuality();

	M_ViewDistance = M_UserSettings->GetViewDistanceQuality();

	M_AntiAliasing = M_UserSettings->GetAntiAliasingQuality();

	M_PostProcessing = M_UserSettings->GetPostProcessingQuality();

	M_ShadowIndex = M_UserSettings->GetShadowQuality();

	M_TextureIndex = M_UserSettings->GetTextureQuality();

	M_GlobalIlluminationQuality = M_UserSettings->GetGlobalIlluminationQuality();

	M_EffectsIndex = M_UserSettings->GetVisualEffectQuality();

	M_FoliageIndex = M_UserSettings->GetFoliageQuality();
	
	UWidgetBlueprintLibrary::SetColorVisionDeficiencyType(M_ColourMode, M_ColourBlindSens, true, false);

	if (M_ColourCorrectionSlider)
	{
		M_ColourCorrectionSlider->SetValue(M_ColourBlindSens);
	}

	if (M_BrightnessSlider)
	{
		M_BrightnessSlider->SetValue(M_Gamma);
	}
	
	if (M_FOVSlider)
	{
		M_FOVSlider->SetValue(M_FOV);
	}

	if (M_MouseSensSlider)
	{
		M_MouseSensSlider->SetValue(M_MouseSens);
	}

	M_UserSettings->ApplySettings(true);

	ShowFPS();
	SetScreenRes();
	
}

void UAFGI_MainInstance::ShowFPS()
{
	if (M_FPSWidget)
	{
		if (M_bShowFPS)
		{
			if (M_FPSWidget->IsVisible() == false)
			{
				M_FPSWidget->SetVisibility(ESlateVisibility::Visible);
			}
		}
		else
		{
			if (M_FPSWidget->IsVisible() == false)
			{
				M_FPSWidget->SetVisibility(ESlateVisibility::Collapsed);
			}
		}
	}
}

void UAFGI_MainInstance::SetScreenRes()
{
	if (M_Resolution.X == 1280)
	{
		M_ResolutionIndex = 0;
		M_Resolution.X = 1280;
		M_Resolution.Y = 720;
		UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(),TEXT("r.setres 1280x720"));
	}
	else if (M_Resolution.X == 1600)
	{
		M_ResolutionIndex = 1;
		M_Resolution.X = 1600;
		M_Resolution.Y = 900;
		UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(),TEXT("r.setres 1600x900"));
	}
	else if (M_Resolution.X == 1920)
	{
		M_ResolutionIndex = 2;
		M_Resolution.X = 1920;
		M_Resolution.Y = 1080;
		UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(),TEXT("r.setres 1920x1080"));
	}
	else if (M_Resolution.X == 2560)
	{
		M_ResolutionIndex = 3;
		M_Resolution.X = 2560;
		M_Resolution.Y = 1440;
		UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(),TEXT("r.setres 2560x1440"));
	}
	else if (M_Resolution.X == 3840)
	{
		M_ResolutionIndex = 4;
		M_Resolution.X = 3840;
		M_Resolution.Y = 2160;
		UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(),TEXT("r.setres 3840x2160"));
	}

	M_UserSettings->ApplyResolutionSettings(true);
	
}

void UAFGI_MainInstance::ApplySettings()
{
	M_UserSettings->SetFullscreenMode(M_WindowMode);
	M_UserSettings->SetFrameRateLimit(M_FrameRate);
	M_UserSettings->SetVSyncEnabled(M_bUseVsync);
	M_UserSettings->SetTextureQuality(M_TextureIndex);
	M_UserSettings->SetFoliageQuality(M_FoliageIndex);
	M_UserSettings->SetShadingQuality(M_ShadowIndex);
	M_UserSettings->SetShadingQuality(M_ShadingIndex);
	M_UserSettings->SetPostProcessingQuality(M_PostProcessing);
	M_UserSettings->SetAntiAliasingQuality(M_AntiAliasing);
	M_UserSettings->SetViewDistanceQuality(M_ViewDistance);
	M_UserSettings->SetGlobalIlluminationQuality(M_GlobalIlluminationQuality);
	M_UserSettings->SetVisualEffectQuality(M_EffectsIndex);

	M_UserSettings->ApplySettings(false);

	SaveGame();
}

void UAFGI_MainInstance::ChangeScreenIndex(int NewIndex)
{
	switch (NewIndex)
	{
	case 0:
		M_Resolution.X = 1280;
		M_Resolution.Y = 720;
		UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(),TEXT("r.setres 1280x720"));
		break;
	case 1:
		M_Resolution.X = 1600;
		M_Resolution.Y = 900;
		UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(),TEXT("r.setres 1600x900"));
		break;
	case 2:
		M_Resolution.X = 1920;
		M_Resolution.Y = 1080;
		UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(),TEXT("r.setres 1920x1080"));
		break;
	case 3:
		M_Resolution.X = 2560;
		M_Resolution.Y = 1440;
		UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(),TEXT("r.setres 2560x1440"));
		break;
	case 4:
		M_Resolution.X = 3840;
		M_Resolution.Y = 2160;
		UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(),TEXT("r.setres 3840x2160"));
		break;
		

		default:break;
	}

	M_UserSettings->ApplyResolutionSettings(true);
	M_UserSettings->ConfirmVideoMode();
}

void UAFGI_MainInstance::ChangeFPS(int NewIndex)
{
	
	switch (NewIndex)
	{
	case 0:
		M_FrameRate = 0.0;
		
		break;
	case 1:
		M_FrameRate = 30;
		break;
	case 2:
		M_FrameRate = 60;
		break;
	case 3:
		M_FrameRate = 144;
		break;

		default:break;
		
	}

	FString Msg = FString::Printf(TEXT("Current FPS is: %f"), M_FrameRate);
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, Msg);
}




