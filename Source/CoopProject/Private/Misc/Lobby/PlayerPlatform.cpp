// Fill out your copyright notice in the Description page of Project Settings.


#include "Misc/Lobby/PlayerPlatform.h"

// Sets default values
APlayerPlatform::APlayerPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	M_Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = M_Root;

	M_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	M_Mesh->SetupAttachment(RootComponent);
	M_Mesh->SetIsReplicated(true);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshToFind(TEXT("/Game/LevelPrototyping/Meshes/SM_ChamferCube"));

    if (MeshToFind.Object)
    {
	    M_Mesh->SetStaticMesh(MeshToFind.Object);
    }

	M_ArrowComp = CreateDefaultSubobject<UArrowComponent>("PlayerSpawnTransform");
	M_ArrowComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APlayerPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerPlatform::SpawnCharacter(APlayerController* PC)
{
	M_PC = PC;

	if (M_CurrentCharacter)
	{
		M_CurrentCharacter->Destroy();
	}
	
	if (M_PlayerChar)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::Undefined;
		AActor* ReturnValue = GetWorld()->SpawnActor<AActor>(M_PlayerChar, M_ArrowComp->GetComponentTransform(),SpawnParameters);

		M_CurrentCharacter = ReturnValue;

		HideInvite.Broadcast();
		
	
	}
	
	
	

	
}

void APlayerPlatform::Clear()
{
	GEngine->AddOnScreenDebugMessage(-1,2, FColor::Red, TEXT("Clear"));
	M_PC = nullptr;

	if (M_CurrentCharacter)
	{
		M_CurrentCharacter->Destroy();
		M_CurrentCharacter = nullptr;
	}
	ShowInvite.Broadcast();
}

