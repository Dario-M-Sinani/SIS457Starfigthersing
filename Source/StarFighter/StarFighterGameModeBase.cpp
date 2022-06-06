// Copyright Epic Games, Inc. All Rights Reserved.


#include "StarFighterGameModeBase.h"
#include "NaveTerrestreEnemiga01.h"
#include "reloj.h"
#include "InventoryActor.h"

void AStarFighterGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//auto ne = SpawnNave<ANaveTerrestreEnemiga01>();
	UE_LOG(LogTemp, Warning, TEXT("Dentro de BeginPlay en GameModeBase"));
	GetWorld()->SpawnActor<ANaveTerrestreEnemiga01>(FVector::ZeroVector, FRotator::ZeroRotator);
	

	GetWorldTimerManager().SetTimer(relojTimerHandle, this, &AStarFighterGameModeBase::SpawnNave, 20.0f, true, 10.0f);//cada cierto tiempo creamos una naveenemiga (reloj) extra en el mapa con el SpawnNave

	GetWorldTimerManager().SetTimer(relojTimerHandle1, this, &AStarFighterGameModeBase::SpawnBuffnot, 03.0f, true, 2.0f);

	//SpawnNave();

}

AStarFighterGameModeBase::AStarFighterGameModeBase()
{
	/*UE_LOG(LogTemp, Warning, TEXT("Dentro de constructor en GameModeBase"));
	GetWorld()->SpawnActor<ANaveTerrestreEnemiga01>(FVector::ZeroVector, FRotator::ZeroRotator);*/

	//SpawnNave<ANaveTerrestreEnemiga01>();

}

void AStarFighterGameModeBase::SpawnNave()
{

	UWorld* const World = GetWorld();
	ejeX = rand() % 2000 + 1;
	ejeY = rand() % 2000 + 1;
	World->SpawnActor<Areloj>(FVector(ejeX, ejeY, 112.0f), FRotator::ZeroRotator);

}

void AStarFighterGameModeBase::SpawnBuffnot()
{

	UWorld* const World = GetWorld();
	qejeX = rand() % 700 - 500;
	World->SpawnActor<AInventoryActor>(FVector(900, qejeX, 112.0f), FRotator::ZeroRotator);

}
