// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComp.h"

#include "MovieSceneTracksComponentTypes.h"
#include "Components/SphereComponent.h"

// Sets default values for this component's properties
UHealthComp::UHealthComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
}


// Called when the game starts
void UHealthComp::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

void UHealthComp::SetMaxHealth(float NewMaxHealth)
{
	MaxHealth = FMath::Max(NewMaxHealth, 1.0f);
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.1f, MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth);
}

void UHealthComp::ApplyDamage_Implementation(float Damage)
{
	if (IsDead_Implementation() || Damage <= 0.0f)
		return;

	CurrentHealth -= Damage;
	CurrentHealth = FMath::Clamp(CurrentHealth , 0.0f, MaxHealth);

	OnHealthChanged.Broadcast(CurrentHealth);

	if (CurrentHealth <= 0.0f)
		OnDeath_Implementation();
}

void UHealthComp::ApplyHeal_Implementation(float HealAmount)
{
	if (IsDead_Implementation() || HealAmount <= 0.0f)
		return;

	CurrentHealth -= HealAmount;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);

	OnHealthChanged.Broadcast(CurrentHealth);
}

bool UHealthComp::IsDead_Implementation() const
{
	return CurrentHealth <= 0.0f;
}

void UHealthComp::OnDeath_Implementation()
{
	OnDeath.Broadcast();

	AActor* Owner = GetOwner();
	if (Owner)
		Owner->SetActorEnableCollision(false);
}

// void UHealthComp::HandleDeath()
// {
// 	OnDeath.Broadcast();
//
// 	GetOwner()->SetActorHiddenInGame(false);
// 	GetOwner()->SetActorHiddenInGame(true);
// 	GetOwner()->Destroy();
// }
