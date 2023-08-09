// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MWInteractionComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MAGICWITHIN_API UMWInteractionComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	void PrimaryInteract();
	
	UMWInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	float EyeSight;

	UPROPERTY(EditAnywhere)
	float VisionRadius;
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
