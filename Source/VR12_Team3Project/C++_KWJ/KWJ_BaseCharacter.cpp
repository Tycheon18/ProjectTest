// Fill out your copyright notice in the Description page of Project Settings.


#include "KWJ_BaseCharacter.h"
#include "KWJ_PlayerController.h"
#include "KWJ_GameMode.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "Components/WidgetComponent.h"
#include "KWJ_PlayerState.h"
#include "BuildManagerComponent.h"

// Sets default values
AKWJ_BaseCharacter::AKWJ_BaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//5PrimaryActorTick.bCanEverTick = true;

	MaxHp = 100.0f;
	CurHp = MaxHp;

	OverheadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadWidget"));
	OverheadWidget->SetupAttachment(RootComponent);

	BuildManager = CreateDefaultSubobject<UBuildManagerComponent>(TEXT("BuildManager"));
}

void AKWJ_BaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AKWJ_BaseCharacter, Weapon);
	DOREPLIFETIME(AKWJ_BaseCharacter, CurHp);
	DOREPLIFETIME(AKWJ_BaseCharacter, bDisableGameplay);
	DOREPLIFETIME(AKWJ_BaseCharacter, CurStamina);
}

// Called when the game starts or when spawned
void AKWJ_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();


	PlayerController = Cast<AKWJ_PlayerController>(Controller);
	if (PlayerController)
	{
		PlayerController->SetHUDHp(CurHp, MaxHp);
		PlayerController->SetHUDStamina(CurStamina, MaxStamina);
	}

	GEngine->AddOnScreenDebugMessage(
		-1,
		60.f,
		FColor::Yellow,
		FString::Printf(TEXT("My Hp is %f"), CurHp)
	);
	GEngine->AddOnScreenDebugMessage(
		-1,
		60.f,
		FColor::Yellow,
		FString::Printf(TEXT("My Stamina is %f"), CurStamina)
	);

	UpdateHUDHp();
	UpdateHUDStamina();

	CurHp -= 10;
}

void AKWJ_BaseCharacter::PollInit()
{
	if (PlayerState == nullptr)
	{
		PlayerState = GetPlayerState<AKWJ_PlayerState>();
		if (PlayerState)
		{
			PlayerState->AddToScore(0.f);
			PlayerState->AddToDefeats(0);
		}
	}
}

void AKWJ_BaseCharacter::OnRep_CurHp()
{
	UpdateHUDHp();

	KWJ_GameMode = KWJ_GameMode == nullptr ? Cast<AKWJ_GameMode>(GetWorld()->GetAuthGameMode()) : KWJ_GameMode;

	if (KWJ_GameMode)
	{

		KWJ_GameMode->RenewTeamState();
	}
}

void AKWJ_BaseCharacter::OnRep_Stamina()
{
	UpdateHUDStamina();

	KWJ_GameMode = KWJ_GameMode == nullptr ? Cast<AKWJ_GameMode>(GetWorld()->GetAuthGameMode()) : KWJ_GameMode;


	if (KWJ_GameMode)
	{
		KWJ_GameMode->RenewTeamState();
	}
}


void AKWJ_BaseCharacter::UpdateHUDHp()
{
	PlayerController = PlayerController == nullptr ? Cast<AKWJ_PlayerController>(Controller) : PlayerController;

	if (PlayerController)
	{
		PlayerController->SetHUDHp(CurHp, MaxHp);
	}
}

void AKWJ_BaseCharacter::UpdateHUDStamina()
{
	PlayerController = PlayerController == nullptr ? Cast<AKWJ_PlayerController>(Controller) : PlayerController;
	if (PlayerController)
	{
		PlayerController->SetHUDStamina(CurStamina, MaxStamina);
	}
}

void AKWJ_BaseCharacter::ServerLeaveGame_Implementation()
{
	AKWJ_GameMode* GameMode = GetWorld()->GetAuthGameMode<AKWJ_GameMode>();
	PlayerState = PlayerState == nullptr ? GetPlayerState<AKWJ_PlayerState>() : PlayerState;
	if (GameMode && PlayerState)
	{
		GameMode->PlayerLeftGame(PlayerState);
	} 
}

// Called every frame
void AKWJ_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PollInit();
}

// Called to bind functionality to input
void AKWJ_BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

