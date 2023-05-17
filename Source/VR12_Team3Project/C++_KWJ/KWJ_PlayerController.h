// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KWJ_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class VR12_TEAM3PROJECT_API AKWJ_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AKWJ_PlayerController();

	void SetHUDHp(float CurHp, float MaxHp);
};
