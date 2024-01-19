// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DataHolderActor.generated.h"

UCLASS()
class COOPPROJECT_API ADataHolderActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADataHolderActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void FirstPlayerController();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APlayerController* FirstController;

};
