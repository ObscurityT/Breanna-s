// Fill out your copyright notice in the Description page of Project Settings
#include "BasePickp.h"



// Sets default values
ABasePickp::ABasePickp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Type = EPickUpType::E_Coin;

}

// Called when the game starts or when spawned
void ABasePickp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePickp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

