// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainPlayerState.h"
#include "GameFramework/PlayerController.h"
#include "CharacterController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHUDOnShowWifi);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHUDOnHideWifi);

/**
 * 
 */
UCLASS()
class COOPPROJECT_API ACharacterController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(BlueprintAssignable, VisibleAnywhere)
	FHUDOnShowWifi M_ShowWifi;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere)
	FHUDOnHideWifi M_HideWifi;

	void CheckPing();

	UPROPERTY(EditAnywhere)
	float M_HighPingThreshold = 50;

	UPROPERTY(EditAnywhere)
	AMainPlayerState* M_PlayerState;
	
	
};
