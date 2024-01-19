
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TransporterComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COOPPROJECT_API UTransporterComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTransporterComponent();

	//Variables

	FVector M_StartPoint;
	FVector M_EndPoint;
	
	bool M_bArePointsSet;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "MoveTime"))
	float M_MoveTime;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "TriggerActors"))
	TArray<AActor*> M_TriggerActors;

	UPROPERTY(VisibleAnywhere, meta = (DisplayName = "ActivatedTriggerCount"))
	int M_ActivatedTriggerCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite ,meta = (DisplayName = "AllTriggerActorsTriggered"))
	bool M_bAllTriggerActorsTriggered;

	UPROPERTY(EditAnywhere)
	bool M_bOwnerIsTriggerActor;

	//Functions

	UFUNCTION(BlueprintCallable)
	void SetPoints(FVector StartPoint, FVector EndPoint);

	UFUNCTION()
	void OnTriggerActorActivated();

	UFUNCTION()
	void OnTriggerActorDeactivated();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
