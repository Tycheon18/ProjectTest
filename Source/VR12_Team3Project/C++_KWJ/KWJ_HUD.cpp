// Fill out your copyright notice in the Description page of Project Settings.


#include "KWJ_HUD.h"
#include "GameFramework/PlayerController.h"
#include "KWJ_CharacterStateWidget.h"
#include "KWJ_Announcement.h"


void AKWJ_HUD::BeginPlay()
{
	Super::BeginPlay();

	//AddCharacterStateWidget();

}

void AKWJ_HUD::AddCharacterStateWidget()
{
	APlayerController* PlayerController = GetOwningPlayerController();
	if (PlayerController &&	CharacterStateWidgetClass)
	{
		CharacterStateWidget = CreateWidget<UKWJ_CharacterStateWidget>(PlayerController, CharacterStateWidgetClass);
		CharacterStateWidget->AddToViewport();
		CharacterStateWidget->AddTeamStateWidget();
	}
}

void AKWJ_HUD::AddAnnouncement()
{
	APlayerController* PlayerController = GetOwningPlayerController();
	if (PlayerController && AnnouncementClass)
	{
		Announcement = CreateWidget<UKWJ_Announcement>(PlayerController, AnnouncementClass);
		Announcement->AddToViewport();
	}
}

void AKWJ_HUD::DrawHUD()
{
	Super::DrawHUD();

	FVector2D ViewportSize;
	if (GEngine)
	{
		GEngine->GameViewport->GetViewportSize(ViewportSize);
		const FVector2D ViewportCenter(ViewportSize.X / 2.f, ViewportSize.Y / 2.f);
	}
}
