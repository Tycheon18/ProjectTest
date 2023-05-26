// Fill out your copyright notice in the Description page of Project Settings.


#include "KWJ_GameState.h"
#include "Net/UnrealNetwork.h"

void AKWJ_GameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AKWJ_GameState, TopScoringPlayers);
}
