// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveNodriza.h"
#include "NaveAereaJugador.h"
#include "Kismet/GameplayStatics.h"
#include "Proyectil.h"
#include "StarFighterGameModeBase.h"

ANaveNodriza::ANaveNodriza()
{
	MoveSpeedR = 30.0f; // velocidad
	MoveSpeedR = 50.0f; // velocidad
	GunOffset = FVector(90.f, 0.f, 0.f); //distancia aparicion de bala
	FireRate = 5.0f;
	bCanFire = true;

	MovingAX = 0.0f;
	MovingAY = 0.0f;

	RInfo.Add("Disparo", 0);

	TArray<AActor*> Instances;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANaveNodriza::StaticClass(), Instances);

	if (Instances.Num() > 1)
	{

		Instance = Cast<ANaveNodriza>(Instances[0]);
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("%s already exists"), *Instance->GetName()));

		Destroy();

	}

}

void ANaveNodriza::BeginPlay()
{
	Super::BeginPlay();


	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ANaveNodriza::FireR, 5.0f, true, 0.0f);//hara la funcion de disparo cada tiempo determinado.


}

void ANaveNodriza::Tick(float DeltaSeconds)
{

	srand(time(NULL));//toma el tiempo de la computadora y esto hace que no halla randoms iguales

	MovingAX = rand() % 18 - 10; //random eje X 
	MovingAY = rand() % 18 - 10; //random eje Y 

	const FVector MoveDirection = FVector(MovingAX, MovingAY, 0.0f);//formamos un vector direccion con los valores random de X y Y
	const FVector Movement = MoveDirection * MoveSpeedR * DeltaSeconds;

	if (Movement.SizeSquared() > 0.0f)
	{
		const FRotator NewRotation = Movement.Rotation();

		FHitResult Hit(1.0f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
	}

	ANaveAereaJugador* avatar = Cast<ANaveAereaJugador>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)); //obtiene la ubicacion de mi Pawn o NaveJugador
	if (!avatar)
	{
		return;

	}
	FVector toPlayer = avatar->GetActorLocation() - GetActorLocation();
	toPlayer.Normalize();

	FRotator toPlayerRotation = toPlayer.Rotation(); //unimos el vector que apunta al jugador con una rotacion
	toPlayerRotation.Pitch = 0;
	RootComponent->SetWorldRotation(toPlayerRotation);


}

void ANaveNodriza::FireR()
{

	bCanFire = true;
	const FVector FireDirectionR = FVector(MovingAX, MovingAY, 0.0f).GetClampedToMaxSize(1.0f); //vector que toma valores de NaveAcuatica


	FireShotR(FireDirectionR); //llamamos a la funcion FireShot

}

void ANaveNodriza::FireShotR(FVector FireDirectionR)
{

	if (bCanFire == true)
	{
		if (FireDirectionR.SizeSquared() > 0.0f)
		{
			ANaveAereaJugador* avatar = Cast<ANaveAereaJugador>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));//obtenemos la ubicacion de la naveJugador
			if (!avatar)
			{
				return;

			}
			FVector toPlayer = avatar->GetActorLocation() - GetActorLocation();

			const FRotator FireRotation = toPlayer.Rotation(); //unimos el vector que apunta al jugador con una rotacion
			const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				World->SpawnActor<AProyectil>(SpawnLocation, FireRotation);
				World->SpawnActor<AProyectil>(SpawnLocation + FVector(450, -450, 0), FireRotation);
				World->SpawnActor<AProyectil>(SpawnLocation + FVector(-50, 50, 0), FireRotation);
				World->SpawnActor<AProyectil>(SpawnLocation + FVector(200, -200, 0), FireRotation);
				World->SpawnActor<AProyectil>(SpawnLocation + FVector(-100, 100, 0), FireRotation);

			}

			bCanFire = false;
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ANaveNodriza::ShotTimerExpired, FireRate);//funcion que hace desaparecer la bala en un tiempo

		}
	}


}

void ANaveNodriza::ShotTimerExpired()
{

	bCanFire = true;

}

void ANaveNodriza::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{

	AProyectil* Choque = Cast<AProyectil>(Other); //solo en caso de que choque con un proyectil sera ejecutada la funcion de Destroy()
	if (Choque != nullptr)
	{

		Destroy();

	}
}





