// Fill out your copyright notice in the Description page of Project Settings.


#include "FinishGame.h"

void AFinishGame::ApplyEffect(AActor* OtherActor)
{
	ARunnerCharacter* Player = Cast<ARunnerCharacter>(OtherActor);
	if(Player) 
	{
		Player->DisableInput(nullptr);
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		Widget = CreateWidget(PC, WidgetClass);
		if(Widget)
		{
			Widget->AddToViewport();
		}
	}
}
