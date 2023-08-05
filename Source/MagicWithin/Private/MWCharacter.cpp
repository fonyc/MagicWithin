// Fill out your copyright notice in the Description page of Project Settings.


#include "MWCharacter.h"


// Sets default values
AMWCharacter::AMWCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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
}

