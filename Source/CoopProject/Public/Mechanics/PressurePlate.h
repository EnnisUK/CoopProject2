// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorComponents/TransporterComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "PressurePlate.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPressurePlateOnActivated);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPressurePlateOnDeactivated);

UCLASS()
class COOPPROJECT_API APressurePlate : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "Root" ))
	USceneComponent* M_RootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "Mesh"))
	UStaticMeshComponent* M_Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "TriggerShape"))
	UStaticMeshComponent* M_TriggerShape;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "Activated"))
	bool M_bActivated;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, meta = (DisplayName = "Transporter", AllowPrivateAccess = "true"))
	UTransporterComponent* M_Transporter;

	
public:	
	// Sets default values for this actor's properties
	APressurePlate();

	//Variables

	FTimerHandle M_OverlapActorsTimer;

	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "OnActivated"))
	FPressurePlateOnActivated M_OnActivated;

	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "OnDeactivated"))
	FPressurePlateOnDeactivated M_OnDeactivated;


	//Functions

	void CheckOverlappingActors();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
