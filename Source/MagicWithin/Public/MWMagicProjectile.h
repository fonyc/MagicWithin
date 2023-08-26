// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MWMagicProjectile.generated.h"

class USphereComponent;
class UParticleSystemComponent;
class UProjectileMovementComponent;

UCLASS()
class MAGICWITHIN_API AMWMagicProjectile : public AActor
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void OnTimeToLiveEnded();
	
	AMWMagicProjectile();

protected:
	FTimerHandle TimerHandle_DestroySelf;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ProjectilePhysics, meta = (AllowPrivateAccess = "true"))
	USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ProjectileSettings, meta = (AllowPrivateAccess = "true"))
	float TTL;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ProjectilePhysics, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = VFX, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* ParticleSystemComponent;
	
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
