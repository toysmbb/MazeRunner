// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBuff.h"
#include "RunnerCharacter.h"
#include "UMG_BuffSpeed.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SpeedBuffActor.generated.h"

class ARunnerCharacter;


UCLASS()
class RUNNER_API ASpeedBuffActor : public ABaseBuff
{
	GENERATED_BODY()
	

protected:
	UPROPERTY(EditAnywhere, Category="Buff")
	float BuffMultiplier = 2.0f;

	UPROPERTY(EditAnywhere, Category="Buff")
	float BuffDuration = 5.0f;
	FTimerHandle BuffResetTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	TSubclassOf<class UUMG_BuffSpeed> UMGBuffClass;

	UUMG_BuffSpeed* ActiveUMGBuff;
public:
	virtual void ApplyEffect(AActor* OtherActor);
};
