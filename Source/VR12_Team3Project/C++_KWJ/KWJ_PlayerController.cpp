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
	PlayerHUD = PlayerHUD == nullptr ? Cast<AKWJ_HUD>(GetHUD()) : PlayerHUD;
	
	bool bHUDValid = PlayerHUD && PlayerHUD->CharacterStateWidget &&
		PlayerHUD->CharacterStateWidget->HpBar &&
		PlayerHUD->CharacterStateWidget->HpText;
	if (bHUDValid)
	{
		const float HpPercent = CurHp / MaxHp; 
		PlayerHUD->CharacterStateWidget->HpBar->SetPercent(HpPercent);
		FString HpText = FString::Printf(TEXT("%d/%d"), FMath::CeilToInt(CurHp), FMath::CeilToInt(MaxHp));
		PlayerHUD->CharacterStateWidget->HpText->SetText(FText::FromString(HpText));
	}
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
	PlayerHUD = PlayerHUD == nullptr ? Cast<AKWJ_HUD>(GetHUD()) : PlayerHUD;
	bool bHUDValid = PlayerHUD &&
		PlayerHUD->CharacterStateWidget &&
		PlayerHUD->CharacterStateWidget->MatchCountdownText;
	if (bHUDValid)
	{
		int32 Minutes = FMath::FloorToInt(CountdownTime / 60.f);
		int32 Seconds = CountdownTime - (Minutes * 60);

		FString CountdownText = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
		PlayerHUD->CharacterStateWidget->MatchCountdownText->SetText(FText::FromString(CountdownText));
	}
}

void AKWJ_PlayerController::OnPossess(APawn* InPawn)
{
}

void AKWJ_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetHUDTime();
	CheckTimeSync(DeltaTime);
}

float AKWJ_PlayerController::GetServerTime()
{
	return GetWorld()->GetTimeSeconds() + ClientServerDelta;
}

void AKWJ_PlayerController::ReceivedPlayer()
{
	Super::ReceivedPlayer();
	if (IsLocalController())
	{
		ServerRequestServerTime(GetWorld()->GetTimeSeconds());
	}
}

void AKWJ_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlayerHUD = Cast<AKWJ_HUD>(GetHUD());

}



void AKWJ_PlayerController::SetHUDTime()
{
	uint32 SecondsLeft = FMath::CeilToInt(MatchTime -GetServerTime());
	if (CountdownInt != SecondsLeft)
	{
		SetHUDMatchCountdown(MatchTime - GetServerTime());
	}


	CountdownInt = SecondsLeft;
}

void AKWJ_PlayerController::CheckTimeSync(float DeltaTime)
{

	TimeSyncRunningTime += DeltaTime;
	if (IsLocalController() && TimeSyncRunningTime > TimeSyncFrequency)
	{
		ServerRequestServerTime(GetWorld()->GetTimeSeconds());
		TimeSyncRunningTime = 0.f;
	}
}

void AKWJ_PlayerController::ClientReportServerTime_Implementation(float TimeofClientRequest, float TimeServerReceivedClientRequest)
{
	float RoundTripTime = GetWorld()->GetTimeSeconds() - TimeofClientRequest;
	float CurrentServerTime = TimeServerReceivedClientRequest + (0.5f * RoundTripTime);
	ClientServerDelta = CurrentServerTime - GetWorld()->GetTimeSeconds();
}

void AKWJ_PlayerController::ServerRequestServerTime_Implementation(float TimeOfClientRequest)
{
	float ServerTimeOfReceipt = GetWorld()->GetTimeSeconds();
	ClientReportServerTime(TimeOfClientRequest, ServerTimeOfReceipt);
}
