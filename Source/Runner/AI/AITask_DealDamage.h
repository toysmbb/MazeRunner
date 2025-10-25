// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "RunnerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "AITask_DealDamage.generated.h"

/**
 * 
 */
UCLASS()
class RUNNER_API UAITask_DealDamage : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UAITask_DealDamage();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	UPROPERTY(EditanyWhere, Category="AI")
    struct FBlackboardKeySelector TargetActorKey;
};
