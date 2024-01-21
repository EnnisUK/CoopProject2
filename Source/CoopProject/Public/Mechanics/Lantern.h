// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CodeMovableObject.h"
#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "Lantern.generated.h"

UCLASS()
class COOPPROJECT_API ALantern : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), DisplayName = "SceneComponent")
	USceneComponent* M_SceneComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), DisplayName = "StaticMesh")
	UStaticMeshComponent* M_Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), DisplayName = "SphereCollision")
	USphereComponent* M_SphereCollision;
	
public:	
	// Sets default values for this actor's properties
	ALantern();

	UPROPERTY()
	bool M_bIsLit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int M_LampIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ACodeMovableObject* M_TargetActor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraComponent* M_Fire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPointLightComponent* M_PointLight;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void LightLamp();
	
	UFUNCTION(Server, Reliable)
	void ServerRPC_LightLamp();

	void OnRep_IsLit();


	UFUNCTION(BlueprintCallable)
	void ResetLampsLights();

	float M_Timer = 5;
	

};
