﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MWGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "MWItemChest.generated.h"

class UBoxComponent;

UCLASS()
class MAGICWITHIN_API AMWItemChest : public AActor, public IMWGameplayInterface
{
	GENERATED_BODY()

public:
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0", ClampMax = "150.0", UIMin = "0.0", UIMax = "150.0"))
	float TargetPitch;

protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* LidMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USceneComponent* Pivot;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	AMWItemChest();
};
