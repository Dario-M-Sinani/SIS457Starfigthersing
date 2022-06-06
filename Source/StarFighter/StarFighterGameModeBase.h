// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StarFighterGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class STARFIGHTER_API AStarFighterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	float ejeX; //daremos valores aleatorios 
	float ejeY; //daremos valores aleatorios 

	float qejeX;
	float qejeY;
	float contador;
	FTimerHandle relojTimerHandle;
	FTimerHandle relojTimerHandle1;



public:
	AStarFighterGameModeBase();

	static int contadorBalas;

	void SpawnNave();//funcionque hara aparecer una nave en en el mapa
	void SpawnBuffnot();



};

