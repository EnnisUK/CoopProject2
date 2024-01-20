// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Systems/GlobalFunctionsInterface.h"
#include "WeightedMovableActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FResetActor);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActivateActor);

/**
 * 
 */
UCLASS()
class COOPPROJECT_API AWeightedMovableActor : public AStaticMeshActor, public IGlobalFunctionsInterface
{
	GENERATED_BODY()
public:
	AWeightedMovableActor();

	UPROPERTY(EditAnywhere, Category = "Stats",meta = (DisplayName ="WeightNeeded"))
	int M_WeightNeeded;

	UPROPERTY(BlueprintAssignable)
	FResetActor M_ResetActor;

	UPROPERTY(BlueprintAssignable)
	FActivateActor M_ActivateActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,meta = (DisplayName ="CurrentWeight"))
	int M_CurrentWeight;
	
};
