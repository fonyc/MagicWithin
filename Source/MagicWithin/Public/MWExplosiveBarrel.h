// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MWExplosiveBarrel.generated.h"

class URadialForceComponent;
class UBoxComponent;

UCLASS()
class MAGICWITHIN_API AMWExplosiveBarrel : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMWExplosiveBarrel();

protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere)
	URadialForceComponent* ForceComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExplosionRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExplosionStrength;

	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherACtor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
