// Fill out your copyright notice in the Description page of Project Settings.


#include "MWCharacter.h"

#include "MWAttributeComponent.h"
#include "MWInteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMWCharacter::AMWCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);

	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SocketOffset = FVector(0, 90.0f, 0);
	SpringArmComponent->TargetArmLength = 300.0f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	InteractionComponent = CreateDefaultSubobject<UMWInteractionComponent>(TEXT("InteractionComponent"));

	AttributeComponent = CreateDefaultSubobject<UMWAttributeComponent>(TEXT("AttributeComponent"));

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
	AttackDelay = 0.2f;
}

// Called when the game starts or when spawned
void AMWCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMWCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMWCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComponent->OnHealthChanged.AddDynamic(this, &AMWCharacter::OnHealthChanged);
}

// Called to bind functionality to input
void AMWCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMWCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMWCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AMWCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("SecondaryAttack", IE_Pressed, this, &AMWCharacter::SecondaryAttack);
	PlayerInputComponent->BindAction("UltimateAttack", IE_Pressed, this, &AMWCharacter::UltimateAttack);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AMWCharacter::PrimaryInteract);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
}

void AMWCharacter::MoveForward(const float Value)
{
	FRotator ControllerRotation = GetControlRotation();

	ControllerRotation.Pitch = 0.0f;
	ControllerRotation.Roll = 0.0f;

	AddMovementInput(ControllerRotation.Vector(), Value);
}

void AMWCharacter::MoveRight(const float Value)
{
	FRotator ControllerRotation = GetControlRotation();

	ControllerRotation.Pitch = 0.0f;
	ControllerRotation.Roll = 0.0f;

	const FVector RightVector = FRotationMatrix(ControllerRotation).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, Value);
}

void AMWCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AMWCharacter::PrimaryAttack_TimeElapsed,
	                                AttackDelay);
}

void AMWCharacter::PrimaryAttack_TimeElapsed()
{
	SpawnProjectile(ProjectileClass);
}

void AMWCharacter::SecondaryAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_SecondaryAttack, this, &AMWCharacter::SecondaryAttack_TimeElapsed,
	                                AttackDelay);
}

void AMWCharacter::SecondaryAttack_TimeElapsed()
{
	SpawnProjectile(DashProjectileClass);
}

void AMWCharacter::UltimateAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_UltimateAttack, this, &AMWCharacter::UltimateAttack_TimeElapsed,
	                                AttackDelay);
}

void AMWCharacter::UltimateAttack_TimeElapsed()
{
	if (!UltimateProjectileClass) return;
	SpawnProjectile(UltimateProjectileClass);
}

void AMWCharacter::PrimaryInteract()
{
	if (!InteractionComponent) return;
	InteractionComponent->PrimaryInteract();
}

void AMWCharacter::SpawnProjectile(TSubclassOf<AActor> ClassToSpawn)
{
	if (!ClassToSpawn) return;
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	FCollisionShape Shape;
	Shape.SetSphere(20.0f);

	//Ignore player
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	//Define Interaction with other stuff
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);

	FVector TraceStart = CameraComponent->GetComponentLocation();
	FVector TraceEnd = CameraComponent->GetComponentLocation() + GetControlRotation().Vector() * 5000;

	FHitResult Hit;

	if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjectQueryParams, Shape,
	                                        CollisionParams))
	{
		TraceEnd = Hit.ImpactPoint;
	}

	FRotator Rotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();

	FTransform SpawnTransform = FTransform(Rotation, HandLocation);

	GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnTransform, SpawnParams);
}

void AMWCharacter::OnHealthChanged(AActor* InstigatorActor, UMWAttributeComponent* OwningComponent, float NewHealth,
                                   float Delta)
{
	if(NewHealth <= 0)
	{
		if(APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			DisableInput(PC);
		} 
	}
}
