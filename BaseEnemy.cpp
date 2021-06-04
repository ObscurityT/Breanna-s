// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	state = EEnemyState::E_Default;
	InvincibilityTime = 1.0f;
	Health = 1;
	bIsDead = false;
}


// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseEnemy::TakeDamage(int Damage, bool LeftHit)
{
	if (state != EEnemyState::E_Invincible)
	{
		if(Health - Damage > 0)
		{ 
			Health -= Damage;
			BeginInvincibilityTimer();

			if (LeftHit)
			{
				LaunchCharacter(FVector(0.0f, -800.0f, 400.0f), false, false);
			} else
			{ 
				LaunchCharacter(FVector(0.0f, 800.0f, 400.0f), false, false);
			}
		}
		else
		{
			bIsDead = true;
			TriggerDeathLogic();
		}
	}
}

void ABaseEnemy::TriggerDeathLogic()
{
	PlayDeathVFX();
	Die();
}

void ABaseEnemy::Die()
{
	Destroy();
}

void ABaseEnemy::BeginInvincibilityTimer()
{
	UE_LOG(LogTemp, Warning, TEXT("Enemy"));
	GetWorld()->GetTimerManager().SetTimer(InvincibilityTimer, this, &ABaseEnemy::EndInvincibilityTimer, InvincibilityTime, false);
	state = EEnemyState::E_Invincible;
}


void ABaseEnemy::EndInvincibilityTimer()
{
	state = EEnemyState::E_Default;
}

void ABaseEnemy::StartAttack()
{
	state = EEnemyState::E_Attack;
}

void ABaseEnemy::EndAttack()
{
	state = EEnemyState::E_Default;
}