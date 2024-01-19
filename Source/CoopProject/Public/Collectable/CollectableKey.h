// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "CollectableKey.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCollectbleKeyOnCollected);

UCLASS()
class COOPPROJECT_API ACollectableKey : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "Root" ))
	USceneComponent* M_RootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "SphereCollision"))
	USphereComponent* M_SphereCollision;
	
	
public:	
	// Sets default values for this actor's properties
	ACollectableKey();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (DisplayName = "Mesh"))
	UStaticMeshComponent* M_Mesh;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void CheckOverlap();

	UPROPERTY(ReplicatedUsing = OnRep_CollectedKey, BlueprintReadWrite, VisibleAnywhere, meta = (DisplayName = "CollectedKey"))
	bool M_bIsCollected;

	UPROPERTY(ReplicatedUsing = OnRep_CollectedKey)
	FCollectbleKeyOnCollected M_OnCollected;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "RotateSpeed"))
	float M_RotateSpeed;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (DisplayName = "CollectedAudio"))
	UAudioComponent* M_CollectedAudio;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnRep_CollectedKey();


	
};
