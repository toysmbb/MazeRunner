// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "RunnerCharacter.h"
#include "AITask_ChasePlayer.generated.h"

class AAIController;
class UBlackboardComponent;

UCLASS()
class RUNNER_API UAITask_ChasePlayer : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UAITask_ChasePlayer();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	UPROPERTY(Editanywhere, Category="Ai")
	struct FBlackboardKeySelector TargetActorKey;
};
