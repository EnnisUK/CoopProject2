// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "Systems/GlobalFunctionsInterface.h"
#include "CrystalPuzzleBase.generated.h"



UCLASS()


class COOPPROJECT_API ACrystalPuzzleBase : public AActor, public IGlobalFunctionsInterface
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "RootComponent"))
	USceneComponent* M_RootComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "CrystalMesh"))
	UStaticMeshComponent* M_CrystalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "SphereMesh"))
	UStaticMeshComponent* M_SphereMesh;

	
public:	
	// Sets default values for this actor's properties
	ACrystalPuzzleBase();
	
	UMaterialInstance* M_CrystalMatOff;
	UMaterialInstance* M_CrystalMatOn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (DisplayName = "EndPoint"))
	FVector M_End;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (DisplayName = "StartPoint"))
	FVector M_Start;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (DisplayName = "HitLocation"))
	FVector M_HitEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraComponent* M_LaserVFX;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (DisplayName = "IsBlocking"))
	bool M_bIsBlocking;

	FTimerHandle M_RotateTimer;

	FRotator M_TargetRot;
	
	bool M_bCrystalOn;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "LineTraceDistance"))
	float M_LineTraceDistance;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void LineTrace();

	void Rotate();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InteractPure() override;

	virtual void ButtonActivateInteract(bool Activate) override;

};
