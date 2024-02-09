// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Systems/GlobalFunctionsInterface.h"
#include "TwoPlayerLightButton.generated.h"


UCLASS()
class COOPPROJECT_API ATwoPlayerLightButton : public AActor, public IGlobalFunctionsInterface
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
	ATwoPlayerLightButton();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true", DisplayName = "ActorsToActivate"))
	TArray<AActor*> M_ActorsToActivate;

	UFUNCTION(BlueprintCallable)
	void ActivateCrystal();

	void ResetCrystal();

	UPROPERTY(ReplicatedUsing = OnRep_UpdateMaterial)
	UMaterialInterface* M_CrystalMaterial;

	UPROPERTY(EditAnywhere)
	UMaterialInstance* M_CrystalOn;
	UPROPERTY(EditAnywhere)
	UMaterialInstance* M_CrystalHalfOn;
	UPROPERTY(EditAnywhere)
	UMaterialInstance* M_CrystalOff;
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (DisplayName = "NeededLightPulse"))
	int M_NeededLightPulses;

	bool M_bIsActive;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	void Interact_Implementation();

	UFUNCTION()
	void OnRep_UpdateMaterial();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
