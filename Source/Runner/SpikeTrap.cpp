// Fill out your copyright notice in the Description page of Project Settings.


#include "SpikeTrap.h"

// Sets default values
ASpikeTrap::ASpikeTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpikeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpikeMesh"));
	RootComponent = SpikeMesh;
	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(SpikeMesh);
}

// Called when the game starts or when spawned
void ASpikeTrap::BeginPlay()
{
	Super::BeginPlay();
	HitBox->OnComponentBeginOverlap.AddDynamic(this, &ASpikeTrap::OnOverlapBegin);
	StartRelativeLocation = SpikeMesh->GetRelativeLocation();
	TargetRelativeLocation = StartRelativeLocation;
}

// Called every frame
void ASpikeTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(bIsRaising)
	{
		FVector Current = SpikeMesh->GetRelativeLocation();
		FVector New = FMath::VInterpTo(Current, TargetRelativeLocation, DeltaTime, RaiseSpeed);
		SpikeMesh->SetRelativeLocation(New);
		if(FVector::Dist(New, TargetRelativeLocation) < 1.0f) 
		{
			bIsRaising = false;
			GetWorldTimerManager().SetTimer(LowerTimerHandle, this, &ASpikeTrap::StartLower, RaiseDuration, false);
		}
	}
	else if (bIsLowering) 
	{
		FVector Current = SpikeMesh->GetRelativeLocation();
		FVector New = FMath::VInterpTo(Current, TargetRelativeLocation, DeltaTime, RaiseSpeed);
		SpikeMesh->SetRelativeLocation(New);
		if (FVector::Dist(New, TargetRelativeLocation) < 1.0f)
		{
		   bIsLowering = false;
		}
	}
}

void ASpikeTrap::ActivateTrap()
{
	StartRelativeLocation = SpikeMesh->GetRelativeLocation();
	TargetRelativeLocation = StartRelativeLocation + FVector(0.0f, 0.0f, RaiseAmount);
	bIsRaising = true;
	bIsLowering = false;
}

void ASpikeTrap::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARunnerCharacter* Player = Cast<ARunnerCharacter>(OtherActor);
	
	if (Player)
	{
		UCharacterMovementComponent* MoveCompon = Player->GetCharacterMovement();
		if (MoveCompon)
		{
			float OriginalSpeed = MoveCompon->MaxWalkSpeed;
			MoveCompon->MaxWalkSpeed /= BuffMultiplier;
			FTimerDelegate TimerDel;
			TimerDel.BindLambda([this, MoveCompon, OriginalSpeed]()
				{
					MoveCompon->MaxWalkSpeed = OriginalSpeed;
				});
			GetWorldTimerManager().SetTimer(DeBuffResetTimerHandle, TimerDel, DeBuffDuration, false);
	}

		
		Player->ModifyHealth(-1);
	}
}

void ASpikeTrap::StartLower()
{
	TargetRelativeLocation = StartRelativeLocation;
	bIsLowering = true;
	bIsRaising = false;
}
