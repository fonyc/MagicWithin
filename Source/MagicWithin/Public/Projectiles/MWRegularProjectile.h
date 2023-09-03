// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MWProjectileBase.h"
#include "GameFramework/Actor.h"
#include "MWRegularProjectile.generated.h"

UCLASS()
class MAGICWITHIN_API AMWRegularProjectile : public AMWProjectileBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMWRegularProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Explode_Implementation() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
