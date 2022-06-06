// Fill out your copyright notice in the Description page of Project Settings.


#include "SingletonLab.h"
#include "NaveNodriza.h"

// Sets default values
ASingletonLab::ASingletonLab()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASingletonLab::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0;i <= 4;i++)
	{
		ANaveNodriza* SpawnedNaveNodriza = GetWorld()->SpawnActor<ANaveNodriza>(ANaveNodriza::StaticClass());

		if (SpawnedNaveNodriza)
		{
			NaveNodriza = SpawnedNaveNodriza;

			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("%s has been created"), *NaveNodriza->GetName()));

		}


	}

}

// Called every frame
void ASingletonLab::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

