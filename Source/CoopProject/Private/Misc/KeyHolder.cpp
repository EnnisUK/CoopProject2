// Fill out your copyright notice in the Description page of Project Settings.


#include "Misc/KeyHolder.h"

// Sets default values
AKeyHolder::AKeyHolder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(true);
	
	M_RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(M_RootComponent);

	M_KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>("KeyMesh");
	M_KeyMesh->SetupAttachment(RootComponent);
	M_KeyMesh->SetIsReplicated(true);
	M_KeyMesh->SetCollisionProfileName(FName("OverlapAllDynamic"));

	M_StatueMesh = CreateDefaultSubobject<UStaticMeshComponent>("StatueMesh");
	M_StatueMesh->SetupAttachment(RootComponent);
	M_StatueMesh->SetIsReplicated(true);
	M_StatueMesh->SetCollisionProfileName(FName("BlockAllDynamic"));


	M_HitBox = CreateDefaultSubobject<UCapsuleComponent>("HitBox");
	M_HitBox->SetupAttachment(RootComponent);
	M_HitBox->SetIsReplicated(true);
	M_HitBox->SetCollisionProfileName("OverlapAllDynamic");

	
	M_RotateSpeed = 100;

}

void AKeyHolder::ActivateKeyMesh()
{
	M_KeyMesh->SetVisibility(true);
}

// Called when the game starts or when spawned
void AKeyHolder::BeginPlay()
{
	Super::BeginPlay();

		M_KeyMesh->SetVisibility(false);

	if (M_CollectableKeyRef)
	{
		M_KeyMesh->SetStaticMesh(M_CollectableKeyRef->M_Mesh->GetStaticMesh());
	}
	

	M_HitBox->OnComponentBeginOverlap.AddDynamic(this, &AKeyHolder::OnCapsuleOverlap);
}

void AKeyHolder::OnCapsuleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult)
{
	if (HasAuthority() && M_CollectableKeyRef && M_CollectableKeyRef->M_bIsCollected)
	{
		if (M_CollectableKeyRef->M_bIsCollected)
		{
			M_bUnlocked = true;
			M_CollectableKeyRef->M_OnCollected.Broadcast();
		}
		ActivateKeyMesh();
	}
}

// Called every frame
void AKeyHolder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (M_KeyMesh->IsVisible())
	{
		M_KeyMesh->AddRelativeRotation(FRotator(0,M_RotateSpeed*DeltaTime, 0));
		
	}
	
}

