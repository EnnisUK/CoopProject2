// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "LeverActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLeverOnActivated);

UCLASS()
class COOPPROJECT_API ALeverActor : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "Root" ))
	USceneComponent* M_RootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "Sphere Hitbox" ))
	USphereComponent* M_SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "Mesh"))
	UStaticMeshComponent* M_Mesh;
	
public:	
	// Sets default values for this actor's properties
	ALeverActor();

	UPROPERTY(ReplicatedUsing = OnRep_ActivatedLever, BlueprintReadWrite, VisibleAnywhere, meta = (DisplayName = "Activated Lever"))
	bool M_bActivatedLever;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(ReplicatedUsing = OnRep_ActivatedLever, BlueprintAssignable)
	FLeverOnActivated M_ActivatedLever;


	UFUNCTION()
	void OnRep_ActivatedLever();
};
