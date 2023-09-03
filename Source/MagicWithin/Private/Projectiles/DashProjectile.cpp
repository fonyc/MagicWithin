// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/DashProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

ADashProjectile::ADashProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	TeleportDelay = 0.2f;
	DetonateDelay = 0.2f;

	MovementComponent->InitialSpeed = 6.000f;
}

void ADashProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	//DrawDebugSphere(GetWorld(), GetActorLocation(),20.0f,32,FColor::Blue,1.0f);
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedDetonate, this, &ADashProjectile::Explode, DetonateDelay);
}

void ADashProjectile::Explode_Implementation()
{
	//DrawDebugSphere(GetWorld(), GetActorLocation(),20.0f,32,FColor::Red, 1.0f);
	
	//Clear timer in case the detonation is called through OnACtorHit
	GetWorldTimerManager().ClearTimer(TimerHandle_DelayedDetonate);

	UGameplayStatics::SpawnEmitterAtLocation(this,ImpactVFX,GetActorLocation(),GetActorRotation());

	//Deactivate all particles/systems/physic interactions of the projectile
	ParticleSystemComponent->DeactivateSystem();
	MovementComponent->StopMovementImmediately();
	SetActorEnableCollision(false);

	//Set new timer to measure when is the teleport going to happen
	FTimerHandle TimerHandle_DelayedTeleport;
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &ADashProjectile::TeleportInstigator, TeleportDelay);
	
	//Dont call Base Explode Implementation cause we dont want it to explode just yet.
	//Super::Explode_Implementation();
}

void ADashProjectile::TeleportInstigator()
{
	if(AActor* ActorToTeleport = GetInstigator())
	{
		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation());
	}
}

void ADashProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ADashProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

