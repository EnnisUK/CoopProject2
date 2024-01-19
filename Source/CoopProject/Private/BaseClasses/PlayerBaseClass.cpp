// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClasses/PlayerBaseClass.h"

#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/WidgetComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Particles/ParticleSystem.h"
#include "Systems/MainGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Mechanics/MovableActor.h"
#include "Mechanics/TriggerActor2.h"
#include "Net/UnrealNetwork.h"


// Sets default values
APlayerBaseClass::APlayerBaseClass()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    M_SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
    M_SpringArm->SetupAttachment(RootComponent);

    M_Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
    M_Camera->SetupAttachment(M_SpringArm);
	M_Camera->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	
	M_PhysicsHandleComp = CreateDefaultSubobject<UPhysicsHandleComponent>("PhysicsHandleComponent");
	M_PhysicsHandleComp->SetIsReplicated(true);
	

}

// Called when the game starts or when spawned
void APlayerBaseClass::BeginPlay()
{
	Super::BeginPlay();
	

	if (APlayerController* PC = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(M_PlayerMappingContext, 0);
		}
		
	}

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

void APlayerBaseClass::Look(const FInputActionValue& Value)
{
    // input is a Vector2D
    const FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);
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
		
		GEngine->AddOnScreenDebugMessage(-1,2,FColor::Red,TEXT("StartedSprint"));
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
		GEngine->AddOnScreenDebugMessage(-1,2,FColor::Red,TEXT("EndedSprint"));
	}
}

void APlayerBaseClass::Grab()
{
	if (HasAuthority())
	{
		if (!M_bIsGrabbed)
		{
			Print(TEXT("Grabbed By Server"));
			GrabObject();
		}
		else
		{
			Print(TEXT("Dropped By Server"));
			DropObject();
		}
	}
	else
	{
		if (!M_bIsGrabbed)
		{
			Print(TEXT("Grabbed By Client"));
			ServerRPC_GrabObject();
		}
		else
		{
			Print(TEXT("Dropped by Client"));
			ServerRPC_DropObject();
		}
	}

}

void APlayerBaseClass::Print(FString Text)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Orange, Text);
}


void APlayerBaseClass::GrabObject()
{
	FCollisionQueryParams QueryParams;
	TArray<AActor*> ActorsToIgnore;
	FVector Start = GetActorLocation();
	FVector End = Start + GetCameraComponent()->GetForwardVector() * M_GrabDistance;
	FHitResult Hit;

	if (UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), Start, End, ObjectTypes, true,ActorsToIgnore, EDrawDebugTrace::ForDuration, Hit, true ))
	{
		if (Hit.GetActor()->GetClass()->IsChildOf(ATriggerActor2::StaticClass()))
		{
			M_TriggerActor = Cast<ATriggerActor2>(Hit.GetActor());
				if (M_TriggerActor == nullptr) return;

			
				
				PickupObject(Hit.GetComponent(), Hit.ImpactPoint, Hit.GetActor()->GetActorRotation());
				M_bIsGrabbed = true;
		}
		
	}
	DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 4, 0, 3);
}

void APlayerBaseClass::DropObject()
{
		M_PhysicsHandleComp->ReleaseComponent();
		M_bIsGrabbed = false;
}

void APlayerBaseClass::ObjectMove()
{
	FVector TargetLocation = GetCameraComponent()->GetComponentLocation() + GetCameraComponent()->GetForwardVector() * M_HoldDistance;
	M_PhysicsHandleComp->SetTargetLocationAndRotation(TargetLocation, GetOwner()->GetActorRotation());	
}

void APlayerBaseClass::PickupObject(UPrimitiveComponent* HitComponent, FVector Location, FRotator Rotation)
{
	M_PhysicsHandleComp->GrabComponentAtLocationWithRotation(HitComponent, NAME_None, Location, Rotation);
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
		FVector TargetLocation = GetCameraComponent()->GetComponentLocation() + GetCameraComponent()->GetForwardVector() * M_HoldDistance;
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

	if (UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), Start, End, ObjectTypes, true,ActorsToIgnore, EDrawDebugTrace::ForDuration, Hit, true ))
	{
		if (Hit.GetActor()->GetClass()->IsChildOf(ATriggerActor2::StaticClass()))
		{
			
				if (HasAuthority())
				{
					 M_TriggerActor = Cast<ATriggerActor2>(Hit.GetActor());
					if (M_TriggerActor == nullptr) return;
					
					Print(UKismetSystemLibrary::GetDisplayName(M_PhysicsHandleComp->GetGrabbedComponent()));
					
					ServerRPC_PickupObject(Hit.GetComponent(), Hit.ImpactPoint, Hit.GetActor()->GetActorRotation());
					M_bIsGrabbed = true;
				}
			
		}
		
	}
	DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 4, 0, 3);
	
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

}

// Called to bind functionality to input
void APlayerBaseClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	EnhancedInputComponent->BindAction(M_MoveAction, ETriggerEvent::Triggered, this, &APlayerBaseClass::Move);
    EnhancedInputComponent->BindAction(M_LookAction, ETriggerEvent::Triggered, this, &APlayerBaseClass::Look);
    EnhancedInputComponent->BindAction(M_JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(M_JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(M_SprintAction, ETriggerEvent::Triggered, this, &APlayerBaseClass::Sprint);
	EnhancedInputComponent->BindAction(M_GrabAction, ETriggerEvent::Triggered, this, &APlayerBaseClass::Grab);
  

}

