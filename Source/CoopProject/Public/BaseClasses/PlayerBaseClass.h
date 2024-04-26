// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"
#include "NiagaraSystem.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Interfaces/NetworkPredictionInterface.h"
#include "Net/UnrealNetwork.h"
#include "Systems/CharacterController.h"


#include "PlayerBaseClass.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSpawnVFX);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FShowMic, bool, Show);

UCLASS()
class COOPPROJECT_API APlayerBaseClass : public ACharacter
{
	GENERATED_BODY()
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DisplayName = "Camera"))
	UCameraComponent* M_Camera;

public:
	// Sets default values for this character's properties
	APlayerBaseClass();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"), meta = (DisplayName = "Player Mapping Context"))
	class UInputMappingContext* M_PlayerMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"), meta = (DisplayName = "Move Action"))
	class UInputAction* M_MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"), meta = (DisplayName = "Pulse Action"))
	class UInputAction* M_PulseAction;


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
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"), meta = (DisplayName = "Ping Action"))
	class UInputAction* M_PingAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"), meta = (DisplayName = "Talk Action"))
    class UInputAction* M_PushToTalk;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"), meta = (DisplayName = "ScrollUp"))
	class UInputAction* M_ScrollUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"), meta = (DisplayName = "ScrollDown"))
	class UInputAction* M_ScrollDown;
	

	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Functions

	void Move(const FInputActionValue& Value);

	void Pulse();
	
	void Sprint();

	void Grab();

	void Print(FString Text);


	void PushToTalk();
	
	void GrabObject();
    
    	
	void DropObject();
    
    	
	void ObjectMove();

	void ScrollUp();

	void ScrollDown();
    
    	
	void PickupObject(UPrimitiveComponent* HitComponent, FVector Location, FRotator Rotation);

	void Ping();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void ServerRPC_Respawn();

	UFUNCTION(BlueprintCallable)
	void Respawn();
	
	
	
	//Server Functions

	UFUNCTION(Server, Unreliable)
	void ServerRPC_StartSprint();

	UFUNCTION(Server, Unreliable)
	void ServerRPC_ScrollUp();

	UFUNCTION(Server, Unreliable)
	void ServerRPC_ScrollDown();

	UFUNCTION(Server, Unreliable)
	void ServerRPC_EndSprint();

	UFUNCTION(Server, Reliable)
	void ServerRPC_GrabObject();

	UFUNCTION(Server, Reliable)
	void ServerRPC_DropObject();

	UFUNCTION(Server, Unreliable)
	void ServerRPC_ObjectMove();

	UFUNCTION(Server, Reliable)
	void ServerRPC_PickupObject(UPrimitiveComponent* HitComponent, FVector Location, FRotator Rotation);

	UFUNCTION(Server, Reliable)
	void ServerRPC_Ping();

	UFUNCTION(Server, Reliable)
	void ServerRPC_LightPulse();
	
	


	

	//Server Variables
	
	    

	

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:	
	
	//Variables

	FVector M_SpawnLocation;
	
	ACharacterController* M_CharacterController;

	bool M_IsSpeaking = false;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "LightPulseRadius"))
	float M_LightPulseRadius;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "TraceObject"))
	TEnumAsByte<ETraceTypeQuery> M_TraceType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,meta = (DisplayName = "LightPulseVFX"))
	UNiagaraSystem* M_LightPulseVFX;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Sprinting"))
	bool bIsSprinting;

	UPROPERTY(BlueprintReadOnly, Replicated)
	bool M_bIsGrabbed = false;

	UPROPERTY(EditAnywhere)
	float M_GrabDistance = 300;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "HoldDistance"))
	float M_HoldDistance = 200;

	UPROPERTY(EditAnywhere)
	float M_PingDistance = 500;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> M_PingActor;

	APawn* M_Pawn;

	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite ,meta = (AllowPrivateAccess = "true" ,DisplayName = "PhysicsHandleComp"))
	UPhysicsHandleComponent* M_PhysicsHandleComp;

	class ATriggerActor* M_TriggerActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (DisplayName = "PingOwner"))
	AActor* M_PingOwner;

	FActorSpawnParameters M_Params;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float M_MouseSens = 1.0f;

	float M_InvertedAmountY = -1;

	float M_InvertedAmountX = -1;

	UPROPERTY(BlueprintAssignable)
	FSpawnVFX SpawnVfx;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "CanPulse"))
	bool M_bCanPulse = true;

	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "ShowMicDelegate"))
	FShowMic M_ShowMic;
	
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	

	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return M_Camera; }

};



