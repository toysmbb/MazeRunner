// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AITask_ChasePlayer.h"

UAITask_ChasePlayer::UAITask_ChasePlayer()
{
	NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UAITask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AICon = OwnerComp.GetAIOwner();
    if (!AICon) return EBTNodeResult::Failed;

    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp) return EBTNodeResult::Failed;

    AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TargetActorKey.SelectedKeyName));
    if (!TargetActor) return EBTNodeResult::Failed;

    ARunnerCharacter* Player = Cast<ARunnerCharacter>(TargetActor);
    if (!Player) return EBTNodeResult::Failed;

    float Distance = FVector::Dist(AICon->GetPawn()->GetActorLocation(), Player->GetActorLocation());
    if (Distance <= 65.0f) return EBTNodeResult::Failed;

    FAIMoveRequest MoveReq;
    MoveReq.SetGoalActor(TargetActor);
    MoveReq.SetUsePathfinding(true);
   

    FNavPathSharedPtr NavPath;
    EPathFollowingRequestResult::Type MoveResult = AICon->MoveTo(MoveReq, &NavPath);

    if (MoveResult == EPathFollowingRequestResult::Failed)
    {
        return EBTNodeResult::Failed;
    }

    return EBTNodeResult::Succeeded;
}
