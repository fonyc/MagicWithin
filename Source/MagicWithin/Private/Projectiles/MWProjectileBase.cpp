
#include "Projectiles/MWProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

void AMWProjectileBase::Explode_Implementation()
{
	if (ensure(IsValid(this) && ImpactVFX))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactVFX, GetActorLocation(), GetActorRotation());
	}
}

void AMWProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//Add possible force against the other actor
	// if (OtherActor != this && OtherComp->IsSimulatingPhysics())
	// {
	// 	OtherComp->AddImpulseAtLocation(MovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
	// }
	
	Explode();
}

// Sets default values
AMWProjectileBase::AMWProjectileBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetSphereRadius(3.0f);
	SphereComponent->SetCollisionProfileName(TEXT("MagicProjectile"));
	SphereComponent->OnComponentHit.AddDynamic(this, &AMWProjectileBase::OnActorHit);
	RootComponent = SphereComponent;

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComp"));
	ParticleSystemComponent->SetupAttachment(SphereComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	MovementComponent->InitialSpeed = 1000.f;
	MovementComponent->bRotationFollowsVelocity = true;
	MovementComponent->bInitialVelocityInLocalSpace = true;
	MovementComponent->ProjectileGravityScale = 0.0f;

	TimeToLive = 1.0f;
}

void AMWProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//Made projectile to ignore its caster
	SphereComponent->IgnoreActorWhenMoving(GetInstigator(), true);
}
