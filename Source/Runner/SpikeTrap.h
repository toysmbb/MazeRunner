// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "RunnerCharacter.h"
#include "TimerManager.h" 
#include "GameFramework/CharacterMovementComponent.h"
#include "Switcher.h"
#include "SpikeTrap.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class ARunnerCharacter;

UCLASS()
class RUNNER_API ASpikeTrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpikeTrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(EditAnywhere, Category="SpikeMesh")
	UStaticMeshComponent* SpikeMesh;

	UPROPERTY(EditANywhere, Category="HitBox")
	UBoxComponent* HitBox;
public:
	UPROPERTY(BlueprintReadWrite, Category = "Variables")
	float BuffMultiplier = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Variables")
	float DeBuffDuration = 5.0f;
	FTimerHandle DeBuffResetTimerHandle;
	
	UPROPERTY(EditAnywhere, Category="Variables")
	float RaiseAmount = 80.0f;

	UPROPERTY(EditAnywhere, Category="Variables")
	float RaiseSpeed = 150.0f;

	UPROPERTY(Editanywhere, Category="Variables")
	float RaiseDuration = 10.0f;

	UFUNCTION()
	void ActivateTrap();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:
	bool bIsRaising = false;
	bool bIsLowering = false;
	FVector StartRelativeLocation;
	FVector TargetRelativeLocation;
	FTimerHandle LowerTimerHandle;

	void StartLower();
};

