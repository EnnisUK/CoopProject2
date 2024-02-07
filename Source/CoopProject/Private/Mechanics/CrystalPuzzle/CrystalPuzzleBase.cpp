// Fill out your copyright notice in the Description page of Project Settings.


#include "Mechanics/CrystalPuzzle/CrystalPuzzleBase.h"

#include "NiagaraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ACrystalPuzzleBase::ACrystalPuzzleBase()
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
void ACrystalPuzzleBase::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle LineTraceHandle;

	GetWorldTimerManager().SetTimer(LineTraceHandle, this, &ACrystalPuzzleBase::LineTrace, 0.01, true);
	
}

void ACrystalPuzzleBase::LineTrace()
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

void ACrystalPuzzleBase::Rotate()
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
void ACrystalPuzzleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACrystalPuzzleBase::InteractPure()
{
		
	M_TargetRot = GetActorRotation() + FRotator(0,45,0);

	GetWorldTimerManager().SetTimer(M_RotateTimer, this, &ACrystalPuzzleBase::Rotate, 0.01, true);
	
}

void ACrystalPuzzleBase::ButtonActivateInteract(bool Activate)
{
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

void ACrystalPuzzleBase::OnRep_HitPoint()
{
}

void ACrystalPuzzleBase::OnRep_EndPoint()
{
}

void ACrystalPuzzleBase::OnRep_MeshMat()
{
	M_CrystalMesh->SetMaterial(0, M_MeshMat);
}

void ACrystalPuzzleBase::OnRep_IsBlocking()
{
}

void ACrystalPuzzleBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACrystalPuzzleBase, M_End);
	DOREPLIFETIME(ACrystalPuzzleBase, M_HitEnd);
	DOREPLIFETIME(ACrystalPuzzleBase, M_MeshMat);
	DOREPLIFETIME(ACrystalPuzzleBase, M_bIsBlocking);
	
}

