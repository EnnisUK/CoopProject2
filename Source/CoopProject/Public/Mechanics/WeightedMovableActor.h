// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorComponents/TransporterComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Systems/GlobalFunctionsInterface.h"
#include "Components/ArrowComponent.h"
#include "WeightedMovableActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FResetActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActivateWeightedPlate);

/**
 * 
 */
UCLASS()
class COOPPROJECT_API AWeightedMovableActor : public AStaticMeshActor, public IGlobalFunctionsInterface
{
	GENERATED_BODY()
public:
	AWeightedMovableActor();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, meta = (DisplayName = "Transporter", AllowPrivateAccess = "true"))
	UTransporterComponent* M_Transporter;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "Stats",meta = (DisplayName ="WeightNeeded"))
	int M_WeightNeeded;

	UPROPERTY(BlueprintAssignable)
	FResetActor M_ResetActor;

	UPROPERTY(BlueprintAssignable)
	FActivateWeightedPlate M_ActivateActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,meta = (DisplayName ="CurrentWeight"), ReplicatedUsing = OnRep_CurrentWeight)
	int M_CurrentWeight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite ,meta = (DisplayName = "Point 1"))
	UArrowComponent* M_Point1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite ,meta = (DisplayName = "Point 2"))
	UArrowComponent* M_Point2;

protected:

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_CurrentWeight();
	
};
