// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseAICharacter.generated.h"

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UStatComponent* StatComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void Patrol();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void Attack();

};
