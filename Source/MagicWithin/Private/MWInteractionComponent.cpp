// Fill out your copyright notice in the Description page of Project Settings.


#include "MWInteractionComponent.h"
#include "MWGameplayInterface.h"

// Sets default values for this component's properties
UMWInteractionComponent::UMWInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	EyeSight = 1000.f;
}

// Called when the game starts
void UMWInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UMWInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMWInteractionComponent::PrimaryInteract() 
{
	//The objects that the line trace is going to detect are World Dynamic, so make sure to set ECC_WorldDynamic to it 
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* Owner = GetOwner();
	
	FVector EyeLocation;
	FVector EndLocation;
	FRotator EyeRotation;
	
	Owner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	EndLocation = EyeLocation + EyeRotation.Vector() * EyeSight;
	
	FHitResult Hit;
	bool bBlockedHit = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, EndLocation, ObjectQueryParams);
	FColor LineTraceColor = bBlockedHit ? FColor::Orange : FColor::Red;
	if(AActor* HitActor = Hit.GetActor())
	{
		if (HitActor->Implements<UMWGameplayInterface>())
		{
			LineTraceColor = FColor::Green;
			APawn* OwnerPawn = Cast<APawn>(Owner);
			IMWGameplayInterface::Execute_Interact(HitActor, OwnerPawn);
		}
	}
	DrawDebugLine(GetWorld(),EyeLocation,EndLocation, LineTraceColor, false, 2.0f,0,2.0f);
}
