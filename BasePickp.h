#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickp.generated.h"


UENUM(BlueprintType)
enum class EPickUpType : uint8
{
	E_Coin			UMETA(DisplayName = "COIN"),
	E_Health		UMETA(DisplayName = "HEALTH"),
	E_Star			UMETA(DisplayName = "STAR"),
	E_KeyItem		UMETA(DisplayName = "KEY_ITEM"),
	E_OpenLevel		UMETA(DisplayName = "OPEN_LEVEL")
};

UCLASS()
class JOGODEFINITIVO4_API ABasePickp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePickp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EPickUpType Type;

};
