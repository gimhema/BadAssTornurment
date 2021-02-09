// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Character.h"
#include "MainWeapon/MainWeaponDefault.h"
#include "MainWeapon/Bullet.h"
#include "SubWeapon/SubWeaponDefault.h"
#include "PlayerbleCharacter.generated.h"

UCLASS()
class BADASSTOURNAMENT_API APlayerbleCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerbleCharacter(const FObjectInitializer& ObjectInitializer);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Status
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, replicated, Category = "Status")
	float sprintSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, replicated, Category = "Status")
	float walkSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, replicated, Category = "Status")
	float CrouchingingSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, replicated, Category = "Status")
	float Health;
	UPROPERTY(BlueprintReadWrite, replicated)
	bool IsLive = true;
	UPROPERTY(BlueprintReadWrite, replicated)
	bool IsCanFire = true;
	UPROPERTY(BlueprintReadWrite, replicated)
	bool IsCrouchinging = false;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Main Weapon
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, replicated, Category = "Status")
	class USoundCue* FireSound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, replicated, Category = "Status")
	class USoundCue* HitSound;
	UPROPERTY()
	FTimerHandle FiringHandle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, replicated)
	class USceneComponent* FirePoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, replicated)
	float dmg;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int current_bullet;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int remain_bullet;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int reload_bullet;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int total_bullet;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, replicated, Category = "Status")
	TSubclassOf<class ABullet> bulletClass;
	UPROPERTY(replicated)
	class UWorld* World;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, replicated, Category = "Status")
	class UAnimMontage* reload_motion;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, replicated, Category = "Status")
	class UParticleSystem* muzzle_particle;
	
	UFUNCTION(BlueprintCallable)
	void SpawnEmitterFunc(FVector target, FRotator target_rot);//U Skill Function
	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void SpawnEmitterFunc_TellClientTo(FVector target, FRotator target_rot);
	void SpawnEmitterFunc_TellClientTo_Implementation(FVector target, FRotator target_rot);
	bool SpawnEmitterFunc_TellClientTo_Validate(FVector target, FRotator target_rot);
	UFUNCTION(Server, Reliable, WithValidation)
	void SpawnEmitterFunc_TellServerTo(FVector target, FRotator target_rot);
	void SpawnEmitterFunc_TellServerTo_Implementation(FVector target, FRotator target_rot);
	bool SpawnEmitterFunc_TellServerTo_Validate(FVector target, FRotator target_rot);//U Skill Function

	UFUNCTION(BlueprintCallable)
	void Fire(FVector target);//U Skill Function
	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Fire_TellClientTo(FVector target);
	void Fire_TellClientTo_Implementation(FVector target);
	bool Fire_TellClientTo_Validate(FVector target);
	UFUNCTION(Server, Reliable, WithValidation)
	void Fire_TellServerTo(FVector target);
	void Fire_TellServerTo_Implementation(FVector target);
	bool Fire_TellServerTo_Validate(FVector target);//U Skill Function
	// Sub Weapon
	

	// Damage
	UFUNCTION(BlueprintCallable)
	void ReceiveDamage(float damage );
	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void ReceiveDamage_Client(float damage);
	void ReceiveDamage_Client_Implementation(float damage);
	bool ReceiveDamage_Client_Validate(float damage);
	UFUNCTION(Server, Reliable, WithValidation)
	void ReceiveDamage_Server(float damage);
	void ReceiveDamage_Server_Implementation(float damage);
	bool ReceiveDamage_Server_Validate(float damage);

	// Sprint
	UFUNCTION(BlueprintCallable)
	void Sprint(bool isPush);
	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Sprint_Client(bool isPush);
	void Sprint_Client_Implementation(bool isPush);
	bool Sprint_Client_Validate(bool isPush);
	UFUNCTION(Server, Reliable, WithValidation)
	void Sprint_Server(bool isPush);
	void Sprint_Server_Implementation(bool isPush);
	bool Sprint_Server_Validate(bool isPush);

	// Crouching
	UFUNCTION(BlueprintCallable)
	void Crouching(bool isPush);
	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Crouching_Client(bool isPush);
	void Crouching_Client_Implementation(bool isPush);
	bool Crouching_Client_Validate(bool isPush);
	UFUNCTION(Server, Reliable, WithValidation)
	void Crouching_Server(bool isPush);
	void Crouching_Server_Implementation(bool isPush);
	bool Crouching_Server_Validate(bool isPush);

	// PlaySound
	UFUNCTION(BlueprintCallable)
	void PlayCharacterSound(int sound_index);
	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void PlayCharacterSound_Client(int sound_index);
	void PlayCharacterSound_Client_Implementation(int sound_index);
	bool PlayCharacterSound_Client_Validate(int sound_index);
	UFUNCTION(Server, Reliable, WithValidation)
	void PlayCharacterSound_Server(int sound_index);
	void PlayCharacterSound_Server_Implementation(int sound_index);
	bool PlayCharacterSound_Server_Validate(int sound_index);


	// Damage
	UFUNCTION(BlueprintCallable)
	void PlayerDeath();
	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void PlayerDeath_Client();
	void PlayerDeath_Client_Implementation();
	bool PlayerDeath_Client_Validate();
	UFUNCTION(Server, Reliable, WithValidation)
	void PlayerDeath_Server();
	void PlayerDeath_Server_Implementation();
	bool PlayerDeath_Server_Validate();

	// Reload
	UFUNCTION(BlueprintCallable)
	void Reload();

	// Play ReloadMotion
	UFUNCTION(BlueprintCallable)
	void ReloadMotion();
	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void ReloadMotion_Client();
	void ReloadMotion_Client_Implementation();
	bool ReloadMotion_Client_Validate();
	UFUNCTION(Server, Reliable, WithValidation)
	void ReloadMotion_Server();
	void ReloadMotion_Server_Implementation();
	bool ReloadMotion_Server_Validate();

	// Regdoll
	UFUNCTION(BlueprintImplementableEvent)
	void Regdoll();
	UFUNCTION(BlueprintImplementableEvent)
	void ShowDeathUI();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	
		
};
