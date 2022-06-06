// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nave.h"
#include "reloj.generated.h"

/**
 * 
 */
UCLASS()
class STARFIGHTER_API Areloj : public ANave
{
	GENERATED_BODY()
private:
	
	Areloj();

	uint32 bCanFire : 1;
	FTimerHandle TimerHandle_ShotTimerExpired; //tiempo que toma de la PC
	FTimerHandle MemberTimerHandle;//caracteristica que usaremos en el BeginPlay
	FTimerHandle MemberTimerHandle1;

public:

	//es como la distancia que aparecera la proyectil.
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadOnly)
		FVector GunOffset;

	//propiedad que hara cuanto tardara en desaparecer el proyectil.
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadOnly)
		float FireRate; 
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadOnly)
		float MoveSpeedR; 

	float MovingAX; //Movimiento que le daremos un valor aleatorio para el eje X
	float MovingAY; //Movimiento que le daremos un valor aleatorio para el eje Y


	virtual void BeginPlay() override;

	void Tick(float DeltaSeconds); //funcion que se actualizara cada frame

	void FireR(); //llamara a FireShotR
	void FireShotR(FVector FireDirectionEnemigo); //Funcion que tiene la finalidad de disparar un proyectil


	void ShotTimerExpired();

public:
	UFUNCTION()
		virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal,
			FVector NormalImpulse, const FHitResult& Hit)override;//esta funcion nos notifica cada golpe que de la clase.

	TMap<FString, int32>RInfo;
	//float Contador;



	void ConteoBalas();
	void MuestraBalasGastadas();
};

