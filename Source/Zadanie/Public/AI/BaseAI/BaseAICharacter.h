// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseAICharacter.generated.h"

UENUM(BlueprintType)
enum class AIDecision : uint8
{
	none,
	Patrol,
	Research,
	Persecution
};

UCLASS()
class ZADANIE_API ABaseAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseAICharacter();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		int TeamIndex = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		bool IsOn = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
