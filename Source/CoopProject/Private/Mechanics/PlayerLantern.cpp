// Fill out your copyright notice in the Description page of Project Settings.


#include "Mechanics/PlayerLantern.h"

#include "Kismet/GameplayStatics.h"
#include "Mechanics/DisappearingActor.h"
#include "Mechanics/HiddenSymbols.h"

// Sets default values
APlayerLantern::APlayerLantern()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(true);

	M_RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	RootComponent = M_RootComponent;

	M_Light = CreateDefaultSubobject<UPointLightComponent>("PointLight");
	M_Light->SetupAttachment(RootComponent);
	M_Light->SetIsReplicated(true);
	
	M_SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	M_SphereComp->SetupAttachment(RootComponent);
	M_SphereComp->SetIsReplicated(true);
	
	M_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	M_Mesh->SetupAttachment(RootComponent);
	M_Mesh->SetIsReplicated(true);

	M_Arrow = CreateDefaultSubobject<UArrowComponent>("Arrow");
	M_Arrow->SetupAttachment(RootComponent);
	M_Arrow->SetIsReplicated(true);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> LanternMesh(TEXT("/Game/Assets/Lantern/Lantern"));
    if (LanternMesh.Object)
    {
	    M_Mesh->SetStaticMesh(LanternMesh.Object);
    }

}

// Called when the game starts or when spawned
void APlayerLantern::BeginPlay()
{
	Super::BeginPlay();

	M_SphereComp->OnComponentBeginOverlap.AddDynamic(this, &APlayerLantern::OnComponentStartOverlap);
	M_SphereComp->OnComponentEndOverlap.AddDynamic(this, &APlayerLantern::OnComponentEndOverlap);
	
}

// Called every frame
void APlayerLantern::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ClippingTrace();
	
}

void APlayerLantern::OnComponentStartOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass()->IsChildOf(AHiddenSymbols::StaticClass()))
	{
		AHiddenSymbols* HiddenSymbols = Cast<AHiddenSymbols>(OtherActor);
		if (HiddenSymbols)
		{
			HiddenSymbols->SetSymbolVisibilty(false);
		}
		
	}
	if (OtherActor->GetClass()->IsChildOf(ADisappearingActor::StaticClass()))
	{
		if (IGlobalFunctionsInterface* GlobalFunctionsInterface = Cast<IGlobalFunctionsInterface>(OtherActor))
		{
			GlobalFunctionsInterface->HideActor();
		}
	}
	if (OtherActor->Implements<UGlobalFunctionsInterface>())
	{
		IGlobalFunctionsInterface::Execute_Interact(OtherActor);
	}
}

void APlayerLantern::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->GetClass()->IsChildOf(AHiddenSymbols::StaticClass()))
	{
		AHiddenSymbols* HiddenSymbols = Cast<AHiddenSymbols>(OtherActor);
		if (HiddenSymbols)
		{
			HiddenSymbols->SetSymbolVisibilty(true);
		}
	}

	if (OtherActor->GetClass()->IsChildOf(ADisappearingActor::StaticClass()))
	{
		if (IGlobalFunctionsInterface* GlobalFunctionsInterface = Cast<IGlobalFunctionsInterface>(OtherActor))
		{
			GlobalFunctionsInterface->ShowActor();
		}
	}
	
	if (OtherActor->Implements<UGlobalFunctionsInterface>())
	{
		IGlobalFunctionsInterface::Execute_Interact(OtherActor);
	}
	
}

void APlayerLantern::ClippingTrace()
{ /*
	if (HasAuthority())
	{
		
	
		
		FVector Start = GetActorLocation();
		FVector End = Start + M_Arrow->GetForwardVector() * 10;
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(this);
		FHitResult Hit;
		if (UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), Start, End, 15, ObjectTypes,true,ActorsToIgnore, EDrawDebugTrace::ForOneFrame,Hit, true))
		{
			 FString Msg = FString::Printf(TEXT("Hit Actor is: %s"), *UKismetSystemLibrary::GetDisplayName(Hit.GetActor()));
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, Msg);

			 if (M_Mesh->GetRelativeRotation() != FRotator(-0.5,0,0))
			 {
			 	M_Mesh->AddRelativeRotation(FRotator(-0.1,0,0));
			 	
			 }
		
		}
		else
		{
			if (M_Mesh->GetRelativeRotation() != FRotator::ZeroRotator)
			{
				FRotator ResetRotation = FMath::RInterpTo(M_Mesh->GetRelativeRotation(), FRotator::ZeroRotator, GetWorld()->GetDeltaSeconds(), 20);
				M_Mesh->SetRelativeRotation(ResetRotation);
			}
		
		}
	}
	*/

	
}

