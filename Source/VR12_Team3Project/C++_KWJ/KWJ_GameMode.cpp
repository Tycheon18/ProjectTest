// Fill out your copyright notice in the Description page of Project Settings.


#include "KWJ_GameMode.h"
#include "KWJ_BaseCharacter.h"
#include "KWJ_GameState.h"
#include "KWJ_PlayerState.h"
#include "KWJ_MonsterCharacter.h"
#include "KWJ_PlayerController.h"

namespace MatchState
{
	const FName Cooldown = FName("Cooldown");
}


void AKWJ_GameMode::MonsterEliminated(AKWJ_BaseCharacter* ElimmedCharacter, AKWJ_MonsterCharacter* VictimMonster, AKWJ_PlayerController AttackerController)
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

void AKWJ_GameMode::PlayerLeftGame(class AKWJ_PlayerState* PlayerLeaving)
{
	if (PlayerLeaving == nullptr) return;
	AKWJ_GameState* ThisGameState = GetGameState<AKWJ_GameState>();
	if (ThisGameState && ThisGameState->TopScoringPlayers.Contains(PlayerLeaving))
	{
		ThisGameState->TopScoringPlayers.Remove(PlayerLeaving);
	}
	AKWJ_BaseCharacter* CharacterLeaving = Cast<AKWJ_BaseCharacter>(PlayerLeaving->GetPawn());
	if (CharacterLeaving)
	{
		//CharacterLeaving->Elim(true);
	}
}

void AKWJ_GameMode::OnMatchStateSet()
{
	Super::OnMatchStateSet();

	//for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	//{
	//	AKWJ_PlayerController* Player = Cast<AKWJ_PlayerController>(*It);
	//	if (Player)
	//	{
	//		Player->OnMatchStateSet(MatchState);
	//	}
	//}
}
