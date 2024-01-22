// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseClasses/PlayerBaseClass.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "PlayerPlatform.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHideInvite);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FShowInvite);

UCLASS()
class COOPPROJECT_API APlayerPlatform : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "SceneRoot"))
	USceneComponent* M_Root;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "Mesh"))
    UStaticMeshComponent* M_Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "PlayerSpawnTransform"))
	UArrowComponent* M_ArrowComp;
	
public:	
	// Sets default values for this actor's properties
	APlayerPlatform();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Functions

	UFUNCTION(BlueprintCallable)
	void SpawnCharacter(APlayerController* PC);
	
	UFUNCTION(BlueprintCallable)
	void Clear();

	//Variables

	UPROPERTY(BlueprintReadWrite)
	APlayerController* M_PC;
	
	UPROPERTY(BlueprintReadWrite)
	AActor* M_CurrentCharacter;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> M_PlayerChar;

	UPROPERTY(BlueprintAssignable)
	FHideInvite HideInvite;

	UPROPERTY(BlueprintAssignable)
	FShowInvite ShowInvite;

};
