// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedBuffActor.h"


void ASpeedBuffActor::ApplyEffect(AActor* OtherActor)
{

	ARunnerCharacter* Player = Cast<ARunnerCharacter>(OtherActor);
	if (Player)
	{
		UCharacterMovementComponent* MoveComp = Player->GetCharacterMovement();
		if (MoveComp)
		{
			float OriginalSpeed = MoveComp->MaxWalkSpeed;
			MoveComp->MaxWalkSpeed *= BuffMultiplier;
			
			APlayerController* PC = GetWorld()->GetFirstPlayerController();
			ActiveUMGBuff = CreateWidget<UUMG_BuffSpeed>(PC, UMGBuffClass);
			if (ActiveUMGBuff)
			{
				ActiveUMGBuff->AddToViewport();
			}

			FTimerDelegate TimerDel;
			TimerDel.BindLambda([this, MoveComp, OriginalSpeed]()
				{
					MoveComp->MaxWalkSpeed = OriginalSpeed;

					if (ActiveUMGBuff)
					{
						ActiveUMGBuff->RemoveFromParent();
						ActiveUMGBuff = nullptr;
					}
				});
			GetWorldTimerManager().SetTimer(BuffResetTimerHandle, TimerDel, BuffDuration, false);
		}
	}
}