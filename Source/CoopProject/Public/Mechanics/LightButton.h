// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Systems/GlobalFunctionsInterface.h"
#include "LightButton.generated.h"

UCLASS()
class COOPPROJECT_API ALightButton : public AActor, public IGlobalFunctionsInterface
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "Root"))
	USceneComponent* M_Root;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "Mesh"))
	UStaticMeshComponent* M_Mesh;
	
public:	
	// Sets default values for this actor's properties
	ALightButton();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true", DisplayName = "ActorsToActivate"))
	TArray<AActor*> M_ActorsToActivate;

	bool M_bIsActive;

	UFUNCTION(BlueprintCallable)
	void ActivateCrystal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact_Implementation();

};
