// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageComp.h"
#include "DamageableInterface.h"

// Sets default values for this component's properties
UDamageComp::UDamageComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UDamageComp::BeginPlay()
{
	Super::BeginPlay();

	UPrimitiveComponent* Collision = nullptr;

	if (CollisionCompClass)
	{
		Collision = Cast<UPrimitiveComponent>(GetOwner()->GetComponentByClass(CollisionCompClass));
	}
	else
	{
		Collision = GetOwner()->FindComponentByClass<UPrimitiveComponent>();
	}
	if (!Collision)
	{
		Collision = GetOwner()->FindComponentByClass<UPrimitiveComponent>();
	}
	
	if (!Collision)
	{
		UE_LOG(LogTemp, Warning, TEXT("DamageDealer: Aucun composant de collision trouvé sur  %s"), *GetOwner()->GetName());
		return;
	}

	Collision->OnComponentBeginOverlap.AddDynamic(this, &UDamageComp::OnBeginOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &UDamageComp::OnEndOverlap);

	GetWorld()->GetTimerManager().SetTimer(
		DamageTimer,
		this,
		&UDamageComp::DealDamageTick,
		DamageInterval,
		true);
}

void UDamageComp::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 BodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == GetOwner())
	{
		return;
	}

	if (OtherActor->GetClass()->ImplementsInterface(UDamageableInterface::StaticClass()))
	{
		OverlappingActors.Add(OtherActor);

		UE_LOG(LogTemp, Warning, TEXT("[DamageDealer] %s a détecté un overlap avec %s (Damageable)"),
	*GetOwner()->GetName(),
	*OtherActor->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[DamageDealer] %s a détecté %s MAIS il n'implémente pas l'interface !"),
	*GetOwner()->GetName(),
	*OtherActor->GetName());
	}
}

void UDamageComp::OnEndOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 BodyIndex)
{
	if (OtherActor)
		OverlappingActors.Remove(OtherActor);
}

void UDamageComp::DealDamageTick()
{
	const float Damage = DPS * DamageInterval;

	for (AActor* Actor : OverlappingActors)
	{
		if (!Actor) continue;

		UE_LOG(LogTemp, Warning, TEXT("[DamageDealer] %s inflige %f dégâts à %s"),
	*GetOwner()->GetName(),
	Damage,
	*Actor->GetName());

		if (Actor->GetClass()->ImplementsInterface(UDamageableInterface::StaticClass()))
		{
			IDamageableInterface::Execute_ApplyDamage(Actor, Damage);
		}
	}
}


