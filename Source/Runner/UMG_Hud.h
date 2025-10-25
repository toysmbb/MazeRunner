// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "UMG_Hud.generated.h"

class UProgressBar;
UCLASS()
class RUNNER_API UUMG_Hud : public UUserWidget
{
	GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable)
    void UpdateHealthBar(float HealthPercent);

protected:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    UProgressBar* HealthProgressBar;
};