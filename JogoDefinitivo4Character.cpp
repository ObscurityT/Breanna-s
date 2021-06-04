// Copyright Epic Games, Inc. All Rights Reserved.

#include "JogoDefinitivo4Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AJogoDefinitivo4Character::AJogoDefinitivo4Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	state = ECharacterState::E_Default;

	bPlayerDead = false;
	bHasAttacked = false;
	InvincibilityTime = 1.f;
	Health = 3;
	NumCoins = 0;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AJogoDefinitivo4Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AJogoDefinitivo4Character::TriggerJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AJogoDefinitivo4Character::StopJump);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AJogoDefinitivo4Character::PlayerAttack);
	PlayerInputComponent->BindAxis("MoveRight", this, &AJogoDefinitivo4Character::MoveRight);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &AJogoDefinitivo4Character::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AJogoDefinitivo4Character::TouchStopped);
}

void AJogoDefinitivo4Character::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

void AJogoDefinitivo4Character::TriggerJump()
{
		ACharacter::Jump();
		bHasLanded = false;
		bHasJumped = true;

}

void AJogoDefinitivo4Character::StopJump()
{
	ACharacter::StopJumping();
	bHasJumped = false;
}

void  AJogoDefinitivo4Character::Landed(const FHitResult& Hit)
{
	ACharacter::Landed(Hit);
	bHasJumped = false;
	bHasLanded = true;
}

void AJogoDefinitivo4Character::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void AJogoDefinitivo4Character::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void AJogoDefinitivo4Character::PlayerAttack()
{
	bHasAttacked = true;
}

void AJogoDefinitivo4Character::TakeDamage(int DamageAmount, bool LeftHit)
{
	if (state != ECharacterState::E_Invincible && state != ECharacterState::E_Star)
	{
		if (Health - DamageAmount < 0)
		{
			Health = 0;
			PlayerDeath();
		}
		else
		{
			Health -= DamageAmount;
			BeginInvincibilityTimer();

			if (LeftHit)
			{
				LaunchCharacter(FVector(0.0f, -800.0f, 400.0f), false, false);
			}
			else
			{
				LaunchCharacter(FVector(0.0f, 800.0f, 400.0f), false, false);
			}
		}
		
	}
}

void AJogoDefinitivo4Character::PlayerDeath()
{
	bPlayerDead = true;
}

void AJogoDefinitivo4Character::BeginInvincibilityTimer()
{
	GetWorld()->GetTimerManager().SetTimer(InvincibilityTimer, this, &AJogoDefinitivo4Character::EndInvincibilityTimer, InvincibilityTime, false);
	state = ECharacterState::E_Invincible;
}

void AJogoDefinitivo4Character::EndInvincibilityTimer()
{
	state = ECharacterState::E_Default;
}

void AJogoDefinitivo4Character::AddCoins(int NumToAdd)
{
	NumCoins += NumToAdd;
}

void AJogoDefinitivo4Character::BeginStarState(float StarTime)
{
	GetWorld()->GetTimerManager().SetTimer(StarTimer, this, &AJogoDefinitivo4Character::EndStarState, StarTime, false);
	state = ECharacterState::E_Star;
}

void AJogoDefinitivo4Character::EndStarState()
{
	state = ECharacterState::E_Default;
}
