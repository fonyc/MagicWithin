// Fill out your copyright notice in the Description page of Project Settings.


#include "MWMagicProjectile.h"

#include "MWAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"


void AMWMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                        const FHitResult& SweepResult)
{
	if (OtherActor == nullptr) return;
	if (OtherActor == GetInstigator()) return;
	if (UMWAttributeComponent* AttributeComponent = Cast<UMWAttributeComponent>(
		OtherActor->GetComponentByClass(UMWAttributeComponent::StaticClass())))
	{
		AttributeComponent->ApplyHealthChange(-20.0f);
		Destroy();
	}
}

void AMWMagicProjectile::OnTimeToLiveEnded()
{
	Destroy();
}

// Sets default values
AMWMagicProjectile::AMWMagicProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetSphereRadius(3.0f);
	SphereComponent->SetCollisionProfileName(TEXT("MagicProjectile"));
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AMWMagicProjectile::OnActorOverlap);
	RootComponent = SphereComponent;

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComp"));
	ParticleSystemComponent->SetupAttachment(SphereComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	MovementComponent->InitialSpeed = 1000.f;
	MovementComponent->bRotationFollowsVelocity = true;
	MovementComponent->bInitialVelocityInLocalSpace = true;

	TTL = 1.0f;
}

// Called when the game starts or when spawned
void AMWMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle_DestroySelf, this, &AMWMagicProjectile::OnTimeToLiveEnded, TTL, false);
}

// Called every frame
void AMWMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
