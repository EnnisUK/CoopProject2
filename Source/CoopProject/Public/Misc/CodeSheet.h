// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Mechanics/CodeMovableObject.h"
#include "Systems/GlobalFunctionsInterface.h"
#include "CodeSheet.generated.h"



/**
 * 
 */
UCLASS()
class COOPPROJECT_API ACodeSheet : public AStaticMeshActor, public IGlobalFunctionsInterface
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	
	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, ReplicatedUsing=OnRep_ChangeInstance)
	UMaterial* M_ParentMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ACodeMovableObject* M_TA;

	UFUNCTION()
	void OnRep_ChangeInstance();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void Interact_Implementation();
	
};
