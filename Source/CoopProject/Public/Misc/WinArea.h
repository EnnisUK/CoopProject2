// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "WinArea.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWinAreaOnWinCondition);

UCLASS()
class COOPPROJECT_API AWinArea : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "Win Zone"))
	UBoxComponent* M_WinArea;
	
public:	
	// Sets default values for this actor's properties
	AWinArea();
	

	UPROPERTY(VisibleAnywhere, meta = (DisplayName = "WinCondition"))
	bool M_bWinCondition;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable)
	FWinAreaOnWinCondition M_OnWinCondition;

	// Replicated Functions

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void MulticastRPCWin();
	

};
