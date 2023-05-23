// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameModeBase.h"
#include "KWJ_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class VR12_TEAM3PROJECT_API AKWJ_GameModeBase : public AMainGameModeBase
{
	GENERATED_BODY()
	
public:
	AKWJ_GameModeBase();
	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;


private:
	float CountdownTime = 0.f;
};
