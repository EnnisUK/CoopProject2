// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorComponents/TransporterComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "MovableActor.generated.h"



UCLASS()
class COOPPROJECT_API AMovableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovableActor();

	//Variables

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite ,meta = (DisplayName = "RootComponent"))
	USceneComponent* M_RootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite ,meta = (DisplayName = "Point 1"))
	UArrowComponent* M_Point1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite ,meta = (DisplayName = "Point 2"))
	UArrowComponent* M_Point2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite ,meta = (DisplayName = "Mesh"))
	UStaticMeshComponent* M_Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite ,meta = (DisplayName = "Transporter"))
	UTransporterComponent* M_Transporter;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
