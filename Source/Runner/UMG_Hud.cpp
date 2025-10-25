// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG_Hud.h"

void UUMG_Hud::NativeConstruct()
{
    Super::NativeConstruct();
    if (HealthProgressBar)
    {
        HealthProgressBar->SetPercent(0.33f); 
    }
}

void UUMG_Hud::UpdateHealthBar(float HealthPercent)
{
    if (HealthProgressBar)
    {
        HealthProgressBar->SetPercent(HealthPercent);
    }
}
