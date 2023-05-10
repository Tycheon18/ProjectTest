// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WeaponBase.generated.h"

class UStaticMesh;
class UTexture2D;
class UWeaponComponent;

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class VR12_TEAM3PROJECT_API UWeaponBase : public UObject
{
	GENERATED_BODY()

public:

	UWeaponBase();	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		FText UseActionText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		UStaticMesh* PickupMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		FText ItemDisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (MultiLine = true))
		FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (ClampMin = 0.0))
		float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (ClampMin = 0))
		int32 Ammo;
};
