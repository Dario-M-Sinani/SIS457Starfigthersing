// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryActor.h"

// Sets default values
AInventoryActor::AInventoryActor():Super()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (MeshAsset.Object != nullptr)
	{
		GetStaticMeshComponent()->SetStaticMesh(MeshAsset.Object);
		GetStaticMeshComponent()->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	}
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
	SetActorEnableCollision(true);

	InitialLifeSpan = 4.0;

	MoveSpeedInventory = 50;

}

// Called when the game starts or when spawned
void AInventoryActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AInventoryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	srand(time(NULL));//toma el tiempo de la computadora y esto hace que no halla randoms iguales

	MovingAXT = rand() % -10; //random eje Y 

	const FVector MoveDirection = FVector(-MovingAXT, 0, 0.0f);//formamos un vector direccion con los valores random de X y Y
	const FVector Movement = MoveDirection;

	if (Movement.SizeSquared() > 0.0f)
	{
		const FRotator NewRotation = Movement.Rotation();

		FHitResult Hit(1.0f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);


	}



}

void AInventoryActor::PickUp()
{
	SetActorTickEnabled(false);
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

void AInventoryActor::PutDown(FTransform TargetLocation)
{
	SetActorTickEnabled(true);
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorLocation(TargetLocation.GetLocation());
}

