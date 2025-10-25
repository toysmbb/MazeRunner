// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "LightSystem.h"
#include "EngineUtils.h"           
#include "Engine/PointLight.h"
#include "Switcher.generated.h"

class ALightSystem;
UCLASS()
class RUNNER_API ASwitcher : public AStaticMeshActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Light")
	ALightSystem* LightSystem;
	
	UPROPERTY()
	bool bIsLightSystemOn = true;
	
	UFUNCTION()
	void bisLightCanState();
};
