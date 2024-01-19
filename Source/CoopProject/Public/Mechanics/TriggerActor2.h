// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "TriggerActor2.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHudOnShow);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHudOnHide);

/**
 * 
 */
UCLASS()
class COOPPROJECT_API ATriggerActor2 : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	ATriggerActor2();

	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FHudOnShow M_ShowHud;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FHudOnShow M_HideHud;
};
