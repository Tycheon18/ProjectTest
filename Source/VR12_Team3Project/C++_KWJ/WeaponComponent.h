// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class AWeaponBaseClass;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VR12_TEAM3PROJECT_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	bool AddWeapon(class AWeaponBaseClass* Weapon);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	AWeaponBaseClass* FirstWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	AWeaponBaseClass* SecondWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WeaponInventory")
	int32 Capacity;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	TArray<class AWeaponBaseClass*> Items;



protected:


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
