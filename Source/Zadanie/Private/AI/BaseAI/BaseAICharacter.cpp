// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BaseAI/BaseAICharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include <Component/StatComponent.h>
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseAICharacter::ABaseAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 600.0f, 0.0f);

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	StatComponent = CreateDefaultSubobject<UStatComponent>(TEXT("StatComponent"));

}

// Called when the game starts or when spawned
void ABaseAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseAICharacter::Patrol()
{
	
}

float ABaseAICharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	if (StatComponent->Health <= 0)
	{
		return 0;
	}

	// Calculate actual damage
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	StatComponent->ApplyDamage(ActualDamage);

	if (StatComponent->IsDeath)
	{
		Destroy();
	}

	return ActualDamage;
}

void ABaseAICharacter::Attack()
{
	FHitResult Hit;

	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = GetActorLocation() + GetActorForwardVector() * 1000.0f;

	ECollisionChannel TraceChannel = ECC_Visibility;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, TraceChannel, QueryParams);
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f); //Draw Trace line

	if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
	{
		UGameplayStatics::ApplyDamage(Hit.GetActor(), 20.f, nullptr, this, UDamageType::StaticClass());
	}
}
