// Fill out your copyright notice in the Description page of Project Settings.


#include "KWJ_LobbyGameMode.h"
#include "GameFramework/GameStateBase.h"

void AKWJ_LobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
	if (NumberOfPlayers == 2)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			bUseSeamlessTravel = true;
			//World->ServerTravel(FString("");
		}
	}
}
