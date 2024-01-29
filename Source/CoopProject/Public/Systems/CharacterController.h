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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"), meta = (DisplayName = "Player Mapping Context"))
	class UInputMappingContext* M_PlayerMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"), meta = (DisplayName = "Move Action"))
	class UInputAction* M_MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"), meta = (DisplayName = "Look Action"))
	class UInputAction* M_LookAction;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"), meta = (DisplayName = "Jump Action"))
	class UInputAction* M_JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"), meta = (DisplayName = "Save Action"))
	class UInputAction* M_SaveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"), meta = (DisplayName = "Load Action"))
	class UInputAction* M_LoadAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"), meta = (DisplayName = "Sprint Action"))
	class UInputAction* M_SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"), meta = (DisplayName = "Grab Action"))
	class UInputAction* M_GrabAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"), meta = (DisplayName = "Pause Action"))
	class UInputAction* M_PauseAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"), meta = (DisplayName = "Ping Action"))
	class UInputAction* M_PingAction;

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

	
	void InputActions();
	
};
