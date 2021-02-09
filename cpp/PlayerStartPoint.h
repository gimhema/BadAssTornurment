// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Playerble/PlayerbleCharacter.h"
#include "GameFramework/Actor.h"
#include "PlayerStartPoint.generated.h"

UCLASS()
class BADASSTOURNAMENT_API APlayerStartPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	APlayerStartPoint(const FObjectInitializer& ObjectInitializer);
	UPROPERTY(replicated)
	class UWorld* World;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GameInfo", replicated)
	TArray<TSubclassOf<class APlayerbleCharacter>> Spawn_Character_List;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void SpawnPlayerbleCharacter();
	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void SpawnPlayerbleCharacter_Client();
	void SpawnPlayerbleCharacter_Client_Implementation();
	bool SpawnPlayerbleCharacter_Client_Validate();
	UFUNCTION(Server, Reliable, WithValidation)
	void SpawnPlayerbleCharacter_Server();
	void SpawnPlayerbleCharacter_Server_Implementation();
	bool SpawnPlayerbleCharacter_Server_Validate();
};
