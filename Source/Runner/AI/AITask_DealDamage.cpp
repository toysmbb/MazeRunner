// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AITask_DealDamage.h"

UAITask_DealDamage::UAITask_DealDamage()
{
	NodeName = TEXT("Deal Damage");
}

EBTNodeResult::Type UAITask_DealDamage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AICon = OwnerComp.GetAIOwner();
	if (!AICon) return EBTNodeResult::Failed;

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp) return EBTNodeResult::Failed;

	UObject* TargetObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor");
	if (!TargetObject)
	{
		return EBTNodeResult::Failed;
	}
	ARunnerCharacter* Player = Cast<ARunnerCharacter>(TargetObject);
	if (!Player) return EBTNodeResult::Failed;
	
	float Distance = FVector::Dist(AICon->GetPawn()->GetActorLocation(), Player->GetActorLocation());
	if (Distance >= 100.0f) return EBTNodeResult::Failed;
	Player->ModifyHealth(-1);
	return EBTNodeResult::Succeeded;
}
