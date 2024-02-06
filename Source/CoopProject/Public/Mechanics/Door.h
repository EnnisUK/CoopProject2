// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Systems/GlobalFunctionsInterface.h"
#include "Door.generated.h"

UCLASS()
class COOPPROJECT_API ADoor : public AActor, public IGlobalFunctionsInterface
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "RootComp"))
	USceneComponent* M_RootComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "DoorMesh"))
	UStaticMeshComponent* M_DoorMesh;
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ButtonActivateInteract(bool Activate) override;

	void ActivateDoor();

	bool M_ActivateDoor;

	FRotator M_TargetRot;

	FRotator M_StartRotation;

	UPROPERTY(BlueprintReadOnly)
	int M_ActivatedButtons;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "NeededButtons"))
	int M_NeededButtons;

	FTimerHandle M_RotateDoor;

};
