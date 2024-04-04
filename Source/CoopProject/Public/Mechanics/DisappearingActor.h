// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Systems/GlobalFunctionsInterface.h"
#include "DisappearingActor.generated.h"



UCLASS()
class COOPPROJECT_API ADisappearingActor : public AActor, public IGlobalFunctionsInterface
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "Mesh"))
	UStaticMeshComponent* M_Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "Root"))
	USceneComponent* M_Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "HitBox"))
	UBoxComponent* M_HitBox;
	
	
public:	
	// Sets default values for this actor's properties
	ADisappearingActor();

	UPROPERTY(ReplicatedUsing = OnRep_IsHidden ,EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "bIsHidden"))
	bool M_bIsHidden = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "LightsOverlapping"))
	int M_LightsOverlapping;

	UPROPERTY(EditAnywhere,BlueprintReadOnly ,meta = (DisplayName = "LightsNeeded", ExposeOnSpawn = "true"))
	int M_LightsNeeded;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "TargetVisibility"))
	float M_TargetVisibility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "CurrentVisibility"))
	float M_CurrentVisibility = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "MeshMaterial"))
	UMaterialInstance* M_Material;

	UPROPERTY(ReplicatedUsing = OnRep_SetCollision)
	TEnumAsByte<ECollisionEnabled::Type> M_HitBoxCollision;

	UFUNCTION(BlueprintImplementableEvent)
	void ShowOverlay();
	
	UFUNCTION(BlueprintImplementableEvent)
	void RemoveOverlay();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnRep_IsHidden();

	UFUNCTION()
	void OnRep_SetCollision();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	void HideActor() override;

	void ShowActor() override;


	UFUNCTION(Server, Reliable)
	void ServerRPC_HideActor();

	UFUNCTION(Server, Reliable)
	void ServerRPC_ShowActor();

};


