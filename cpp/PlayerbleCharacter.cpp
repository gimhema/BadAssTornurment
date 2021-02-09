// Fill out your copyright notice in the Description page of Project Settings.

#include "BadassTournamentGameMode.h"
#include "Net/UnrealNetwork.h"
#include "Animation/AnimMontage.h"
#include "Kismet/KismetMathLibrary.h"
#include "PlayerbleCharacter.h"

// Sets default values
APlayerbleCharacter::APlayerbleCharacter(const FObjectInitializer& ObjectInitializer)
{
	bReplicates = true;
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	World = GetWorld();

	FirePoint = CreateDefaultSubobject<USceneComponent>(TEXT("FirePoint"));
	FirePoint->SetupAttachment(GetMesh());
	FirePoint->SetRelativeLocation(FVector(0, 0, 0));
	FirePoint->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));

	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
}

// Called when the game starts or when spawned
void APlayerbleCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerbleCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerbleCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerbleCharacter::GetLifetimeReplicatedProps(TArray <FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APlayerbleCharacter, World);
	DOREPLIFETIME(APlayerbleCharacter, Health);
	DOREPLIFETIME(APlayerbleCharacter, IsLive);
	DOREPLIFETIME(APlayerbleCharacter, FirePoint);
	DOREPLIFETIME(APlayerbleCharacter, dmg);
	DOREPLIFETIME(APlayerbleCharacter, bulletClass);
	DOREPLIFETIME(APlayerbleCharacter, IsCanFire);
	DOREPLIFETIME(APlayerbleCharacter, IsCrouchinging);
	DOREPLIFETIME(APlayerbleCharacter, sprintSpeed);
	DOREPLIFETIME(APlayerbleCharacter, walkSpeed);
	DOREPLIFETIME(APlayerbleCharacter, CrouchingingSpeed);
	DOREPLIFETIME(APlayerbleCharacter, FireSound);
	DOREPLIFETIME(APlayerbleCharacter, HitSound);
	DOREPLIFETIME(APlayerbleCharacter, reload_motion);
	DOREPLIFETIME(APlayerbleCharacter, muzzle_particle);
}

void APlayerbleCharacter::SpawnEmitterFunc(FVector target, FRotator target_rot)
{
	SpawnEmitterFunc_TellServerTo(target, target_rot);
}

void APlayerbleCharacter::SpawnEmitterFunc_TellClientTo_Implementation(FVector target, FRotator target_rot)
{
	UGameplayStatics::SpawnEmitterAtLocation(this, muzzle_particle, target, target_rot, true, EPSCPoolMethod::None);
}

bool APlayerbleCharacter::SpawnEmitterFunc_TellClientTo_Validate(FVector target, FRotator target_rot)
{
	return true;
}

void APlayerbleCharacter::SpawnEmitterFunc_TellServerTo_Implementation(FVector target, FRotator target_rot)
{
	if (Role == ROLE_Authority)
	{
		SpawnEmitterFunc_TellClientTo(target, target_rot);
	}
}

bool APlayerbleCharacter::SpawnEmitterFunc_TellServerTo_Validate(FVector target, FRotator target_rot)
{
	return true;
}





void APlayerbleCharacter::Fire(FVector target)
{
	if(IsCanFire == true && IsLive == true && current_bullet > 0)
	{ 
		current_bullet = current_bullet - 1;
		PlayCharacterSound(0);
		Fire_TellServerTo(target);
	}
}

void APlayerbleCharacter::Fire_TellClientTo_Implementation(FVector target)
{
	const FVector SpawnLocation = FirePoint->GetComponentLocation();
	const FRotator SpawnRotation = UKismetMathLibrary::FindLookAtRotation(SpawnLocation, target);
	World->SpawnActor<ABullet>(bulletClass, SpawnLocation, SpawnRotation);
}

bool APlayerbleCharacter::Fire_TellClientTo_Validate(FVector target)
{
	return true;
}

void APlayerbleCharacter::Fire_TellServerTo_Implementation(FVector target)
{
	if (Role == ROLE_Authority)
	{
		Fire_TellClientTo(target);
	}
}

bool APlayerbleCharacter::Fire_TellServerTo_Validate(FVector target)
{
	return true;
}



void APlayerbleCharacter::ReceiveDamage(float damage)
{
	ReceiveDamage_Server(damage);
}

void APlayerbleCharacter::ReceiveDamage_Client_Implementation(float damage)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, TEXT("Receive Damage Client"));
	Health = Health - damage;
	if (Health <= 0)
	{
		PlayerDeath();
	}
}

bool APlayerbleCharacter::ReceiveDamage_Client_Validate(float damage)
{
	return true;
}

void APlayerbleCharacter::ReceiveDamage_Server_Implementation(float damage)
{
	if (Role == ROLE_Authority)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, TEXT("Receive Damage Server"));
		Health = Health - damage;
		if (Health <= 0)
		{
			PlayerDeath();
		}
	}
}

bool APlayerbleCharacter::ReceiveDamage_Server_Validate(float damage)
{
	return true;
}

void APlayerbleCharacter::Sprint(bool isPush)
{
	Sprint_Server(isPush);
}

void APlayerbleCharacter::Sprint_Client_Implementation(bool isPush)
{
	if (isPush == true)
	{
		IsCanFire = false;
		GetCharacterMovement()->MaxWalkSpeed = sprintSpeed;
	}
	else
	{
		IsCanFire = true;
		GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
	}
}

bool APlayerbleCharacter::Sprint_Client_Validate(bool isPush)
{
	return true;
}

void APlayerbleCharacter::Sprint_Server_Implementation(bool isPush)
{
	if (Role == ROLE_Authority)
	{
		Sprint_Client(isPush);
	}
}

bool APlayerbleCharacter::Sprint_Server_Validate(bool isPush)
{
	return true;
}

void APlayerbleCharacter::Crouching(bool isPush)
{
	Crouching_Server(isPush);
}

void APlayerbleCharacter::Crouching_Client_Implementation(bool isPush)
{
	if (isPush == true)
	{
		IsCrouchinging = true;
		GetCharacterMovement()->MaxWalkSpeed = CrouchingingSpeed;
		FVector fireLoc;
		fireLoc.Set(FirePoint->GetComponentLocation().X, FirePoint->GetComponentLocation().Y, FirePoint->GetComponentLocation().Z - 50.0f);
		FirePoint->SetWorldLocation(fireLoc);
	}
	else
	{
		IsCrouchinging = false;
		GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
		FVector fireLoc;
		fireLoc.Set(FirePoint->GetComponentLocation().X, FirePoint->GetComponentLocation().Y, FirePoint->GetComponentLocation().Z + 50.0f);
		FirePoint->SetWorldLocation(fireLoc);
	}
}

bool APlayerbleCharacter::Crouching_Client_Validate(bool isPush)
{
	return true;
}

void APlayerbleCharacter::Crouching_Server_Implementation(bool isPush)
{
	if (Role == ROLE_Authority)
	{
		Crouching_Client(isPush);
	}
}

bool APlayerbleCharacter::Crouching_Server_Validate(bool isPush)
{
	return true;
}

void APlayerbleCharacter::PlayCharacterSound(int sound_index)
{
	PlayCharacterSound_Server(sound_index);
}

void APlayerbleCharacter::PlayCharacterSound_Client_Implementation(int sound_index)
{
	FVector spawnLocation = GetActorLocation();
	switch (sound_index)
	{
	case 0:
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, spawnLocation);
		break;
	case 1:
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, spawnLocation);
		break;
	}
	//FVector spawnLocation = GetActorLocation();
	//UGameplayStatics::SpawnEmitterAtLocation(this, PlayCharacterSoundEffect, spawnLocation, FRotator::ZeroRotator, true, EPSCPoolMethod::AutoRelease);
}

bool APlayerbleCharacter::PlayCharacterSound_Client_Validate(int sound_index)
{
	return true;
}

void APlayerbleCharacter::PlayCharacterSound_Server_Implementation(int sound_index)
{
	if (Role == ROLE_Authority)
	{
		PlayCharacterSound_Client(sound_index);
	}
}

bool APlayerbleCharacter::PlayCharacterSound_Server_Validate(int sound_index)
{
	return true;
}



void APlayerbleCharacter::PlayerDeath()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Player Death Call"));
	ShowDeathUI();
	PlayerDeath_Server();
}

void APlayerbleCharacter::PlayerDeath_Client_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Player Death Client"));
	IsLive = false;
	Regdoll();
}

bool APlayerbleCharacter::PlayerDeath_Client_Validate()
{
	return true;
}

void APlayerbleCharacter::PlayerDeath_Server_Implementation()
{
	if (Role == ROLE_Authority)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Player Death Server"));
		PlayerDeath_Client();
	}
}

bool APlayerbleCharacter::PlayerDeath_Server_Validate()
{
	return true;
}

void APlayerbleCharacter::Reload()
{
	ReloadMotion();
	if(remain_bullet > 0)
	{
	int gap_reload_current = reload_bullet - current_bullet;
	if(gap_reload_current <= remain_bullet)
	{
	current_bullet = current_bullet + gap_reload_current;
	remain_bullet = remain_bullet - gap_reload_current;
	}else
	{
	current_bullet = current_bullet + gap_reload_current;
	remain_bullet = 0;
	}
	}
}

void APlayerbleCharacter::ReloadMotion()
{
	ReloadMotion_Server();
}

void APlayerbleCharacter::ReloadMotion_Client_Implementation()
{
	IsCanFire = false;
	PlayAnimMontage(reload_motion);
	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, [this]() {IsCanFire = true; }, 1.5f, 1);
}

bool APlayerbleCharacter::ReloadMotion_Client_Validate()
{
	return true;
}

void APlayerbleCharacter::ReloadMotion_Server_Implementation()
{
	if (Role == ROLE_Authority)
	{
		ReloadMotion_Client();
	}
}

bool APlayerbleCharacter::ReloadMotion_Server_Validate()
{
	return true;
}

