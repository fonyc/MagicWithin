// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/MWRegularProjectile.h"

AMWRegularProjectile::AMWRegularProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AMWRegularProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AMWRegularProjectile::Explode_Implementation()
{
	//Add damage to all Regular projectiles
	// if (UMWAttributeComponent* AttributeComponent = Cast<UMWAttributeComponent>(
	// 	OtherActor->GetComponentByClass(UMWAttributeComponent::StaticClass())))
	// {
	// 	AttributeComponent->ApplyHealthChange(-20.0f);
	// }

	//Add possible force against the other actor
	//if(OtherComp->IsSimulatingPhysics())
	//{
	//OtherComp->AddImpulseAtLocation(MovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
	//}
	//Explode()

	//Parent behaviour is in charge of destruction
	Super::Explode_Implementation();
}

void AMWRegularProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

