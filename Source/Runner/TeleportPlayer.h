// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBuff.h"
#include "RunnerCharacter.h"
#include "TeleportPlayer.generated.h"


class ARunnerCharacter;

UCLASS()
class RUNNER_API ATeleportPlayer : public ABaseBuff
{
	GENERATED_BODY()
	
protected:

    UPROPERTY(EditAnywhere, Category="Teleport")
	TArray<FVector> TeleportLocations;
public:
	virtual void ApplyEffect(AActor* OtherActor) override;
};
