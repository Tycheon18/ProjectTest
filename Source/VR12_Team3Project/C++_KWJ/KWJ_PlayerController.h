// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KWJ_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class VR12_TEAM3PROJECT_API AKWJ_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AKWJ_PlayerController();

	void SetHUDHp(float CurHp, float MaxHp);
	void SetHUDScore(float Score);
	void SetHUDWeaponAmmo(int32 Ammo);
	void SetHUDCarriedAmmo(int32 Ammo);
	void SetHUDMatchCountdown(float CountdownTime);
	virtual void OnPossess(APawn* InPawn) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY();
	class AKWJ_HUD* PlayerHUD;
};
