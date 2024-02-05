// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Systems/GlobalFunctionsInterface.h"
#include "LightButton.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FResetInteract);

UCLASS()
class COOPPROJECT_API ALightButton : public AActor, public IGlobalFunctionsInterface
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "Root"))
	USceneComponent* M_Root;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "CrystalMesh"))
	UStaticMeshComponent* M_CrystalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "StandMesh"))
	UStaticMeshComponent* M_StandMesh;
	
public:	
	// Sets default values for this actor's properties
	ALightButton();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true", DisplayName = "ActorsToActivate"))
	TArray<AActor*> M_ActorsToActivate;

	UPROPERTY(ReplicatedUsing=OnRep_bIsActive, BlueprintReadOnly)
	bool M_bIsActive;

	UFUNCTION(BlueprintCallable)
	void ActivateCrystal();

	UPROPERTY(EditAnywhere)
	UMaterialInstance* M_CrystalOn;
	UPROPERTY(EditAnywhere)
	UMaterialInstance* M_CrystalOff;

	UPROPERTY(BlueprintAssignable)
	FResetInteract M_ResetInteract;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact_Implementation();

	UFUNCTION()
	void OnRep_bIsActive();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
