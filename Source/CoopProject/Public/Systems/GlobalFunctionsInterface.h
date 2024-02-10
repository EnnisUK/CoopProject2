// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GlobalFunctionsInterface.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGlobalFunctionsInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COOPPROJECT_API IGlobalFunctionsInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintImplementableEvent)
	void WeightTrigger();

	
	virtual void HideActor() {}



	
	virtual void ShowActor() {}

	UFUNCTION(BlueprintImplementableEvent)
	void Interact();

	UFUNCTION(BlueprintImplementableEvent)
	void SetVisFunction();

	virtual void InteractPure() {}

	
	virtual void ButtonActivateInteract(bool Activate) {}


	
	
};
