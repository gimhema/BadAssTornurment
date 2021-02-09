// Fill out your copyright notice in the Description page of Project Settings.

#include "Net/UnrealNetwork.h"
#include "SubWeaponDefault.h"

// Sets default values
ASubWeaponDefault::ASubWeaponDefault()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

// Called when the game starts or when spawned
void ASubWeaponDefault::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASubWeaponDefault::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

