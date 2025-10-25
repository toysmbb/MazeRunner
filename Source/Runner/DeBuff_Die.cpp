

#include "DeBuff_Die.h"


void ADeBuff_Die::ApplyEffect(AActor* OtherActor)
{
	ARunnerCharacter* Player = Cast<ARunnerCharacter>(OtherActor);
	if(Player) 
	{
		minusHp = Player->GetCurrentHealth();
		Player->ModifyHealth(-minusHp);
	}
}
