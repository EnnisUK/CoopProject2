


#include "Misc/CheckpointBox.h"


#include "BaseClasses/PlayerBaseClass.h"
#include "GameFramework/Character.h"

// Sets default values
ACheckpointBox::ACheckpointBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	M_HitBox = CreateDefaultSubobject<UBoxComponent>("HitBox");
	RootComponent = M_HitBox;

}

void ACheckpointBox::CheckOverlap()
{
	TArray<AActor*> OverlappingActors;
	
	M_HitBox->GetOverlappingActors(OverlappingActors, APlayerBaseClass::StaticClass());

	for (AActor* Player : OverlappingActors)
	{
		APlayerBaseClass* PlayerRef = Cast<APlayerBaseClass>(Player);
		if (PlayerRef)
		{
			PlayerRef->M_SpawnLocation = GetActorLocation();
		}
		
	}
}

// Called when the game starts or when spawned
void ACheckpointBox::BeginPlay()
{
	Super::BeginPlay();
	
	M_ActorLocation = GetActorLocation();

	M_HitBox->OnComponentBeginOverlap.AddDynamic(this, &ACheckpointBox::OnBeginOverlap);
}

void ACheckpointBox::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass()->IsChildOf(ACharacter::StaticClass()))
	{
		CheckOverlap();
	}
}

// Called every frame
void ACheckpointBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

