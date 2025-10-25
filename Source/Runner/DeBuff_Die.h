// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBuff.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "RunnerCharacter.h"
#include "DeBuff_Die.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class ARunnerCharacter;

UCLASS()
class RUNNER_API ADeBuff_Die : public ABaseBuff
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category = "Variables")
	int32 minusHp;
public:
	virtual void ApplyEffect(AActor* OtherActor) override;
};
	