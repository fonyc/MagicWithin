﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "MWItemChest.h"
#include "Components/BoxComponent.h"

// Sets default values
AMWItemChest::AMWItemChest()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	Pivot = CreateDefaultSubobject<USceneComponent>(TEXT("Pivot"));
	Pivot->SetupAttachment(BaseMesh);

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(Pivot);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(BaseMesh);
	BoxComponent->SetCollisionProfileName(TEXT("Chest"));

	TargetPitch = 110.0f;
}

void AMWItemChest::Interact(APawn* InstigatorPawn)
{
	UE_LOG(LogTemp, Warning, TEXT("ASDASD"));
}

// Called when the game starts or when spawned
void AMWItemChest::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMWItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
