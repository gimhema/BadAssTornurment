// Fill out your copyright notice in the Description page of Project Settings.

#include "Net/UnrealNetwork.h"
#include "Kismet/KismetMathLibrary.h"
#include "BadAssStartCharacter.h"

// Sets default values
ABadAssStartCharacter::ABadAssStartCharacter(const FObjectInitializer& ObjectInitializer)
{
	bReplicates = true;
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	World = GetWorld();
}

// Called when the game starts or when spawned
void ABadAssStartCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABadAssStartCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABadAssStartCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABadAssStartCharacter::GetLifetimeReplicatedProps(TArray <FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABadAssStartCharacter, World);
	DOREPLIFETIME(ABadAssStartCharacter, Spawn_Character_List);
}

void ABadAssStartCharacter::SpawnPlayerbleCharacter(FVector SpawnLoc, FRotator SpawnRot)
{
	int character_idx = UKismetMathLibrary::RandomInteger(Spawn_Character_List.Num() - 1);
	APlayerbleCharacter* playerbleCharacter = World->SpawnActor<APlayerbleCharacter>(Spawn_Character_List[character_idx], SpawnLoc, SpawnRot);
	GetController()->Possess(playerbleCharacter);
}
