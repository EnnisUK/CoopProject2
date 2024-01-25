// Fill out your copyright notice in the Description page of Project Settings.


#include "Mechanics/PlayerLantern.h"

#include "Mechanics/HiddenSymbols.h"

// Sets default values
APlayerLantern::APlayerLantern()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(true);

	M_RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	RootComponent = M_RootComponent;

	M_Light = CreateDefaultSubobject<UPointLightComponent>("PointLight");
	M_Light->SetupAttachment(RootComponent);
	M_Light->SetIsReplicated(true);
	
	M_SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	M_SphereComp->SetupAttachment(RootComponent);
	M_SphereComp->SetIsReplicated(true);
	
	M_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	M_Mesh->SetupAttachment(RootComponent);
	M_Mesh->SetIsReplicated(true);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> LanternMesh(TEXT("/Game/Assets/Lantern"));
    if (LanternMesh.Object)
    {
	    M_Mesh->SetStaticMesh(LanternMesh.Object);
    }

}

// Called when the game starts or when spawned
void APlayerLantern::BeginPlay()
{
	Super::BeginPlay();

	M_SphereComp->OnComponentBeginOverlap.AddDynamic(this, &APlayerLantern::OnComponentStartOverlap);
	M_SphereComp->OnComponentEndOverlap.AddDynamic(this, &APlayerLantern::OnComponentEndOverlap);
	
}

// Called every frame
void APlayerLantern::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void APlayerLantern::OnComponentStartOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass()->IsChildOf(AHiddenSymbols::StaticClass()))
	{
		AHiddenSymbols* HiddenSymbols = Cast<AHiddenSymbols>(OtherActor);
		if (HiddenSymbols)
		{
			HiddenSymbols->SetSymbolVisibilty(false);
		}
		
	}
}

void APlayerLantern::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AHiddenSymbols* HiddenSymbols = Cast<AHiddenSymbols>(OtherActor);
	if (HiddenSymbols)
	{
		HiddenSymbols->SetSymbolVisibilty(true);
	}
}

