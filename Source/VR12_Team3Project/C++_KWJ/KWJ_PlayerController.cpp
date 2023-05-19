// Fill out your copyright notice in the Description page of Project Settings.


#include "KWJ_PlayerController.h"
#include "KWJ_HUD.h"
#include "KWJ_CharacterStateWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"


AKWJ_PlayerController::AKWJ_PlayerController()
{
}

void AKWJ_PlayerController::SetHUDHp(float CurHp, float MaxHp)
{
}

void AKWJ_PlayerController::SetHUDScore(float Score)
{
}

void AKWJ_PlayerController::SetHUDWeaponAmmo(int32 Ammo)
{
}

void AKWJ_PlayerController::SetHUDCarriedAmmo(int32 Ammo)
{
}

void AKWJ_PlayerController::SetHUDMatchCountdown(float CountdownTime)
{
	/*PlayerHUD = PlayerHUD == nullptr ? Cast<AKWJ_HUD>(GetHUD()) : PlayerHUD;
	bool bHUDValid = PlayerHUD &&
		PlayerHUD->CharacterOverlay &&
		PlayerHUD->CharacterOverlay->MatchCountdownTest;
	if (bHUDValid)
	{
		int32 Minutes = FMath::FloorToInt(CountdownTime / 60.f);
		int32 Seconds = CountdownTime - (Minutes * 60);

		FString CountdownText;
		PlayerHUD->CharacterOverlay->ScoreAmount->SetText(FText::FromString(ScoreText));
	}*/
}

void AKWJ_PlayerController::OnPossess(APawn* InPawn)
{
}

void AKWJ_PlayerController::BeginPlay()
{
}
