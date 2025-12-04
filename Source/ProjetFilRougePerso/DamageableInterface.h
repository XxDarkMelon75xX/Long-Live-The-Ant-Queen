// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DamageableInterface.generated.h"

// This class does not need to be modified.
// UINTERFACE(MinimalAPI)
UINTERFACE(Blueprintable)
class UDamageableInterface : public UInterface
{
	GENERATED_BODY()
};

class PROJETFILROUGEPERSO_API IDamageableInterface : public IInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Damage")
	void ApplyDamage(float Damage);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Damage")
	void ApplyHeal(float HealAmount);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Damage")
	bool IsDead() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Damage")
	void OnDeath();

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
