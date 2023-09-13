#include "Projectiles/MWProjectileBase.h"

#include "MWAttributeComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

void AMWProjectileBase::Explode_Implementation()
{
	if (IsValid(this) && ImpactVFX)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactVFX, GetActorLocation(), GetActorRotation());
		Destroy();
	}
}

void AMWProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == nullptr) return;
	if (OtherActor == GetInstigator()) return;

	//Add damage to all Base projectiles
	if (UMWAttributeComponent* AttributeComponent = Cast<UMWAttributeComponent>(
		OtherActor->GetComponentByClass(UMWAttributeComponent::StaticClass())))
	{
		AttributeComponent->ApplyHealthChange(-BaseDamage);
	}

	Explode();
}

AMWProjectileBase::AMWProjectileBase()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetSphereRadius(3.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Projectile"));
	SphereComponent->OnComponentHit.AddDynamic(this, &AMWProjectileBase::OnActorHit);
	RootComponent = SphereComponent;

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComp"));
	ParticleSystemComponent->SetupAttachment(RootComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	MovementComponent->InitialSpeed = 1000.f;
	MovementComponent->bRotationFollowsVelocity = true;
	MovementComponent->bInitialVelocityInLocalSpace = true;
	MovementComponent->ProjectileGravityScale = 0.0f;

	TimeToLive = 1.0f;
	BaseDamage = 20.0f;
}

void AMWProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	SphereComponent->IgnoreActorWhenMoving(GetInstigator(), true);
}
