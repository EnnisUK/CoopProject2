// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "TriggerActor.generated.h"

/**
 * 
 */
UCLASS()
class COOPPROJECT_API ATriggerActor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	ATriggerActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Weight"))
	int M_Weight;
	
};
