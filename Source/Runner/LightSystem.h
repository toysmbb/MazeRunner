// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PointLightComponent.h"
#include "LightSystem.generated.h"

class UPointLightComponent;

UCLASS()
class RUNNER_API ALightSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightSystem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(EditAnywhere, Category="Light")
	UPointLightComponent* PointLight;
};
