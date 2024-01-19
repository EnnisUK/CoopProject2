
#include "ActorComponents/TransporterComponent.h"

#include "Collectable/CollectableKey.h"
#include "Mechanics/LeverActor.h"
#include "Mechanics/PressurePlate.h"


UTransporterComponent::UTransporterComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);

	M_MoveTime = 3;
	M_ActivatedTriggerCount = 0;
	
	M_bArePointsSet = false;

	M_StartPoint = FVector::Zero();
	M_EndPoint = FVector::Zero();

	
	
}


void UTransporterComponent::SetPoints(FVector StartPoint, FVector EndPoint)
{
	if (StartPoint.Equals(EndPoint)) return;
	
	
	M_StartPoint = StartPoint;
	M_EndPoint = EndPoint;
	M_bArePointsSet = true;
}

void UTransporterComponent::OnTriggerActorActivated()
{
	GEngine->AddOnScreenDebugMessage(-1,2,FColor::White, TEXT("Triggered"));
	M_ActivatedTriggerCount++;

	
	
}

void UTransporterComponent::OnTriggerActorDeactivated()
{
	M_ActivatedTriggerCount--;
	

}



void UTransporterComponent::BeginPlay()
{
	Super::BeginPlay();

	if (M_bOwnerIsTriggerActor)
	{
		M_TriggerActors.Add(GetOwner());
	}
	
	for (AActor* TA : M_TriggerActors)
	{
		if (APressurePlate* PressurePlateActor = Cast<APressurePlate>(TA))
		{
			PressurePlateActor->M_OnActivated.AddDynamic(this, &UTransporterComponent::OnTriggerActorActivated);
			PressurePlateActor->M_OnDeactivated.AddDynamic(this, &UTransporterComponent::OnTriggerActorDeactivated);
			continue;
		}

		if(ACollectableKey* KeyActor = Cast<ACollectableKey>(TA))
		{
			KeyActor->M_OnCollected.AddDynamic(this, &UTransporterComponent::OnTriggerActorActivated);
			continue;
		}
		if (ALeverActor* LeverActor = Cast<ALeverActor>(TA))
		{
			LeverActor->M_ActivatedLever.AddDynamic(this, &UTransporterComponent::OnTriggerActorActivated);
		}
		
	}
	
}



void UTransporterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (M_TriggerActors.Num() > 0)
	{
		M_bAllTriggerActorsTriggered = (M_ActivatedTriggerCount >= M_TriggerActors.Num());
		if (M_bAllTriggerActorsTriggered)
		{
			
		}
	}
	
	AActor* Owner = GetOwner();
	if ( Owner && Owner->HasAuthority() && M_bArePointsSet)
	{
		FVector CurrentLocation  = Owner->GetActorLocation();
		float Speed = FVector::Distance(M_StartPoint, M_EndPoint) / M_MoveTime;

		FVector TargetLocation = M_bAllTriggerActorsTriggered ? M_EndPoint : M_StartPoint;
		
		if (!CurrentLocation.Equals(TargetLocation))
		{
			FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
			Owner->SetActorLocation(NewLocation);
		}
	}
}

