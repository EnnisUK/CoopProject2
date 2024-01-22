// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "CodeMovableObject.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FResetPuzzle);

/**
 * 
 */
UCLASS()
class COOPPROJECT_API ACodeMovableObject : public AStaticMeshActor
{
	GENERATED_BODY()


public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	ACodeMovableObject();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void CheckInput();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated ,meta = (DisplayName = "CorrectCode"))
	FString M_CorrectCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated,meta = (DisplayName = "RandomNumbersString"))
	TArray<FString> M_RandomNumbersString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing=OnRep_UpdateInputCode ,meta = (DisplayName = "InputCode"))
	FString M_InputCode;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  ReplicatedUsing=OnRep_ChangeColour)
	FLinearColor M_Colour1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,  ReplicatedUsing=OnRep_ChangeColour)
	FLinearColor M_Colour2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,  ReplicatedUsing=OnRep_ChangeColour)
	FLinearColor M_Colour3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,  ReplicatedUsing=OnRep_ChangeColour)
	FLinearColor M_Colour4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,  ReplicatedUsing=OnRep_ChangeColour)
	FLinearColor M_Colour5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,  ReplicatedUsing=OnRep_ChangeColour)
	FLinearColor M_Colour6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,  ReplicatedUsing=OnRep_ChangeColour)
	FLinearColor M_Colour7;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing=OnRep_ChangeColour)
	FLinearColor M_Colour8;

	UPROPERTY(BlueprintAssignable)
	FResetPuzzle M_ResetPuzzle;

	//Server Functions

	UFUNCTION()
	void OnRep_ChangeColour();

	UFUNCTION()
	void OnRep_UpdateInputCode();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ResetLamps();
};
