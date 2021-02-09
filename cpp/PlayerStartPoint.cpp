// Fill out your copyright notice in the Description page of Project Settings.

#include "Net/UnrealNetwork.h"
#include "Kismet/KismetMathLibrary.h"
#include "PlayerStartPoint.h"

// Sets default values
APlayerStartPoint::APlayerStartPoint(const FObjectInitializer& ObjectInitializer)
{
	bReplicates = true;
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	World = GetWorld();
}

// Called when the game starts or when spawned
void APlayerStartPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerStartPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerStartPoint::GetLifetimeReplicatedProps(TArray <FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APlayerStartPoint, World);
	DOREPLIFETIME(APlayerStartPoint, Spawn_Character_List);
}


void APlayerStartPoint::SpawnPlayerbleCharacter()
{
	SpawnPlayerbleCharacter_Server();

}

void APlayerStartPoint::SpawnPlayerbleCharacter_Client_Implementation()
{
	int character_idx = UKismetMathLibrary::RandomInteger(Spawn_Character_List.Num());
	const FVector SpawnLocation = GetActorLocation();
	const FRotator SpawnRotation = GetActorRotation();
	World->SpawnActor<APlayerbleCharacter>(Spawn_Character_List[character_idx], SpawnLocation, SpawnRotation);
}

bool APlayerStartPoint::SpawnPlayerbleCharacter_Client_Validate()
{
	return true;
}

void APlayerStartPoint::SpawnPlayerbleCharacter_Server_Implementation()
{
	if (Role == ROLE_Authority)
	{
		SpawnPlayerbleCharacter_Client();
	}
}

bool APlayerStartPoint::SpawnPlayerbleCharacter_Server_Validate()
{
	return true;
}
