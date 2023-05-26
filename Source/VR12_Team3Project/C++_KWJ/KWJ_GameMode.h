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
	AKWJ_GameMode();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	float WaitingTime = 30.f;

	UPROPERTY(EditDefaultsOnly)
	float MatchTime = 120.f;

	UPROPERTY(EditDefaultsOnly)
	float CooldownTime = 10.f;

	float LevelStartingTime = 0.f;

protected:
	virtual void BeginPlay() override;

	virtual void OnMatchStateSet() override;

private:
	float CountdownTime = 0.f;

public:
	FORCEINLINE float GetCountdownTime() const { return CountdownTime; }
};
