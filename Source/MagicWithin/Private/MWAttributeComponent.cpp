// Fill out your copyright notice in the Description page of Project Settings.


#include "MWAttributeComponent.h"


// Sets default values for this component's properties
UMWAttributeComponent::UMWAttributeComponent()
{
	Health = 100.0f;
}

bool UMWAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;
	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);
	return true;
}
