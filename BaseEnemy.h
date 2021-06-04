// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEnemy.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	E_Default UMETA(DisplayName = "DEFAULT"),
	E_Invincible UMETA(DisplayName = "INVINCIBLE"),
	E_Attack UMETA(DisplayName =  "ATTACK")
};

UCLASS()
class JOGODEFINITIVO4_API ABaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void TakeDamage(int Damage, bool LeftHit);

	UFUNCTION(BlueprintCallable)
	void TriggerDeathLogic();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayDeathVFX();

	UFUNCTION(BlueprintCallable)
	void Die();

	UFUNCTION(BlueprintCallable)
	void BeginInvincibilityTimer();

	UFUNCTION(BlueprintCallable)
	void StartAttack();

	UFUNCTION(BlueprintCallable)
	void EndAttack();

	void EndInvincibilityTimer();

	FTimerHandle InvincibilityTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEnemyState state;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InvincibilityTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Health;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsDead;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int AttackDamage;
};
