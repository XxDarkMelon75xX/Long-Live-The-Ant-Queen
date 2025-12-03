// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageableInterface.h"
#include "HealthComp.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJETFILROUGEPERSO_API UHealthComp : public UActorComponent, public IDamageableInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	float CurrentHealth;

public:	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDeath OnDeath;

	virtual void ApplyDamage_Implementation(float Damage) override;
	virtual void ApplyHeal_Implementation(float HealAmount) override;
	virtual bool IsDead_Implementation() const override { return CurrentHealth <= 0.0f; };

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetCurrentHealth() const { return CurrentHealth; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetMaxHealth() const { return MaxHealth; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	float SetMaxHealth(float NewMaxHealth) { MaxHealth = NewMaxHealth; return NewMaxHealth; }

	
		
};
