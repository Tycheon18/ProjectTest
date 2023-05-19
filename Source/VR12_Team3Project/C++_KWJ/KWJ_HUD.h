// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "KWJ_HUD.generated.h"

/**
 * 
 */
UCLASS()
class VR12_TEAM3PROJECT_API AKWJ_HUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void DrawHUD() override;

	UPROPERTY(EditAnywhere, Category = "PlayerState")
	TSubclassOf<class UUserWidget> CharacterStateWidgetClass;


	class UKWJ_CharacterStateWidget* CharacterStateWidget;

protected:
	virtual void BeginPlay() override;
	void AddCharacterStateWidget();

private:
	

};
