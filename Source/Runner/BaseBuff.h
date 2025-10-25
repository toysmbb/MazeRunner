// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BaseBuff.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class RUNNER_API ABaseBuff : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseBuff();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category="Mesh")
	UStaticMeshComponent* BuffMesh;

	UPROPERTY(EditAnywhere, Category="Collision")
	UBoxComponent* HitBox;

	UPROPERTY(EditAnywhere, Category="Variables")
	bool bIsShouldDestroyMesh = true;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void ApplyEffect(AActor* OtherActor);

	UFUNCTION()
	virtual void DestroyBuffMesh();
};
