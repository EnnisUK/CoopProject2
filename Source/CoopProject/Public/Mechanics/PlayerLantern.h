// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"
#include "PlayerLantern.generated.h"

class AHiddenSymbols;

UCLASS()
class COOPPROJECT_API APlayerLantern : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "Mesh"))
	UStaticMeshComponent* M_Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "Root"))
	USceneComponent* M_RootComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "Light"))
	UPointLightComponent* M_Light;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "SphereHitbox"))
	USphereComponent* M_SphereComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "Arrow"))
	UArrowComponent* M_Arrow;
	
public:	
	// Sets default values for this actor's properties
	APlayerLantern();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Variables

	UFUNCTION()
	void OnComponentStartOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UFUNCTION(BlueprintCallable)
	void ClippingTrace();

	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
};
