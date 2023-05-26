// Fill out your copyright notice in the Description page of Project Settings.


#include "KWJ_GameMode.h"
#include "KWJ_PlayerController.h"

namespace MatchState
{
	const FName Cooldown = FName("Cooldown");
}

AKWJ_GameMode::AKWJ_GameMode()
{
}

void AKWJ_GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MatchState == MatchState::WaitingToStart)
	{
		CountdownTime = WaitingTime - GetWorld()->GetTimeSeconds() + LevelStartingTime;
		if (CountdownTime <= 0.f)
		{
			StartMatch();
		}
	}
	else if (MatchState == MatchState::InProgress)
	{
		CountdownTime = WaitingTime + MatchTime - GetWorld()->GetTimeSeconds() + LevelStartingTime;
		if (CountdownTime <= 0.f)
		{
			SetMatchState(MatchState::Cooldown);
		}
	}
	else if (MatchState == MatchState::Cooldown)
	{
		CountdownTime = CooldownTime + WaitingTime + MatchTime - GetWorld()->GetTimeSeconds() + LevelStartingTime;
		if (CountdownTime <= 0.f)
		{

		}
	}
}

void AKWJ_GameMode::BeginPlay()
{
}

void AKWJ_GameMode::OnMatchStateSet()
{
	Super::OnMatchStateSet();

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		AKWJ_PlayerController* Player = Cast<AKWJ_PlayerController>(*It);
		if (Player)
		{
			Player->OnMatchStateSet(MatchState);
		}
	}
}
