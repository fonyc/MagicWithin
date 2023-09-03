// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MWProjectileBase.h"
#include "DashProjectile.generated.h"

UCLASS()
class MAGICWITHIN_API ADashProjectile : public AMWProjectileBase
{
	GENERATED_BODY()

public:
	ADashProjectile();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float TeleportDelay;

	UPROPERTY(EditDefaultsOnly, Category= "Teleport")
	float DetonateDelay;

	FTimerHandle TimerHandle_DelayedDetonate;
	virtual void Explode_Implementation() override;
	void TeleportInstigator();
	virtual void PostInitializeComponents() override;
	
public:
	virtual void Tick(float DeltaTime) override;
};
