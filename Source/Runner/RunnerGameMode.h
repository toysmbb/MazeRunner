// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RunnerGameMode.generated.h"

/**
 *  Simple GameMode for a third person game
 */
UCLASS(abstract)
class ARunnerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	/** Constructor */
	ARunnerGameMode();
};



