// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KWJ_ReturnToMainMenu.generated.h"

/**
 * 
 */
UCLASS()
class VR12_TEAM3PROJECT_API UKWJ_ReturnToMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void MenuSetup();
	void MenuTearDown();

protected:
	virtual bool Initialize() override;

	UFUNCTION()
	void OnDestroySession(bool bWasSuccessful);


	void OnPlayerLeftGame();
private:
	UPROPERTY(meta = (BindWidget))
	class UButton* ReturnButton;

	UFUNCTION()
	void ReturnButtonClicked();

	UPROPERTY()
	class UMultiplayerSessionsSubsystem* MultiplayerSessionsSubsystem;

	class APlayerController* PlayerController;
};
