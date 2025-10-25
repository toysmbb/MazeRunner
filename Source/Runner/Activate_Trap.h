// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBuff.h"
#include "RunnerCharacter.h"
#include "SpikeTrap.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "TimerManager.h"
#include "Switcher.h"
#include "Activate_Trap.generated.h"


class ARunnerCharacter;
class ASpikeTrap;
UCLASS()
class RUNNER_API AActivate_Trap : public ABaseBuff
{
	GENERATED_BODY()
	
protected:

   
   UPROPERTY(EditAnywhere, Category = "Dependencies")
   ASwitcher* SwitcherReference;

   UPROPERTY(EditAnywhere, Category = "Variables")
   float ActivateTrapMaxRadius = 1000.0f;

   UPROPERTY(EditAnywhere, Category = "Variables")
   float ActivationCooldown = 9.5f;
public:
	
	virtual void ApplyEffect(AActor* OtherActor) override;


	void ResetActivation();
private:
	bool bIsCanActivate = true;
	FTimerHandle CoolDownTimerHandle;
};
