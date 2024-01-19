// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/CoopGamemode.h"
#include "UObject/ConstructorHelpers.h"
#include "Systems/CharacterController.h"



ACoopGameMode::ACoopGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Characters/BP_MainCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<ACharacterController> CharacterControllerClass(TEXT("/Game/Blueprints/Systems/BP_CharacterController"));
	if (CharacterControllerClass.Class != NULL)
	{
		PlayerControllerClass = CharacterControllerClass.Class;
	}

	static ConstructorHelpers::FClassFinder<AMainPlayerState> MainPlayerStateClass(TEXT("/Game/Blueprints/Systems/BP_MainPlayerState"));
	if (MainPlayerStateClass.Class != NULL)
	{
		PlayerStateClass = MainPlayerStateClass.Class;
	}
	
}


