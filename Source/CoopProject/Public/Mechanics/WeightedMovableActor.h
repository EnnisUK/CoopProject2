// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Systems/GlobalFunctionsInterface.h"
#include "WeightedMovableActor.generated.h"

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
	
};
