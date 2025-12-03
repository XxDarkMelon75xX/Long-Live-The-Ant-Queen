// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComp.h"

// Sets default values for this component's properties
UHealthComp::UHealthComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHealthComp::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	
}

void UHealthComp::ApplyDamage_Implementation(float Damage)
{
	if (Damage <= 0.0f || IsDead_Implementation())
		return;

	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth);

	if (CurrentHealth <= 0.0f)
	{
		OnDeath.Broadcast();
	}
	
}

void UHealthComp::ApplyHeal_Implementation(float HealAmount)
{
	if (HealAmount <= 0.0f || IsDead_Implementation())
		return;

	CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth);
	
}
