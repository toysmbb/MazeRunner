// Fill out your copyright notice in the Description page of Project Settings.


#include "Switcher.h"

void ASwitcher::bisLightCanState()
{

	bIsLightSystemOn = !bIsLightSystemOn;

	UWorld* World = GetWorld();
	if (!World) return;

	
	for (TActorIterator<ALightSystem> It(World); It; ++It)
	{
		ALightSystem* Light = *It;
		if (Light)
		{
			Light->SetActorHiddenInGame(!bIsLightSystemOn);
			Light->SetActorEnableCollision(bIsLightSystemOn);
			Light->SetActorTickEnabled(bIsLightSystemOn);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("All lights are now %s"), bIsLightSystemOn ? TEXT("ON") : TEXT("OFF"));
}
