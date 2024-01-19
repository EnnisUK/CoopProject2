// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectable/CollectableKey.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "KeyHolder.generated.h"

UCLASS()
class COOPPROJECT_API AKeyHolder : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "Root" ))
	USceneComponent* M_RootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "Key Mesh"))
	UStaticMeshComponent* M_KeyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "Statue Mesh"))
	UStaticMeshComponent* M_StatueMesh;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", DisplayName = "HitBox"))
	UCapsuleComponent* M_HitBox;
	
	
public:	
	// Sets default values for this actor's properties
	AKeyHolder();

	//Variables

	UPROPERTY(EditAnywhere)
	float M_RotateSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Key" ,meta = (DisplayName = "Key Ref"))
	ACollectableKey* M_CollectableKeyRef;
	

	//Functions

	UFUNCTION()
	void ActivateKeyMesh();

	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnCapsuleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& HitResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool M_bUnlocked;

};
