﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MWAttributeComponent.h"
#include "GameFramework/Character.h"
#include "MWCharacter.generated.h"

class UMWAttributeComponent;
class UMWInteractionComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class MAGICWITHIN_API AMWCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category= "Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category= "Attack")
	TSubclassOf<AActor> DashProjectileClass;

	UPROPERTY(EditAnywhere, Category= "Attack")
	TSubclassOf<AActor> UltimateProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere, Category = "Attack")
	float AttackDelay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Attributes")
	UMWAttributeComponent* AttributeComponent;
	
	FTimerHandle TimerHandle_PrimaryAttack;
	FTimerHandle TimerHandle_SecondaryAttack;
	FTimerHandle TimerHandle_UltimateAttack;
	
public:
	// Sets default values for this character's properties
	AMWCharacter();

protected:
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	UMWInteractionComponent* InteractionComponent;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(const float Value);
	void MoveRight(const float Value);
	void PrimaryAttack();
	void PrimaryAttack_TimeElapsed();
	void SecondaryAttack();
	void SecondaryAttack_TimeElapsed();
	void UltimateAttack();
	void UltimateAttack_TimeElapsed();
	void PrimaryInteract();
	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UMWAttributeComponent* OwningComponent, float NewHealth, float Delta);
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
