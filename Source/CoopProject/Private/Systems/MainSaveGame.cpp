// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/MainSaveGame.h"

UMainSaveGame::UMainSaveGame()
{

	M_ColourMode = EColorVisionDeficiency::NormalVision;
	
	M_MasterVolume = 0.5;

	M_SFXVolume = 0.5;

	M_MusicVolume = 0.5;

	M_bShowFPS = false;
	
	M_ControllerSens = 10;

	M_ColourBlindSens = 0.0;
	
	M_Gamma = 2.2;

	M_PlayerLocation = FVector::Zero();

	M_FOV = 90;

	M_FPSIndex = 0;

	M_MouseSens = 1;
	
	M_Resolution = M_Resolution.X = 1920, M_Resolution.Y = 1080;

	M_MicVolume = 1;

	M_InvertedSensX = 1;

	M_InvertedSensY = 1;
}
