// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KWJ_TeamStateWidget.generated.h"

/**
 * 
 */
UCLASS()
class VR12_TEAM3PROJECT_API UKWJ_TeamStateWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PlayerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* HpBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* StaminaBar;

	UFUNCTION()
	void SetHp(float CurHp, float MaxHp);

	UFUNCTION()
	void SetStamina(float CurStamina, float MaxStamina);
};
