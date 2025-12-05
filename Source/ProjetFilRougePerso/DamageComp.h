// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJETFILROUGEPERSO_API UDamageComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamageComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float DPS = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float DamageInterval =  0.2f;

	UPROPERTY(EditAnywhere, Category = "Damage")
	TSubclassOf<UPrimitiveComponent> CollisionCompClass;

private:
	UFUNCTION()
	void OnBeginOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 BodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 BodyIndex);

	void DealDamageTick();

	TSet<AActor*> OverlappingActors;

	FTimerHandle DamageTimer;
	


		
};
