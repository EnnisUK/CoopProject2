// Fill out your copyright notice in the Description page of Project Settings.


#include "Mechanics/WeightedMovableActor.h"

AWeightedMovableActor::AWeightedMovableActor()
{
	bReplicates = true;
	SetReplicateMovement(true);

	M_Transporter = CreateDefaultSubobject<UTransporterComponent>("Transporter");
	M_Transporter->SetIsReplicated(true);
	M_Transporter->M_MoveTime = 0.25f;

	M_Point1 = CreateDefaultSubobject<UArrowComponent>("Point1");
	M_Point1->SetupAttachment(RootComponent);
	M_Point1->SetRelativeLocation(FVector::Zero());
	M_Point2 = CreateDefaultSubobject<UArrowComponent>("Point2");
	M_Point2->SetupAttachment(RootComponent);
	M_Point2->SetRelativeLocation(FVector(0,0,300));
}

void AWeightedMovableActor::BeginPlay()
{
	Super::BeginPlay();
	
	FVector StartPoint = GetActorLocation() + M_Point1->GetRelativeLocation();
	FVector EndPoint = GetActorLocation() + M_Point2->GetRelativeLocation();

	M_Transporter->SetPoints(StartPoint, EndPoint);
	
}
