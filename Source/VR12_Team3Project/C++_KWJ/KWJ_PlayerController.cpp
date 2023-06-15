// Fill out your copyright notice in the Description page of Project Settings.


#include "KWJ_PlayerController.h"
#include "KWJ_HUD.h"
#include "KWJ_CharacterStateWidget.h"
#include "KWJ_PlayerState.h"
#include "Components/VerticalBox.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "KWJ_BaseCharacter.h"
#include "Net/UnrealNetwork.h"
#include "KWJ_GameMode.h"
#include "KWJ_Announcement.h"
#include "Kismet/GameplayStatics.h"
#include "KWJ_GameState.h"
#include "KWJ_ReturnToMainMenu.h"
#include "KWJ_TeamStateWidget.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"


AKWJ_PlayerController::AKWJ_PlayerController()
{
}

void AKWJ_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlayerName = PlayerState->GetPlayerName();
	PlayerHUD = Cast<AKWJ_HUD>(GetHUD());
	ServerCheckMatchState();
}


void AKWJ_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AKWJ_BaseCharacter* PlayerCharacter = Cast<AKWJ_BaseCharacter>(InPawn);
	if (PlayerCharacter)
	{
		SetHUDHp(PlayerCharacter->GetCurHp(), PlayerCharacter->GetMaxHp());
	}
}

void AKWJ_PlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AKWJ_PlayerController, MatchState);
}

void AKWJ_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetHUDTime();
	CheckTimeSync(DeltaTime);


	
}

void AKWJ_PlayerController::SetHUDHp(float CurHp, float MaxHp)
{
	PlayerHUD = PlayerHUD == nullptr ? Cast<AKWJ_HUD>(GetHUD()) : PlayerHUD;

	bool bHUDValid = PlayerHUD &&
		PlayerHUD->CharacterStateWidget &&
		PlayerHUD->CharacterStateWidget->HpBar &&
		PlayerHUD->CharacterStateWidget->HpText;
	if (bHUDValid)
	{

		const float HpPercent = CurHp / MaxHp; 
	
		PlayerHUD->CharacterStateWidget->HpBar->SetPercent(HpPercent);
		FString HpText = FString::Printf(TEXT("%d/%d"), FMath::CeilToInt(CurHp), FMath::CeilToInt(MaxHp));
		PlayerHUD->CharacterStateWidget->HpText->SetText(FText::FromString(HpText));

	}
	else
	{

		bInitializeCharacterOverlay = true;
		HUDHp = CurHp;
		HUDMaxHp = MaxHp;
	}
}

void AKWJ_PlayerController::SetHUDStamina(float CurStamina, float MaxStamina)
{
	PlayerHUD = PlayerHUD == nullptr ? Cast<AKWJ_HUD>(GetHUD()) : PlayerHUD;

	bool bHUDValid = PlayerHUD &&
		PlayerHUD->CharacterStateWidget &&
		PlayerHUD->CharacterStateWidget->StaminaBar &&
		PlayerHUD->CharacterStateWidget->StaminaText;
	if (bHUDValid)
	{
		const float StaminaPercent = CurStamina / MaxStamina;
		PlayerHUD->CharacterStateWidget->StaminaBar->SetPercent(StaminaPercent);
		FString StaminaText = FString::Printf(TEXT("%d/%d"), FMath::CeilToInt(CurStamina), FMath::CeilToInt(MaxStamina));
		PlayerHUD->CharacterStateWidget->StaminaText->SetText(FText::FromString(StaminaText));
	}
	else
	{
		bInitializeCharacterOverlay = true;
		HUDStamina = CurStamina;
		HUDMaxStamina = MaxStamina;
	}
}

void AKWJ_PlayerController::SetHUDCoin(int Coin)
{
	PlayerHUD = PlayerHUD == nullptr ? Cast<AKWJ_HUD>(GetHUD()) : PlayerHUD;

	bool bHUDValid = PlayerHUD &&
		PlayerHUD->CharacterStateWidget &&
		PlayerHUD->CharacterStateWidget->StaminaBar &&
		PlayerHUD->CharacterStateWidget->StaminaText;
	if (bHUDValid)
	{
		FString CoinAmount = FString::Printf(TEXT("%d"), Coin);
		PlayerHUD->CharacterStateWidget->CoinAmount->SetText(FText::FromString(CoinAmount));
	}
	else
	{
		bInitializeCharacterOverlay = true;
		HUDCoin = Coin;
	}
}

void AKWJ_PlayerController::SetHUDScore(float Score)
{
	PlayerHUD = PlayerHUD == nullptr ? Cast<AKWJ_HUD>(GetHUD()) : PlayerHUD;
		
	bool bHUDValid = PlayerHUD &&
		PlayerHUD->CharacterStateWidget &&
		PlayerHUD->CharacterStateWidget->ScoreAmount;
	if (bHUDValid)
	{
		FString ScoreText = FString::Printf(TEXT("%d"), FMath::FloorToInt(Score));
		PlayerHUD->CharacterStateWidget->ScoreAmount->SetText(FText::FromString(ScoreText));
	}
}

void AKWJ_PlayerController::SetHUDDefeats(int32 Defeats)
{
	PlayerHUD = PlayerHUD == nullptr ? Cast<AKWJ_HUD>(GetHUD()) : PlayerHUD;

	bool bHUDValid = PlayerHUD &&
		PlayerHUD->CharacterStateWidget &&
		PlayerHUD->CharacterStateWidget->DefeatsAmount;
	if (bHUDValid)
	{
		FString ScoreText = FString::Printf(TEXT("%d"), Defeats);
		PlayerHUD->CharacterStateWidget->DefeatsAmount->SetText(FText::FromString(ScoreText));
	}
}

void AKWJ_PlayerController::SetHUDWeaponAmmo(int32 Ammo)
{
}

void AKWJ_PlayerController::SetHUDCarriedAmmo(int32 Ammo)
{
}

void AKWJ_PlayerController::SetHUDMatchCountdown(float CountdownTime)
{
	PlayerHUD = PlayerHUD == nullptr ? Cast<AKWJ_HUD>(GetHUD()) : PlayerHUD;
	bool bHUDValid = PlayerHUD &&
		PlayerHUD->CharacterStateWidget &&
		PlayerHUD->CharacterStateWidget->MatchCountdownText;
	if (bHUDValid)
	{
		if (CountdownTime < 0.f)
		{
			PlayerHUD->CharacterStateWidget->MatchCountdownText->SetText(FText());
			return;
		}
		int32 Minutes = FMath::FloorToInt(CountdownTime / 60.f);
		int32 Seconds = CountdownTime - (Minutes * 60);

		FString CountdownText = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
		PlayerHUD->CharacterStateWidget->MatchCountdownText->SetText(FText::FromString(CountdownText));
	}
}

void AKWJ_PlayerController::SetHUDAnnouncementCountdown(float CountdownTime)
{
	PlayerHUD = PlayerHUD == nullptr ? Cast<AKWJ_HUD>(GetHUD()) : PlayerHUD;
	bool bHUDValid = PlayerHUD &&
		PlayerHUD->Announcement &&
		PlayerHUD->Announcement->WaitingTime;
	if (bHUDValid)
	{
		if (CountdownTime < 0.f)
		{
			PlayerHUD->Announcement->WaitingTime->SetText(FText());
			return;
		}
		int32 Minutes = FMath::FloorToInt(CountdownTime / 60.f);
		int32 Seconds = CountdownTime - (Minutes * 60);

		FString CountdownText = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
		PlayerHUD->Announcement->WaitingTime->SetText(FText::FromString(CountdownText));
	}
}

void AKWJ_PlayerController::SetHUDTime()
{
	float TimeLeft = 0.f;
	if (MatchState == MatchState::WaitingToStart) TimeLeft = WaitingTime - GetServerTime() + LevelStartingTime;
	else if (MatchState == MatchState::InProgress) TimeLeft = WaitingTime + MatchTime - GetServerTime() + LevelStartingTime;
	else if (MatchState == MatchState::Cooldown) TimeLeft = CooldownTime + WaitingTime + MatchTime - GetServerTime() + LevelStartingTime;
	uint32 SecondsLeft = FMath::CeilToInt(TimeLeft);

	if (HasAuthority())
	{
		Team3GameMode = Team3GameMode == nullptr ? Cast<AKWJ_GameMode>(UGameplayStatics::GetGameMode(this)) : Team3GameMode;
		if (Team3GameMode)
		{
			SecondsLeft = FMath::CeilToInt(Team3GameMode->GetCountdownTime());
		}
	}
	if (CountdownInt != SecondsLeft)
	{
		if (MatchState == MatchState::WaitingToStart)
		{
			SetHUDAnnouncementCountdown(TimeLeft);
		}
		if (MatchState == MatchState::InProgress)
		{
			SetHUDMatchCountdown(TimeLeft);
		}
	}

	CountdownInt = SecondsLeft;
}

void AKWJ_PlayerController::PollInit()
{
	if (CharacterStateWidget == nullptr)
	{
		if (PlayerHUD && PlayerHUD->CharacterStateWidget)
		{
			CharacterStateWidget = PlayerHUD->CharacterStateWidget;
			if (CharacterStateWidget)
			{
				SetHUDHp(HUDHp, HUDMaxHp);
			}
		}
	}
}

float AKWJ_PlayerController::GetServerTime()
{
	return GetWorld()->GetTimeSeconds() + ClientServerDelta;
}

void AKWJ_PlayerController::ReceivedPlayer()
{
	Super::ReceivedPlayer();
	if (IsLocalController())
	{
		ServerRequestServerTime(GetWorld()->GetTimeSeconds());
	}
}

void AKWJ_PlayerController::OnMatchStateSet(FName State)
{
	MatchState = State;

	if (MatchState == MatchState::InProgress)
	{
		HandleMatchHasStarted();
	}
	else if (MatchState == MatchState::Cooldown)
	{
		HandleCooldown();
	}
}

void AKWJ_PlayerController::HandleMatchHasStarted()
{
	PlayerHUD = PlayerHUD == nullptr ? Cast<AKWJ_HUD>(GetHUD()) : PlayerHUD;
	if (PlayerHUD)
	{
		PlayerHUD->AddCharacterStateWidget();
		//if (PlayerHUD->Announcement)
		//{
		//	PlayerHUD->Announcement->SetVisibility(ESlateVisibility::Hidden);
		//}
	}
}

void AKWJ_PlayerController::HandleCooldown()
{
	PlayerHUD = PlayerHUD == nullptr ? Cast<AKWJ_HUD>(GetHUD()) : PlayerHUD;
	if (PlayerHUD)
	{
		PlayerHUD->CharacterStateWidget->RemoveFromParent();
		bool bHUDValid = PlayerHUD->Announcement &&
			PlayerHUD->Announcement->AnnouncementText &&
			PlayerHUD->Announcement->InfoText;
		if (bHUDValid)
		{
			PlayerHUD->Announcement->SetVisibility(ESlateVisibility::Visible);
			FString AnnouncementText("New Match Starts In:");
			PlayerHUD->Announcement->AnnouncementText->SetText(FText::FromString(AnnouncementText));

			AKWJ_GameState* GameState = Cast<AKWJ_GameState>(UGameplayStatics::GetGameState(this));
			AKWJ_PlayerState* MyPlayerState = GetPlayerState<AKWJ_PlayerState>();
			if (GameState && MyPlayerState)
			{
				TArray<AKWJ_PlayerState*> TopPlayers = GameState->TopScoringPlayers;
				FString InfoTextString;
				if (TopPlayers.Num() == 0)
				{
					InfoTextString = FString("There is no Winner.");
				}
				else if (TopPlayers.Num() == 1 && TopPlayers[0] == PlayerState)
				{
					InfoTextString = FString("You are the Winner!");
				}
				else if (TopPlayers.Num() == 1)
				{
					InfoTextString = FString::Printf(TEXT("Winner : \n%s"), *TopPlayers[0]->GetPlayerName());
				}
				else if (TopPlayers.Num() > 1)
				{
					InfoTextString = FString("Players tied for the Win :\n");
					for (auto TiedPlayer : TopPlayers)
					{
						InfoTextString.Append(FString::Printf(TEXT("%s\n"), *TiedPlayer->GetPlayerName()));
					}
				}

				PlayerHUD->Announcement->InfoText->SetText(FText::FromString(InfoTextString));
			}
		}
	}
	AKWJ_BaseCharacter* PlayerCharacter = Cast<AKWJ_BaseCharacter>(GetPawn());
	if (PlayerCharacter)
	{
		PlayerCharacter->bDisableGameplay = true;
	}
}

void AKWJ_PlayerController::OnRep_MatchState()
{
	if(MatchState == MatchState::InProgress)
	{
		HandleMatchHasStarted();
	}
}


void AKWJ_PlayerController::CheckTimeSync(float DeltaTime)
{

	TimeSyncRunningTime += DeltaTime;
	if (IsLocalController() && TimeSyncRunningTime > TimeSyncFrequency)
	{
		ServerRequestServerTime(GetWorld()->GetTimeSeconds());
		TimeSyncRunningTime = 0.f;
	}
}

void AKWJ_PlayerController::ShowReturnToMainMenu()
{
	if (ReturnToMainMenuWidget == nullptr) return;
	if (ReturnToMainMenu == nullptr)
	{
		ReturnToMainMenu = CreateWidget<UKWJ_ReturnToMainMenu>(this, ReturnToMainMenuWidget);
	}
	if (ReturnToMainMenu)
	{
		bReturnToMainMenuOpen = !bReturnToMainMenuOpen;
		if (bReturnToMainMenuOpen)
		{
			ReturnToMainMenu->MenuSetup();
		}
		else
		{
			ReturnToMainMenu->MenuTearDown();
		}
	}
}

void AKWJ_PlayerController::ServerCheckMatchState_Implementation()
{
	AKWJ_GameMode* PlayerGameMode = Cast<AKWJ_GameMode>(UGameplayStatics::GetGameMode(this));
	if (PlayerGameMode)
	{
		WaitingTime = PlayerGameMode->WaitingTime;
		MatchTime = PlayerGameMode->MatchTime;
		CooldownTime = PlayerGameMode->CooldownTime;
		LevelStartingTime = PlayerGameMode->LevelStartingTime;
		MatchState = PlayerGameMode->GetMatchState();
		ClientJoinMidgame(MatchState, WaitingTime, MatchTime, CooldownTime, LevelStartingTime);

	}
}

void AKWJ_PlayerController::ClientJoinMidgame_Implementation(FName StateOfMatch, float Waiting, float Match, float Cooldown ,float StartingTime)	 
{
	WaitingTime = Waiting;
	MatchTime = Match;
	CooldownTime = Cooldown;
	LevelStartingTime = StartingTime;
	MatchState = StateOfMatch;
	OnMatchStateSet(MatchState);

}

void AKWJ_PlayerController::ClientReportServerTime_Implementation(float TimeofClientRequest, float TimeServerReceivedClientRequest)
{
	float RoundTripTime = GetWorld()->GetTimeSeconds() - TimeofClientRequest;
	float CurrentServerTime = TimeServerReceivedClientRequest + (0.5f * RoundTripTime);
	ClientServerDelta = CurrentServerTime - GetWorld()->GetTimeSeconds();
}

void AKWJ_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (InputComponent == nullptr) return;

	InputComponent->BindAction("Quit", IE_Pressed, this, &AKWJ_PlayerController::ShowReturnToMainMenu);
}

void AKWJ_PlayerController::ServerRequestServerTime_Implementation(float TimeOfClientRequest)
{
	float ServerTimeOfReceipt = GetWorld()->GetTimeSeconds();
	ClientReportServerTime(TimeOfClientRequest, ServerTimeOfReceipt);
}

void AKWJ_PlayerController::GetAllPlayerControllers()
{
	UWorld* World = GetWorld();
	if (World)
	{
		for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
		{
			APlayerController* PlayerController = It->Get();
			if (PlayerController)
			{
				PlayerControllers.Add(PlayerController);
			}
		}
	}

}

void AKWJ_PlayerController::CreateTeamState()
{
	PlayerHUD = PlayerHUD == nullptr ? Cast<AKWJ_HUD>(GetHUD()) : PlayerHUD;

	//bool bTeamWidgetValid = PlayerHUD &&
	//	PlayerHUD->CharacterStateWidget &&
	//	PlayerHUD->CharacterStateWidget->TeamStateList;
	//	
	//for (auto PlayerController : PlayerControllers)
	//{
	//	PlayerHUD->CharacterStateWidget->AddTeamStateWidget();
	//	AKWJ_BaseCharacter* BaseCharacter = Cast<AKWJ_BaseCharacter>(PlayerController->GetCharacter());
	//	if (BaseCharacter != nullptr)
	//	{
	//		BaseCharacter->GetCurHp();
	//		BaseCharacter->GetMaxHp();


	//	}
	//}
}


void AKWJ_PlayerController::CharacterTypeChange()
{
	ACharacter* MyCharacter = Cast<ACharacter>(GetPawn());
	if (MyCharacter)
	{

		UClass* CharacterClass = MyCharacter->GetClass();
		if (CharacterClass)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				30.0f,
				FColor::Yellow,
				FString::Printf(TEXT("Character Type Change is Called"))
			);

			if (CharacterClass == KnightCharacter)
			{
				GEngine->AddOnScreenDebugMessage(
					-1,
					30.0f,
					FColor::Yellow,
					FString::Printf(TEXT("This is Knight Character"))
				);

				FRotator Rotation = MyCharacter->GetActorRotation();

				UnPossess();

				TArray<UStaticMeshComponent*> StaticMeshComponents;
				MyCharacter->GetComponents<UStaticMeshComponent>(StaticMeshComponents);
				for (UStaticMeshComponent* StaticMeshComponent : StaticMeshComponents)
				{
					StaticMeshComponent->DestroyComponent();
				}

				MyCharacter->Destroy();



				APawn* NewCharacter = GetWorld()->SpawnActor<APawn>(GunnerCharacter, GetSpawnLocation(), Rotation);
				if (NewCharacter)
				{
					Possess(NewCharacter);
				}
			}

			if (CharacterClass == GunnerCharacter)
			{
				GEngine->AddOnScreenDebugMessage(
					-1,
					30.0f,
					FColor::Yellow,
					FString::Printf(TEXT("This is Gunner Character"))
				);


				FRotator Rotation = MyCharacter->GetActorRotation();

				TArray<UStaticMeshComponent*> StaticMeshComponents;
				MyCharacter->GetComponents<UStaticMeshComponent>(StaticMeshComponents);
				for (UStaticMeshComponent* StaticMeshComponent : StaticMeshComponents)
				{
					StaticMeshComponent->DestroyComponent();
				}


				UnPossess();

				MyCharacter->Destroy();



				APawn* NewCharacter = GetWorld()->SpawnActor<APawn>(KnightCharacter, GetSpawnLocation(), Rotation);
				if (NewCharacter)
				{
					Possess(NewCharacter);
				}
			}



			// 캐릭터 클래스를 사용하여 작업 수행
			// 예: 클래스 이름 가져오기, 속성 설정, 함수 호출 등
		}
	}
}

void AKWJ_PlayerController::SetTeamState()
{
	PlayerHUD = PlayerHUD == nullptr ? Cast<AKWJ_HUD>(GetHUD()) : PlayerHUD;

	bool bTeamWidgetValid = PlayerHUD &&
		PlayerHUD->CharacterStateWidget;

	if (bTeamWidgetValid)
	{
		PlayerHUD->CharacterStateWidget->AddTeamStateWidget();
	}
}
