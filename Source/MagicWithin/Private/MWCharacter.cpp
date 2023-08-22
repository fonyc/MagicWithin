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
	SpringArmComponent->SocketOffset = FVector(0,90.0f,0);
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

// Called to bind functionality to input
void AMWCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMWCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMWCharacter::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AMWCharacter::PrimaryAttack);
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
	
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AMWCharacter::PrimaryAttack_TimeElapsed, AttackDelay);
}

void AMWCharacter::PrimaryAttack_TimeElapsed()
{
	const FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	const FTransform SpawnTransform = FTransform(GetControlRotation(),HandLocation);
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.Instigator = this;
	
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTransform, SpawnParameters);
}

void AMWCharacter::PrimaryInteract()
{
	if(!InteractionComponent) return;
	InteractionComponent->PrimaryInteract();
}
