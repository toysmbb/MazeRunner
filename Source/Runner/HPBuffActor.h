// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBuff.h"
#include "RunnerCharacter.h"
#include "UMG_BuffHP.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HPBuffActor.generated.h"

class ARunnerCharacter;

UCLASS()
class RUNNER_API AHPBuffActor : public ABaseBuff
{
	GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, Category="Variabales")
	int32 SummandHP = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UUMG_BuffHP> UMGBuffClass;

	UUMG_BuffHP* ActiveUMGBuff;
public:
	virtual void ApplyEffect(AActor* OtherActor) override;

};
