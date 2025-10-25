// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportPlayer.h"



void ATeleportPlayer::ApplyEffect(AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap with %s"), *OtherActor->GetName());
	ARunnerCharacter* Player = Cast<ARunnerCharacter>(OtherActor);
	if(Player && TeleportLocations.Num() > 0) 
	{
		int32 RandomIndex = FMath::RandRange(0, TeleportLocations.Num() - 1);
		FVector NewLocation = TeleportLocations[RandomIndex];
		
		Player->SetActorLocation(NewLocation, false, nullptr, ETeleportType::TeleportPhysics);

		UE_LOG(LogTemp, Warning, TEXT("Teleported player to: %s"), *NewLocation.ToString());
	}
}