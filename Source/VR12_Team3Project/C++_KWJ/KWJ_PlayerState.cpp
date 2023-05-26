// Fill out your copyright notice in the Description page of Project Settings.


#include "KWJ_PlayerState.h"
#include "KWJ_BaseCharacter.h"
#include "KWJ_PlayerController.h"
#include "Net/UnrealNetwork.h"

void AKWJ_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AKWJ_PlayerState, Defeats);
}
void AKWJ_PlayerState::AddToScore(float ScoreAmount)
{
	SetScore(GetScore() + ScoreAmount);
	Character = Character == nullptr ? Cast<AKWJ_BaseCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<AKWJ_PlayerController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHUDScore(ScoreAmount);
		}
	}
}

void AKWJ_PlayerState::OnRep_Score()
{
	Super::OnRep_Score();

	Character = Character == nullptr ? Cast<AKWJ_BaseCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<AKWJ_PlayerController>(Character->Controller) : Controller;	  
		if (Controller)
		{
			Controller->SetHUDScore(Score);
		}
	}
}


void AKWJ_PlayerState::AddToDefeats(int32 DefeatsAmount)
{
	Defeats += DefeatsAmount;
	Character = Character == nullptr ? Cast<AKWJ_BaseCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<AKWJ_PlayerController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHUDDefeats(DefeatsAmount);
		}
	}
}

void AKWJ_PlayerState::OnRep_Defeats()
{
	Character = Character == nullptr ? Cast<AKWJ_BaseCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<AKWJ_PlayerController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHUDDefeats(Defeats);
		}
	}
}


