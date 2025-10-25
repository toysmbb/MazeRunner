// Fill out your copyright notice in the Description page of Project Settings.


#include "Activate_Trap.h"


void AActivate_Trap::ApplyEffect(AActor* OtherActor)
{
	if (!bIsCanActivate) return;
    bIsShouldDestroyMesh = false;
	ARunnerCharacter* Player = Cast<ARunnerCharacter>(OtherActor);
	ASwitcher* Switcher = SwitcherReference;
	if(Player)
	{
	
		float BestDistSq = FLT_MAX;
		ASpikeTrap* BestTrap = nullptr;
		for (TActorIterator<ASpikeTrap> It(GetWorld()); It; ++It) 
		{
			ASpikeTrap* Trap = *It;
			if (!Trap) continue;

			float DistSq = FVector::DistSquared(Trap->GetActorLocation(), GetActorLocation());
			if (DistSq < BestDistSq)
			{
				BestDistSq = DistSq;
				BestTrap = Trap;
			}
		}
		if(BestTrap && Switcher->bIsLightSystemOn == true)
		{
		if(BestDistSq <= ActivateTrapMaxRadius * ActivateTrapMaxRadius) 
		{
			BestTrap->ActivateTrap();
			bIsCanActivate = false;
			GetWorldTimerManager().SetTimer(CoolDownTimerHandle, this, &AActivate_Trap::ResetActivation, ActivationCooldown, false);
		}
		}
	}
}


void AActivate_Trap::ResetActivation()
{
	bIsCanActivate = true;
}
