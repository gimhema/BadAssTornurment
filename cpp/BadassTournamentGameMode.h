// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine.h"
#include "Playerble/PlayerbleCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "BadassTournamentGameMode.generated.h"

UCLASS(minimalapi)
class ABadassTournamentGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

public:
	ABadassTournamentGameMode();
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Info")
	int userCount;

public:
	UFUNCTION(BlueprintCallable)
	void DecreaseUserCount();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DeclareGameResult();
};



