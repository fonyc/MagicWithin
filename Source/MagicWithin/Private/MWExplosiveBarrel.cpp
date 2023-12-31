﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "MWExplosiveBarrel.h"

#include "MWAttributeComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"


// Sets default values
AMWExplosiveBarrel::AMWExplosiveBarrel()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	AttributeComponent = CreateDefaultSubobject<UMWAttributeComponent>(TEXT("AttributeComponent"));
	
	ForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("ForceComponent"));
	ForceComponent->SetupAttachment(RootComponent);
	ForceComponent->SetAutoActivate(false);
	
	ExplosionRadius = 750.0f;
	ExplosionStrength = 2500.0f;
	
	ForceComponent->Radius = ExplosionRadius;
	ForceComponent->ImpulseStrength = ExplosionStrength;
	
	//Ignore mass on objects affected by the impulse
	ForceComponent->bImpulseVelChange = true;
	
	ForceComponent->AddCollisionChannelToAffect(ECC_WorldDynamic);
}

void AMWExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherACtor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	AttributeComponent->ApplyHealthChange(-20.0f);
	if(AttributeComponent->IsAlive())
	{
		ForceComponent->FireImpulse();
		Destroy();
	}
}

void AMWExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//BINDING OnComponent hit from mesh to our custom UFunction
	BaseMesh->OnComponentHit.AddDynamic(this, &AMWExplosiveBarrel::OnActorHit);
}

// Called every frame
void AMWExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

