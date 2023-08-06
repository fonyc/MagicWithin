﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "MWCharacter.h"

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
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	bUseControllerRotationYaw = false;
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