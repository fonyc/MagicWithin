// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MWExplosiveItem.generated.h"

UCLASS()
class MAGICWITHIN_API AMWExplosiveItem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMWExplosiveItem();

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComponent;
	
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
