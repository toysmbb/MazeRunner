// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSystem.h"

// Sets default values
ALightSystem::ALightSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	RootComponent = PointLight;
}

// Called when the game starts or when spawned
void ALightSystem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALightSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

