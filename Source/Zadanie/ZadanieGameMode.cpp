// Copyright Epic Games, Inc. All Rights Reserved.

#include "ZadanieGameMode.h"
#include "ZadanieCharacter.h"
#include "UObject/ConstructorHelpers.h"

AZadanieGameMode::AZadanieGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
