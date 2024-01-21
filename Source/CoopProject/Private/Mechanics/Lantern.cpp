// Fill out your copyright notice in the Description page of Project Settings.


#include "Mechanics/Lantern.h"

#include <string>

#include "BaseClasses/PlayerBaseClass.h"
#include "Kismet/KismetStringLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ALantern::ALantern()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(true);

	M_SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	RootComponent = M_SceneComponent;

	M_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	M_Mesh->SetupAttachment(RootComponent);
	M_Mesh->SetIsReplicated(true);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> LanternMesh(TEXT("/Game/ModularGothicFantasyEnvironment/Meshes/Props/SM_WallLantern-1"));

    if (LanternMesh.Object)
    {
	    M_Mesh->SetStaticMesh(LanternMesh.Object);
    }

	M_SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	M_SphereCollision->SetupAttachment(RootComponent);
	M_SphereCollision->SetIsReplicated(true);
	M_SphereCollision->SetSphereRadius(300);

	M_PointLight = CreateDefaultSubobject<UPointLightComponent>("Light");
	M_PointLight->SetupAttachment(RootComponent);
	M_PointLight->SetIsReplicated(true);

	M_Fire = CreateDefaultSubobject<UNiagaraComponent>("FireParticle");
	M_Fire->SetupAttachment(RootComponent);
	M_Fire->SetIsReplicated(true);


	M_Fire->SetVisibility(true);
	M_PointLight->SetVisibility(true);

	M_Timer = 5;
	
}

// Called when the game starts or when spawned
void ALantern::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALantern::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor*> OverlappingActors;
	M_SphereCollision->GetOverlappingActors(OverlappingActors);

	for (AActor* I : OverlappingActors)
	{
		if (I->GetClass()->IsChildOf(APlayerBaseClass::StaticClass()) && !M_bIsLit)
		{
			if (HasAuthority())
			{
				M_bIsLit = true;
				LightLamp();
			}
			else
			{
				M_bIsLit = true;
				ServerRPC_LightLamp();
			}
			
		}
	}

}

void ALantern::LightLamp()
{
	if (M_Fire)
	{
		M_Fire->SetVisibility(false);
		M_PointLight->SetVisibility(false);

		if (M_TargetActor)
		{
			FString NumberToString = UKismetStringLibrary::Conv_IntToString(M_LampIndex);
			
			M_TargetActor->M_InputCode = UKismetStringLibrary::Concat_StrStr(M_TargetActor->M_InputCode, NumberToString);
			M_TargetActor->CheckInput();
		}
	}
}

void ALantern::ResetLampsLights()
{
	
	
	if (M_Timer <= 0)
	{
		M_Fire->SetVisibility(true);
		M_PointLight->SetVisibility(true);
		M_bIsLit = false;
	}
	else
	{
		M_Timer -= 1;
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ALantern::ResetLampsLights, 1.0, false);
	}

}


void ALantern::ServerRPC_LightLamp_Implementation()
{
	if (M_Fire)
	{
		M_Fire->SetVisibility(false);
		M_PointLight->SetVisibility(false);
	}
}

