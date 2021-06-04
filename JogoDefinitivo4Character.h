// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JogoDefinitivo4Character.generated.h"


UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	E_Default UMETA(DisplayName = "DEFAULT"),
	E_Invincible UMETA(DisplayName = "INVINCIBLE"),
	E_Star UMETA(DisplayName = "STAR")
};


UCLASS(config=Game)
class AJogoDefinitivo4Character : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

protected:

	/** Called for side to side input */
	void MoveRight(float Val);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface



public:
	AJogoDefinitivo4Character();

	void TriggerJump();
	void StopJump();
	
	void Landed(const FHitResult& Hit) override;

	UFUNCTION(BlueprintCallable)
	void TakeDamage(int DamageAmount, bool LeftHit);

	UFUNCTION(BlueprintCallable)
	void PlayerAttack();

	UFUNCTION(BlueprintCallable)
	void PlayerDeath();

	UFUNCTION(BlueprintCallable)
	void BeginInvincibilityTimer();

	void EndInvincibilityTimer();

	UFUNCTION(BlueprintCallable)
	void AddCoins(int NumToAdd);

	UFUNCTION(BlueprintCallable)
	void BeginStarState(float StarTime);

	void EndStarState();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ECharacterState state;

	FTimerHandle InvincibilityTimer;

	FTimerHandle StarTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float InvincibilityTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int NumCoins;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
		int Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bHasJumped;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bHasLanded;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
		float MaxHealth;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bPlayerDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	bool bHasAttacked;

	

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
};
