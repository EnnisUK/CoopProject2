

#include "Mechanics/MovableActor.h"

// Sets default values
AMovableActor::AMovableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(true);

	M_RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(M_RootComponent);

	M_Point1 = CreateDefaultSubobject<UArrowComponent>("Point1");
	M_Point1->SetupAttachment(RootComponent);
	M_Point1->SetRelativeLocation(FVector::Zero());
	M_Point2 = CreateDefaultSubobject<UArrowComponent>("Point2");
	M_Point2->SetupAttachment(RootComponent);
	M_Point2->SetRelativeLocation(FVector(0,0,300));
	

	M_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	M_Mesh->SetupAttachment(RootComponent);
	M_Mesh->SetIsReplicated(true);

	M_Transporter = CreateDefaultSubobject<UTransporterComponent>("Transporter");
	M_Transporter->SetIsReplicated(true);

}

// Called when the game starts or when spawned
void AMovableActor::BeginPlay()
{
	Super::BeginPlay();

	FVector StartPoint = GetActorLocation() + M_Point1->GetRelativeLocation();
	FVector EndPoint = GetActorLocation() + M_Point2->GetRelativeLocation();
	
	M_Transporter->SetPoints(StartPoint, EndPoint);
	
}

// Called every frame
void AMovableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

