// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeightedMovableActor.h"
#include "GameFramework/Actor.h"
#include "WeightPlate.generated.h"

UCLASS()
class COOPPROJECT_API AWeightPlate : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "Root" ))
	USceneComponent* M_RootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "Mesh"))
	UStaticMeshComponent* M_Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "TriggerShape"))
	UStaticMeshComponent* M_TriggerShape;
	
public:	
	// Sets default values for this actor's properties
	AWeightPlate();

	UPROPERTY(EditAnywhere, Category = "Stats",meta = (DisplayName = "ActorsToTrigger"))
	AWeightedMovableActor* M_ActorToTrigger;

	

	

	UPROPERTY(EditAnywhere, meta = (DisplayName ="CurrentWeight"))
	int M_CurrentWeight
;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void WeightTrigger_Implementation();

};
