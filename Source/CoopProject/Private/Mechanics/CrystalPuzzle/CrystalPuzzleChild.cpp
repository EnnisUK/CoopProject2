// Fill out your copyright notice in the Description page of Project Settings.


#include "Mechanics/CrystalPuzzle/CrystalPuzzleChild.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ACrystalPuzzleChild::ACrystalPuzzleChild()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(true);

	M_RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	RootComponent = M_RootComponent;

	M_CrystalMesh = CreateDefaultSubobject<UStaticMeshComponent>("CrystalMesh");
	M_CrystalMesh->SetIsReplicated(true);
	M_CrystalMesh->SetupAttachment(RootComponent);
	
	M_SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>("SphereMesh");
	M_SphereMesh->SetIsReplicated(true);
	M_SphereMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> CrystalMaterialOff(TEXT("/Game/Assets/CrystalPuzzle/M_CrystalPuzzleOff"));
	if (CrystalMaterialOff.Object)
	{
		M_CrystalMatOff = CrystalMaterialOff.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> CrystalMaterialOn(TEXT("/Game/Assets/CrystalPuzzle/M_CrystalPuzzleOn"));
	if (CrystalMaterialOn.Object)
	{
		M_CrystalMatOn = CrystalMaterialOn.Object;
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CrystalMesh(TEXT("/Game/Assets/CrystalPuzzle/Crystal"));

	if (CrystalMesh.Object)
	{
		M_CrystalMesh->SetStaticMesh(CrystalMesh.Object);
		M_CrystalMesh->SetMaterial(0, M_CrystalMatOff);
	}
	

}

// Called when the game starts or when spawned
void ACrystalPuzzleChild::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACrystalPuzzleChild::LineTrace()
{
	M_Start = M_SphereMesh->GetComponentLocation();
	M_End =  M_SphereMesh->GetForwardVector() * M_LineTraceDistance + M_Start;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	FHitResult Hit;
	if (M_bCrystalOn)
	{
		UKismetSystemLibrary::LineTraceSingle(GetWorld(),M_Start, M_End, UEngineTypes::ConvertToTraceType(ECC_Camera), false, ActorsToIgnore, EDrawDebugTrace::ForDuration, Hit, true);
		M_bIsBlocking = Hit.bBlockingHit;

		if (Hit.bBlockingHit)
		{
			M_HitEnd = Hit.Location;
		}
		
	}
}

void ACrystalPuzzleChild::Rotate()
{
	if (!GetActorRotation().Equals(M_TargetRot))
	{
		FRotator NewRot = FMath::RInterpTo(GetActorRotation(), M_TargetRot, GetWorld()->GetDeltaSeconds(), 1.5);
		SetActorRotation(NewRot);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(M_RotateTimer);
	}
}

// Called every frame
void ACrystalPuzzleChild::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LineTrace();

}

void ACrystalPuzzleChild::InteractPure()
{
	IGlobalFunctionsInterface::InteractPure();
}

void ACrystalPuzzleChild::ButtonActivateInteract(bool Activate)
{
	if (!M_bIsActive)
	{
		M_bIsActive = true;
	
		if (!M_bCrystalOn)
		{
			M_bCrystalOn = true;
			M_CrystalMesh->SetMaterial(0, M_CrystalMatOn);
			M_MeshMat = M_CrystalMatOn;
			M_LaserVFX->SetVisibility(true);
		}
		else
		{
			M_bCrystalOn = false;
			M_CrystalMesh->SetMaterial(0, M_CrystalMatOff);
			M_MeshMat = M_CrystalMatOff;
			M_LaserVFX->SetVisibility(false);
		}
	}
}

void ACrystalPuzzleChild::OnRep_HitPoint()
{
}

void ACrystalPuzzleChild::OnRep_EndPoint()
{
}

void ACrystalPuzzleChild::OnRep_MeshMat()
{
	M_CrystalMesh->SetMaterial(0, M_MeshMat);
}

void ACrystalPuzzleChild::OnRep_IsBlocking()
{
}

void ACrystalPuzzleChild::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACrystalPuzzleChild, M_End);
	DOREPLIFETIME(ACrystalPuzzleChild, M_HitEnd);
	DOREPLIFETIME(ACrystalPuzzleChild, M_MeshMat);
	DOREPLIFETIME(ACrystalPuzzleChild, M_bIsBlocking);
}

