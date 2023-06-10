// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "KWJ_GameMode.generated.h"

namespace MatchState
{
	extern VR12_TEAM3PROJECT_API const FName Cooldown; // Match Diration has been reached. Dispaly winner and begin cooldown timer.

}

/**
 * 
 */
UCLASS()
class VR12_TEAM3PROJECT_API AKWJ_GameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	virtual void MonsterEliminated(class AKWJ_BaseCharacter* ElimmedCharacter, class AKWJ_MonsterCharacter* VictimMonster, class AKWJ_PlayerController AttackerController);

	virtual void Tick(float DeltaTime) override;

	void PlayerLeftGame(class AKWJ_PlayerState* PlayerLeaving);

	UPROPERTY(EditDefaultsOnly)
	float WaitingTime = 30.f;

	UPROPERTY(EditDefaultsOnly)
	float MatchTime = 120.f;

	UPROPERTY(EditDefaultsOnly)
	float CooldownTime = 10.f;

	float LevelStartingTime = 0.f;

	UFUNCTION()
	void RenewTeamState();

protected:
	
	virtual void OnMatchStateSet() override;

private:
	float CountdownTime = 0.f;

public:
	FORCEINLINE float GetCountdownTime() const { return CountdownTime; }
};
