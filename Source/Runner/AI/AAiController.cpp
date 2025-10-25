// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AAiController.h"

void AAAiController::BeginPlay()
{
	Super::BeginPlay();
	if (EnemyBehaviorTree)
	{
		RunBehaviorTree(EnemyBehaviorTree);

		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		if (PlayerPawn)
		{
			GetBlackboardComponent()->SetValueAsObject("TargetActor", PlayerPawn);
		}
	}
}
