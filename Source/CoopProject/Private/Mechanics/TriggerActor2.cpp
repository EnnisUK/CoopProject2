// Fill out your copyright notice in the Description page of Project Settings.


#include "Mechanics/TriggerActor2.h"

ATriggerActor2::ATriggerActor2()
{
	bReplicates = true;
	SetReplicateMovement(true);

	GetStaticMeshComponent()->SetIsReplicated(true);
	GetStaticMeshComponent()->SetSimulatePhysics(true);
}
