// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractActor/BaseButton.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "AI/BaseAI/BaseAICharacter.h"
#include <Zadanie/ZadanieCharacter.h>


// Sets default values
ABaseButton::ABaseButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetCollisionProfileName("OverlapAll");
	CollisionBox->SetNotifyRigidBodyCollision(false);
	CollisionBox->SetHiddenInGame(false);
	CollisionBox->SetBoxExtent(FVector(200.0f, 200.0f, 100.0f));

}

// Called when the game starts or when spawned
void ABaseButton::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseButton::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ABaseButton::OnOverlapEnd);
	
}

// Called every frame
void ABaseButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseButton::Interact_Implementation()
{
    if (UWorld* World = GetWorld())
    {
        TArray<ABaseAICharacter*> BaseAICharacter;
        for (TActorIterator<ABaseAICharacter> FindIterator(World, ABaseAICharacter::StaticClass()); FindIterator; ++FindIterator)
        {
			BaseAICharacter.Add(*FindIterator);
        }
    }
}

void ABaseButton::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AZadanieCharacter* Character = Cast<AZadanieCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (Character)
	{
		Character->BaseButton = this;
	}
}

void ABaseButton::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AZadanieCharacter* Character = Cast<AZadanieCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (Character)
	{
		Character->BaseButton = nullptr;
	}
}

