// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Interfaces/NetworkPredictionInterface.h"


#include "PlayerBaseClass.generated.h"

UCLASS()
class COOPPROJECT_API APlayerBaseClass : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "SpringArm"))
	USpringArmComponent* M_SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "Camera"))
	UCameraComponent* M_Camera;

public:
	// Sets default values for this character's properties
	APlayerBaseClass();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"), meta = (DisplayName = "Player Mapping Context"))
	class UInputMappingContext* M_PlayerMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"), meta = (DisplayName = "Move Action"))
	class UInputAction* M_MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"), meta = (DisplayName = "Look Action"))
	class UInputAction* M_LookAction;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"), meta = (DisplayName = "Jump Action"))
	class UInputAction* M_JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"), meta = (DisplayName = "Save Action"))
	class UInputAction* M_SaveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"), meta = (DisplayName = "Load Action"))
	class UInputAction* M_LoadAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"), meta = (DisplayName = "Sprint Action"))
	class UInputAction* M_SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"), meta = (DisplayName = "Grab Action"))
	class UInputAction* M_GrabAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"), meta = (DisplayName = "Pause Action"))
	class UInputAction* M_PauseAction;
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Input Functions

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);
	
	void Sprint();

	void Grab();

	void Print(FString Text);
	
	//Server Functions

	UFUNCTION(Server, Unreliable)
	void ServerRPC_StartSprint();

	UFUNCTION(Server, Unreliable)
	void ServerRPC_EndSprint();

	UFUNCTION(Server, Reliable)
	void ServerRPC_GrabObject();

	UFUNCTION(Server, Reliable)
	void ServerRPC_DropObject();

	UFUNCTION(Server, Reliable)
	void ServerRPC_ObjectMove();

	UFUNCTION(Server, Reliable)
	void ServerRPC_PickupObject(UPrimitiveComponent* HitComponent, FVector Location, FRotator Rotation);
	
	    
    	void GrabObject();
    
    	
    	void DropObject();
    
    	
    	void ObjectMove();
    
    	
    	void PickupObject(UPrimitiveComponent* HitComponent, FVector Location, FRotator Rotation);
	

	

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	
	
	//Variables
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Sprinting"))
	bool bIsSprinting;

	UPROPERTY(BlueprintReadOnly, Replicated)
	bool M_bIsGrabbed = false;

	UPROPERTY(EditAnywhere)
	float M_GrabDistance = 300;

	UPROPERTY(EditAnywhere)
	float M_HoldDistance = 200;
	

	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite ,meta = (AllowPrivateAccess = "true" ,DisplayName = "PhysicsHandleComp"))
	UPhysicsHandleComponent* M_PhysicsHandleComp;

	class ATriggerActor2* M_TriggerActor;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	

	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return M_Camera; }
	FORCEINLINE class USpringArmComponent* GetSpringArmComponent() const { return M_SpringArm; }

};
