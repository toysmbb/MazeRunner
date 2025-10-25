// Fill out your copyright notice in the Description page of Project Settings.


#include "HPBuffActor.h"


void AHPBuffActor::ApplyEffect(AActor* OtherActor)
{
	ARunnerCharacter* Player = Cast<ARunnerCharacter>(OtherActor);
	if(Player) 
	{
		Player->ModifyHealth(SummandHP);
		
	}
}


