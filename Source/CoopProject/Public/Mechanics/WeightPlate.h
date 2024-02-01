// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeightedMovableActor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "ActorComponents/TransporterComponent.h"
#include "Mechanics/TriggerActor.h"
#include "WeightPlate.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeightPlateOnActivated);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeightPlateOnDeactivated);

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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "TriggerBox"))
	UBoxComponent* M_TriggerBox;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, meta = (DisplayName = "Transporter", AllowPrivateAccess = "true"))
	UTransporterComponent* M_Transporter;
	
public:	
	// Sets default values for this actor's properties
	AWeightPlate();

	UPROPERTY(EditAnywhere, Category = "Stats",meta = (DisplayName = "ActorsToTrigger"))
	AWeightedMovableActor* M_ActorToTrigger;

	
	bool bTrigger = false;
	
	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "OnActivated"))
	FWeightPlateOnActivated M_OnActivated;

	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "OnDeactivated"))
	FWeightPlateOnDeactivated M_OnDeactivated;
	
;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Print(FString Message);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	ATriggerActor* M_WeightedActor;
	
};
