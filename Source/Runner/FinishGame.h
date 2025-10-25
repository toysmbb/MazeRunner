// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBuff.h"
#include "RunnerCharacter.h"
#include "Blueprint/UserWidget.h"
#include "FinishGame.generated.h"


class ARunnerCharacter;

UCLASS()
class RUNNER_API AFinishGame : public ABaseBuff
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> WidgetClass;

	UUserWidget* Widget;
public:
	virtual void ApplyEffect(AActor* OtherActor) override;
  
};
