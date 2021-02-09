// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "BadassTournamentGameMode.h"
#include "BadassTournamentCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABadassTournamentGameMode::ABadassTournamentGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}


void ABadassTournamentGameMode::DecreaseUserCount()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Player Kill"));
	userCount = userCount - 1;
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::FromInt(userCount));
	if (userCount == 1) { DeclareGameResult(); }
}
