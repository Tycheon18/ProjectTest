// Fill out your copyright notice in the Description page of Project Settings.


#include "KWJ_PlayerState.h"
#include "KWJ_BaseCharacter.h"
#include "KWJ_PlayerController.h"

void AKWJ_PlayerState::AddToScore(float ScoreAmount)
{
	Score += ScoreAmount;
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


