// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AAiController.generated.h"

class UBehaviorTree;

UCLASS()
class RUNNER_API AAAiController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="AI")
	UBehaviorTree* EnemyBehaviorTree;

};
