// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "WeaponBaseClass.generated.h"

class UStaticMesh;
class UTexture2D;
class UWeaponComponent;
class ABasicCharacter;

UCLASS(Blueprintable, BlueprintType, DefaultToInstanced)
class VR12_TEAM3PROJECT_API AWeaponBaseClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBaseClass();
	AWeaponBaseClass(const class FObjectInitializer& ObjectInitializer);

	void SetOwningPawn(ABasicCharacter* NewOwner);
	void AttachMeshToPawn();
	void OnEquip(const AWeaponBaseClass* LastWeapon);
	

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

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	class UBoxComponent* WeaponCollision;

protected:
	class ABasicCharacter* MyPawn;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
