// Fill out your copyright notice in the Description page of Project Settings.


#include "KWJ_ReturnToMainMenu.h"
#include "KWJ_BaseCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Components/Button.h"
#include "../MultiplayerSessions/MultiplayerSessionsSubsystem.h"
#include "GameFramework/GameModeBase.h"

void UKWJ_ReturnToMainMenu::MenuSetup()
{
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	bIsFocusable = true;

	UWorld* World = GetWorld();
	if (World)
	{
		PlayerController = PlayerController == nullptr ? World->GetFirstPlayerController() : PlayerController;
		if (PlayerController)
		{
			FInputModeGameAndUI InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);
		}
	}

	if (ReturnButton && !ReturnButton->OnClicked.IsBound())
	{
		ReturnButton->OnClicked.AddDynamic(this, &UKWJ_ReturnToMainMenu::ReturnButtonClicked);
	}
	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();

	}
}

bool UKWJ_ReturnToMainMenu::Initialize()
{
	if(!Super::Initialize())
	{
		return false;
	}

	if (ReturnButton)
	{
		ReturnButton->OnClicked.AddDynamic(this, &UKWJ_ReturnToMainMenu::ReturnButtonClicked);
	}
	
	return true;
}

void UKWJ_ReturnToMainMenu::OnDestroySession(bool bWasSuccessful)
{
	if (!bWasSuccessful)
	{
		ReturnButton->SetIsEnabled(true);
		return;
	}

	UWorld* World = GetWorld();
	if (World)
	{
		AGameModeBase* GameMode = World->GetAuthGameMode<AGameModeBase>();
		if (GameMode)
		{
			GameMode->ReturnToMainMenuHost();
		}
		else
		{
			PlayerController = PlayerController == nullptr ? World->GetFirstPlayerController() : PlayerController;
			if(PlayerController)
			{ 
				PlayerController->ClientReturnToMainMenuWithTextReason(FText());
			}
		}
	}
}


void UKWJ_ReturnToMainMenu::MenuTearDown()
{
	RemoveFromParent();
	UWorld* World = GetWorld();
	if (World)
	{
		PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeGameOnly InputModeData;
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(false);
		}
	}

	if (ReturnButton && ReturnButton->OnClicked.IsBound())
	{
		ReturnButton->OnClicked.RemoveDynamic(this, &UKWJ_ReturnToMainMenu::ReturnButtonClicked);
	}
	if (MultiplayerSessionsSubsystem && MultiplayerSessionsSubsystem->MultiplayerOnDestroySessionComplete.IsBound())
	{
		MultiplayerSessionsSubsystem->MultiplayerOnDestroySessionComplete.RemoveDynamic(this, &UKWJ_ReturnToMainMenu::OnDestroySession);
	}
}

void UKWJ_ReturnToMainMenu::ReturnButtonClicked()
{
	ReturnButton->SetIsEnabled(false);

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* FirstPlayerController = World->GetFirstPlayerController(); 
		if (FirstPlayerController)
		{
			AKWJ_BaseCharacter* BaseCharacter = Cast<AKWJ_BaseCharacter>(FirstPlayerController->GetPawn());
			if (BaseCharacter)
			{
				BaseCharacter->ServerLeaveGame();
				BaseCharacter->OnLeftGame.AddDynamic(this, &UKWJ_ReturnToMainMenu::OnPlayerLeftGame);
			}
			else
			{
				ReturnButton->SetIsEnabled(true);
			}
		}
	}

}

void UKWJ_ReturnToMainMenu::OnPlayerLeftGame()
{
	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->DestroySession();
	}
}