// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "KWJ_GameState.generated.h"

/**
 * 
 */
UCLASS()
class VR12_TEAM3PROJECT_API AKWJ_GameState : public AGameState
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated)
	TArray<class AKWJ_PlayerState*	> TopScoringPlayers;
};
