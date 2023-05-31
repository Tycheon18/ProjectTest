// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WeaponBaseClass.h"
#include "KWJ_BaseCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLeftGame);

UCLASS()
class VR12_TEAM3PROJECT_API AKWJ_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKWJ_BaseCharacter();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated)
	bool bDisableGameplay = false; // Check to blueprint input compatible

	UFUNCTION(Server, Reliable)
		void ServerLeaveGame();

	FOnLeftGame OnLeftGame;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void UpdateHUDHp();
	

	void PollInit();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* OverheadWidget;

	UPROPERTY(EditAnywhere,  Category = "PlayerState")
	float MaxHp = 100.f;

	UPROPERTY(ReplicatedUsing = OnRep_Health, VisibleAnywhere,Category = "PlayerState")
	float CurHp = 100.f;

	UFUNCTION()
	void OnRep_Health();

	UPROPERTY(Replicated)
	class AWeaponBaseClass* Weapon;

	UPROPERTY()
	class AKWJ_PlayerController* PlayerController;

	class AKWJ_PlayerState* PlayerState;

	bool bLeftGame = false;




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE float GetCurHp() const { return CurHp; }
	FORCEINLINE float GetMaxHp() const { return MaxHp; }
};
