// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KWJ_CharacterStateWidget.generated.h"

/**
 * 
 */
UCLASS()
class VR12_TEAM3PROJECT_API UKWJ_CharacterStateWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BIndWidget))
	class UProgressBar* HpBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BIndWidget))
	class UTextBlock* HpText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BIndWidget))
	class UTextBlock* GoldText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BIndWidget))
	class UTextBlock* ScoreAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BIndWidget))
	class UTextBlock* DefeatsAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BIndWidget))
	class UTextBlock* MatchCountdownText;
};
