// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Playerble/PlayerbleCharacter.h"
#include "GameFramework/Character.h"
#include "BadAssStartCharacter.generated.h"

UCLASS()
class BADASSTOURNAMENT_API ABadAssStartCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	ABadAssStartCharacter(const FObjectInitializer& ObjectInitializer);
	// Sets default values for this character's properties

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(replicated)
	class UWorld* World;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CharacterList", replicated)
	TArray<TSubclassOf<APlayerbleCharacter>> Spawn_Character_List;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void SpawnPlayerbleCharacter(FVector SpawnLoc, FRotator SpawnRot);

};
