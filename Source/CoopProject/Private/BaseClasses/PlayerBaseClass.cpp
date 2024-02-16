// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClasses/PlayerBaseClass.h"

#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/WidgetComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Particles/ParticleSystem.h"
#include "Systems/MainGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Mechanics/MovableActor.h"
#include "Mechanics/TriggerActor.h"
#include "Systems/AFGI_MainInstance.h"
#include "Systems/GlobalFunctionsInterface.h"


// Sets default values
APlayerBaseClass::APlayerBaseClass()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

    M_Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
    M_Camera->SetupAttachment(GetMesh(), FName(TEXT("Head")));
	M_Camera->bUsePawnControlRotation = true;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	
	M_PhysicsHandleComp = CreateDefaultSubobject<UPhysicsHandleComponent>("PhysicsHandleComponent");
	M_PhysicsHandleComp->SetIsReplicated(true);
	

}

// Called when the game starts or when spawned
void APlayerBaseClass::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PC = Cast<APlayerController>(Controller);
	if (PC)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(M_PlayerMappingContext, 0);
			
		}
		
	}


	if (!HasAuthority())
	{
		M_Pawn = Cast<APawn>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	}

	M_SpawnLocation = GetActorLocation();
	
}
	



void APlayerBaseClass::Move(const FInputActionValue& Value)
{
    if (Controller != nullptr)
    {
        const FVector2D MoveValue = Value.Get<FVector2D>();
        const FRotator MovementRotation(0, Controller->GetControlRotation().Yaw, 0);

        // Forward/Backward direction
        if (MoveValue.Y != 0.f)
        {
            // Get forward vector
            const FVector Direction = MovementRotation.RotateVector(FVector::ForwardVector);

            AddMovementInput(Direction, MoveValue.Y);
        }

        // Right/Left direction
        if (MoveValue.X != 0.f)
        {
            // Get right vector
            const FVector Direction = MovementRotation.RotateVector(FVector::RightVector);

            AddMovementInput(Direction, MoveValue.X);
        }
    }
}

void APlayerBaseClass::Pulse()
{
	if (M_bCanPulse)
	{
		M_bCanPulse = false;
		SpawnVfx.Broadcast();
	
		ServerRPC_LightPulse();
	}
	
}

void APlayerBaseClass::ServerRPC_StartSprint_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = 1200;
}

void APlayerBaseClass::ServerRPC_EndSprint_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = 600;
}

void APlayerBaseClass::Sprint()
{
	if (bIsSprinting == false)
	{
		bIsSprinting = true;
		if (HasAuthority())
		{
			GetCharacterMovement()->MaxWalkSpeed = 1200;
		}
		else
		{
			ServerRPC_StartSprint();
			GetCharacterMovement()->MaxWalkSpeed = 1200;
		}
		
		
	}
	else
	{
		bIsSprinting = false;
		if (HasAuthority())
		{
			GetCharacterMovement()->MaxWalkSpeed = 600;
		}
		else
		{
			ServerRPC_EndSprint();
			GetCharacterMovement()->MaxWalkSpeed = 600;
		}
		
	}
}

void APlayerBaseClass::Grab()
{
	if (HasAuthority())
	{
		if (!M_bIsGrabbed)
		{
			
			GrabObject();
		}
		else
		{
			
			DropObject();
		}
	}
	else
	{
		if (!M_bIsGrabbed)
		{
			
			ServerRPC_GrabObject();
		}
		else
		{
			
			ServerRPC_DropObject();
		}
	}

}

void APlayerBaseClass::Print(FString Text)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Orange, Text);
}

void APlayerBaseClass::PushToTalk()
{
	
	M_CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	

	if (!M_IsSpeaking && M_CharacterController)
	{
		M_IsSpeaking = true;
		M_CharacterController->PushToTalk(true);
	}
	else if (M_IsSpeaking && M_CharacterController)
	{
		M_IsSpeaking = false;
		M_CharacterController->PushToTalk(false);
	}
}


void APlayerBaseClass::GrabObject()
{
	FCollisionQueryParams QueryParams;
	TArray<AActor*> ActorsToIgnore;
	FVector Start = GetActorLocation();
	FVector End = Start + GetCameraComponent()->GetForwardVector() * M_GrabDistance;
	FHitResult Hit;

	if (UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), Start, End, ObjectTypes, true,ActorsToIgnore, EDrawDebugTrace::None, Hit, true ))
	{
		if (Hit.GetActor()->GetClass()->IsChildOf(ATriggerActor::StaticClass()))
		{
			M_TriggerActor = Cast<ATriggerActor>(Hit.GetActor());
				if (M_TriggerActor == nullptr) return;

			
				
				PickupObject(Hit.GetComponent(), Hit.ImpactPoint, Hit.GetActor()->GetActorRotation());
				M_bIsGrabbed = true;
		}
		
	}
	
}

void APlayerBaseClass::DropObject()
{
		
		M_PhysicsHandleComp->ReleaseComponent();
		M_bIsGrabbed = false;
}

void APlayerBaseClass::ObjectMove()
{
	FVector TargetLocation = GetActorLocation() + FVector(0, 0, 100) + GetCameraComponent()->GetForwardVector() * M_HoldDistance;
	M_PhysicsHandleComp->SetTargetLocationAndRotation(TargetLocation, GetOwner()->GetActorRotation());	
}

void APlayerBaseClass::PickupObject(UPrimitiveComponent* HitComponent, FVector Location, FRotator Rotation)
{
	M_PhysicsHandleComp->GrabComponentAtLocationWithRotation(HitComponent, NAME_None, Location, Rotation);
}

void APlayerBaseClass::Ping()
{
	
	
	if (HasAuthority())
	{
		FHitResult Hit;
		FVector Start = this->GetCameraComponent()->GetComponentLocation();
		FVector End = Start + GetCameraComponent()->GetForwardVector() * M_PingDistance;
		AActor* CamOwner = GetCameraComponent()->GetOwner();
		if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility))
		{
			M_Params.Owner = this;
			M_PingOwner = M_Params.Owner;
			GetWorld()->SpawnActor<AActor>(M_PingActor, Hit.Location, FRotator::ZeroRotator, M_Params);
			
		}
		else
		{
			M_Params.Owner = this;
			M_PingOwner = M_Params.Owner;
			GetWorld()->SpawnActor<AActor>(M_PingActor, End, FRotator::ZeroRotator, M_Params);
		}
	

		DrawDebugLine(GetWorld(), Start, End, FColor::Blue);
	}
	else
	{
		M_Params.Owner = this;
		M_PingOwner = M_Params.Owner;
		ServerRPC_Ping();
	}
}

void APlayerBaseClass::Respawn()
{
	SetActorLocation(M_SpawnLocation);
}

void APlayerBaseClass::ServerRPC_Respawn_Implementation()
{
	SetActorLocation(M_SpawnLocation);
}



void APlayerBaseClass::ServerRPC_Ping_Implementation()
{
	FHitResult Hit;
	FVector Start = this->GetCameraComponent()->GetComponentLocation();
	FVector End =  Start + GetCameraComponent()->GetForwardVector() * M_PingDistance;
	AActor* CamOwner = GetCameraComponent()->GetOwner();
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility))
	{
		GetWorld()->SpawnActor<AActor>(M_PingActor, Hit.Location, FRotator::ZeroRotator, M_Params);
	}
	else
	{
		GetWorld()->SpawnActor<AActor>(M_PingActor, End, FRotator::ZeroRotator, M_Params);
	}
	

	DrawDebugLine(GetWorld(), Start, End, FColor::Blue);
	
}


void APlayerBaseClass::ServerRPC_LightPulse_Implementation()
{
	
	if (HasAuthority())
	{
		TArray<AActor*> ActorsToIgnore;
		TArray<FHitResult> HitResultArray;

		if (UKismetSystemLibrary::SphereTraceMulti(GetWorld(),GetActorLocation(), GetActorLocation(), M_LightPulseRadius, M_TraceType, false, ActorsToIgnore, EDrawDebugTrace::None, HitResultArray, true))
		{
			for (FHitResult HR : HitResultArray)
			{
				if (HR.GetActor()->Implements<UGlobalFunctionsInterface>())
				{
					IGlobalFunctionsInterface::Execute_Interact(HR.GetActor());
				}
				if (IGlobalFunctionsInterface* GlobalFunctionsInterface = Cast<IGlobalFunctionsInterface>(HR.GetActor()))
				{
					GlobalFunctionsInterface->InteractPure();
				}
				
				
			}
		}
		
	}
}

void APlayerBaseClass::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(APlayerBaseClass, M_bIsGrabbed, COND_OwnerOnly);
}

void APlayerBaseClass::ServerRPC_PickupObject_Implementation(UPrimitiveComponent* HitComponent, FVector Location, FRotator Rotation)
{
	M_PhysicsHandleComp->GrabComponentAtLocationWithRotation(HitComponent, NAME_None, Location, Rotation);
	
}

void APlayerBaseClass::ServerRPC_ObjectMove_Implementation()
{
	if (HasAuthority())
	{
		FVector TargetLocation = GetActorLocation() + FVector(0, 0, 100) + GetCameraComponent()->GetForwardVector() * M_HoldDistance;
		M_PhysicsHandleComp->SetTargetLocationAndRotation(TargetLocation, GetOwner()->GetActorRotation());
	}

}

void APlayerBaseClass::ServerRPC_GrabObject_Implementation()
{
	FCollisionQueryParams QueryParams;
	TArray<AActor*> ActorsToIgnore;
	FVector Start = GetActorLocation();
	FVector End = Start + GetCameraComponent()->GetForwardVector() * M_GrabDistance;
	FHitResult Hit;

	if (UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), Start, End, ObjectTypes, true,ActorsToIgnore, EDrawDebugTrace::None, Hit, true ))
	{
		if (Hit.GetActor()->GetClass()->IsChildOf(ATriggerActor::StaticClass()))
		{
			
				if (HasAuthority())
				{
					 M_TriggerActor = Cast<ATriggerActor>(Hit.GetActor());
					if (M_TriggerActor == nullptr) return;
					
					Print(UKismetSystemLibrary::GetDisplayName(M_PhysicsHandleComp->GetGrabbedComponent()));
					
					ServerRPC_PickupObject(Hit.GetComponent(), Hit.ImpactPoint, Hit.GetActor()->GetActorRotation());
					M_bIsGrabbed = true;
				}
			
		}
		
	}
	
}

void APlayerBaseClass::ServerRPC_DropObject_Implementation()
{
	if (HasAuthority())
	{
		M_PhysicsHandleComp->ReleaseComponent();
		M_bIsGrabbed = false;
		
	}
	
}


// Called every frame
void APlayerBaseClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (M_bIsGrabbed)
	{
		if (!HasAuthority())
		{
			ServerRPC_ObjectMove();
		}
		else
		{
			ObjectMove();
		}
		
		
	}

	if (bIsSprinting)
	{
		if (GetVelocity().Length() <= 10)
		{
			Sprint();
			
		}
		
	}
	
	

}

// Called to bind functionality to input
void APlayerBaseClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	EnhancedInputComponent->BindAction(M_MoveAction, ETriggerEvent::Triggered, this, &APlayerBaseClass::Move);
    EnhancedInputComponent->BindAction(M_JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(M_JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(M_SprintAction, ETriggerEvent::Triggered, this, &APlayerBaseClass::Sprint);
	EnhancedInputComponent->BindAction(M_GrabAction, ETriggerEvent::Triggered, this, &APlayerBaseClass::Grab);
	EnhancedInputComponent->BindAction(M_PingAction, ETriggerEvent::Triggered, this, &APlayerBaseClass::Ping);
	EnhancedInputComponent->BindAction(M_PushToTalk, ETriggerEvent::Triggered, this, &APlayerBaseClass::PushToTalk);
	EnhancedInputComponent->BindAction(M_PulseAction, ETriggerEvent::Triggered, this, &APlayerBaseClass::Pulse);

}

