// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "KWJ_PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class VR12_TEAM3PROJECT_API AKWJ_PlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	virtual void OnRep_Score() override;
	void AddToScore(float ScoreAmount);
private:
	class AKWJ_BaseCharacter* Character;
	class AKWJ_PlayerController* Controller;
};
