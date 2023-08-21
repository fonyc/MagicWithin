﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "MWExplosiveBarrel.h"

#include "Components/BoxComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"


// Sets default values
AMWExplosiveBarrel::AMWExplosiveBarrel()
{
	// BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	// BoxCollider->SetSimulatePhysics(true);
	// RootComponent = BoxCollider;
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;
	
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
	ForceComponent->FireImpulse();
}

// Called when the game starts or when spawned
void AMWExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();

	//BINDING OnComponent hit from mesh to our custom UFunction
	BaseMesh->OnComponentHit.AddDynamic(this, &AMWExplosiveBarrel::OnActorHit);
}

// Called every frame
void AMWExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
