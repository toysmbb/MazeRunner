// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBuff.h"

// Sets default values
ABaseBuff::ABaseBuff()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BuffMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuffMesh"));
	RootComponent = BuffMesh;
	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(BuffMesh);
	HitBox->SetBoxExtent(FVector(100.0f));
}

// Called when the game starts or when spawned
void ABaseBuff::BeginPlay()
{
	Super::BeginPlay();
	HitBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseBuff::OnOverlapBegin);
}

// Called every frame
void ABaseBuff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseBuff::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{ 
	ApplyEffect(OtherActor);
	DestroyBuffMesh();
}

void ABaseBuff::ApplyEffect(AActor* OtherActor)
{
}

void ABaseBuff::DestroyBuffMesh()
{
	if (bIsShouldDestroyMesh == true) {
		BuffMesh->DestroyComponent();
		HitBox->DestroyComponent();
		SetActorHiddenInGame(true);
	}
}

