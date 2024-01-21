// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "CodeSheet.generated.h"



/**
 * 
 */
UCLASS()
class COOPPROJECT_API ACodeSheet : public AStaticMeshActor
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	
	void ChangeColour();

	//Server Functions

	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_ChangeColour();
	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	UMaterialInstance* M_Instace1;

	UPROPERTY(ReplicatedUsing=OnRep_ChangeInstance, EditAnywhere, BlueprintReadOnly)
	UMaterialInstance* M_Instace2;

	UPROPERTY(ReplicatedUsing=OnRep_ChangeInstance, EditAnywhere, BlueprintReadOnly)
	UMaterialInstance* M_Instace3;

	UFUNCTION()
	void OnRep_ChangeInstance();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
};
