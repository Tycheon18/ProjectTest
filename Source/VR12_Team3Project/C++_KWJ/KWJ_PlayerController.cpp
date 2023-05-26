// Fill out your copyright notice in the Description page of Project Settings.


#include "KWJ_PlayerController.h"
#include "KWJ_HUD.h"
#include "KWJ_CharacterStateWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "KWJ_BaseCharacter.h"
#include "Net/UnrealNetwork.h"
#include "KWJ_GameMode.h"
#include "KWJ_Announcement.h"
#include "Kismet/GameplayStatics.h"


AKWJ_PlayerController::AKWJ_PlayerController()
{
}

void AKWJ_PlayerController::BeginPlay()
{
	Super::BeginPlay();


	PlayerHUD = Cast<AKWJ_HUD>(GetHUD());
	ServerCheckMatchState();

}

void AKWJ_PlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AKWJ_PlayerController, MatchState);
}

void AKWJ_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetHUDTime();
	CheckTimeSync(DeltaTime);
	
}

void AKWJ_PlayerController::SetHUDHp(float CurHp, float MaxHp)
{
	PlayerHUD = PlayerHUD == nullptr ? Cast<AKWJ_HUD>(GetHUD()) : PlayerHUD;
	
	bool bHUDValid = PlayerHUD &&
		PlayerHUD->CharacterStateWidget &&
		PlayerHUD->CharacterStateWidget->HpBar &&
		PlayerHUD->CharacterStateWidget->HpText;
	if (bHUDValid)
	{
		const float HpPercent = CurHp / MaxHp; 
		PlayerHUD->CharacterStateWidget->HpBar->SetPercent(HpPercent);
		FString HpText = FString::Printf(TEXT("%d/%d"), FMath::CeilToInt(CurHp), FMath::CeilToInt(MaxHp));
		PlayerHUD->CharacterStateWidget->HpText->SetText(FText::FromString(HpText));
	}
	else
	{
		bInitializeCharacterOverlay = true;
		HUDHp = CurHp;
		HUDMaxHp = MaxHp;
	}
}

void AKWJ_PlayerController::SetHUDScore(float Score)
{
	PlayerHUD = PlayerHUD == nullptr ? Cast<AKWJ_HUD>(GetHUD()) : PlayerHUD;
		
	bool bHUDValid = PlayerHUD &&
		PlayerHUD->CharacterStateWidget &&
		PlayerHUD->CharacterStateWidget->ScoreAmount;
	if (bHUDValid)
	{
		FString ScoreText = FString::Printf(TEXT("%d"), FMath::FloorToInt(Score));
		PlayerHUD->CharacterStateWidget->ScoreAmount->SetText(FText::FromString(ScoreText));
	}
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
		if (CountdownTime < 0.f)
		{
			PlayerHUD->CharacterStateWidget->MatchCountdownText->SetText(FText());
			return;
		}
		int32 Minutes = FMath::FloorToInt(CountdownTime / 60.f);
		int32 Seconds = CountdownTime - (Minutes * 60);

		FString CountdownText = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
		PlayerHUD->CharacterStateWidget->MatchCountdownText->SetText(FText::FromString(CountdownText));
	}
}

void AKWJ_PlayerController::SetHUDAnnouncementCountdown(float CountdownTime)
{
	PlayerHUD = PlayerHUD == nullptr ? Cast<AKWJ_HUD>(GetHUD()) : PlayerHUD;
	bool bHUDValid = PlayerHUD &&
		PlayerHUD->Announcement &&
		PlayerHUD->Announcement->WaitingTime;
	if (bHUDValid)
	{
		if (CountdownTime < 0.f)
		{
			PlayerHUD->Announcement->WaitingTime->SetText(FText());
			return;
		}
		int32 Minutes = FMath::FloorToInt(CountdownTime / 60.f);
		int32 Seconds = CountdownTime - (Minutes * 60);

		FString CountdownText = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
		PlayerHUD->Announcement->WaitingTime->SetText(FText::FromString(CountdownText));
	}
}

void AKWJ_PlayerController::SetHUDTime()
{
	float TimeLeft = 0.f;
	if (MatchState == MatchState::WaitingToStart) TimeLeft = WaitingTime - GetServerTime() + LevelStartingTime;
	else if (MatchState == MatchState::InProgress) TimeLeft = WaitingTime + MatchTime - GetServerTime() + LevelStartingTime;
	else if (MatchState == MatchState::Cooldown) TimeLeft = CooldownTime + WaitingTime + MatchTime - GetServerTime() + LevelStartingTime;
	uint32 SecondsLeft = FMath::CeilToInt(TimeLeft);

	if (HasAuthority())
	{
		Team3GameMode = Team3GameMode == nullptr ? Cast<AKWJ_GameMode>(UGameplayStatics::GetGameMode(this)) : Team3GameMode;
		if (Team3GameMode)
		{
			SecondsLeft = FMath::CeilToInt(Team3GameMode->GetCountdownTime());
		}
	}
	if (CountdownInt != SecondsLeft)
	{
		if (MatchState == MatchState::WaitingToStart)
		{
			SetHUDAnnouncementCountdown(TimeLeft);
		}
		if (MatchState == MatchState::InProgress)
		{
			SetHUDMatchCountdown(TimeLeft);
		}
	}

	CountdownInt = SecondsLeft;
}

void AKWJ_PlayerController::PollInit()
{
	if (CharacterStateWidget == nullptr)
	{
		if (PlayerHUD && PlayerHUD->CharacterStateWidget)
		{
			CharacterStateWidget = PlayerHUD->CharacterStateWidget;
			if (CharacterStateWidget)
			{
				SetHUDHp(HUDHp, HUDMaxHp);
			}
		}
	}
}


void AKWJ_PlayerController::OnPossess(APawn* InPawn)
{
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

void AKWJ_PlayerController::OnMatchStateSet(FName State)
{
	MatchState = State;

	if (MatchState == MatchState::InProgress)
	{
		HandleMatchHasStarted();
	}
	else if (MatchState == MatchState::Cooldown)
	{
		HandleCooldown();
	}
}

void AKWJ_PlayerController::HandleMatchHasStarted()
{
	PlayerHUD = PlayerHUD == nullptr ? Cast<AKWJ_HUD>(GetHUD()) : PlayerHUD;
	if (PlayerHUD)
	{
		PlayerHUD->AddCharacterStateWidget();
		if (PlayerHUD->Announcement)
		{
			PlayerHUD->Announcement->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void AKWJ_PlayerController::HandleCooldown()
{
	PlayerHUD = PlayerHUD == nullptr ? Cast<AKWJ_HUD>(GetHUD()) : PlayerHUD;
	if (PlayerHUD)
	{
		PlayerHUD->CharacterStateWidget->RemoveFromParent();
		bool bHUDValid = PlayerHUD->Announcement &&
			PlayerHUD->Announcement->AnnouncementText &&
			PlayerHUD->Announcement->InfoText;
		if (bHUDValid)
		{
			PlayerHUD->Announcement->SetVisibility(ESlateVisibility::Visible);
			FString AnnouncementText("New Match Starts In:");
			PlayerHUD->Announcement->AnnouncementText->SetText(FText::FromString(AnnouncementText));
			PlayerHUD->Announcement->InfoText->SetText(FText());
		}
	}
	AKWJ_BaseCharacter* PlayerCharacter = Cast<AKWJ_BaseCharacter>(GetPawn());
	if (PlayerCharacter)
	{
		PlayerCharacter->bDisableGameplay = true;
	}
}

void AKWJ_PlayerController::OnRep_MatchState()
{
	if(MatchState == MatchState::InProgress)
	{
		HandleMatchHasStarted();
	}
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

void AKWJ_PlayerController::ServerCheckMatchState_Implementation()
{
	AKWJ_GameMode* PlayerGameMode = Cast<AKWJ_GameMode>(UGameplayStatics::GetGameMode(this));
	if (PlayerGameMode)
	{
		WaitingTime = PlayerGameMode->WaitingTime;
		MatchTime = PlayerGameMode->MatchTime;
		CooldownTime = PlayerGameMode->CooldownTime;
		LevelStartingTime = PlayerGameMode->LevelStartingTime;
		MatchState = PlayerGameMode->GetMatchState();
		ClientJoinMidgame(MatchState, WaitingTime, MatchTime, CooldownTime, LevelStartingTime);

	}
}

void AKWJ_PlayerController::ClientJoinMidgame_Implementation(FName StateOfMatch, float Waiting, float Match, float Cooldown ,float StartingTime)	 
{
	WaitingTime = Waiting;
	MatchTime = Match;
	CooldownTime = Cooldown;
	LevelStartingTime = StartingTime;
	MatchState = StateOfMatch;
	OnMatchStateSet(MatchState);

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
