// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHud.h"

AMainGameModeBase::AMainGameModeBase()
{

}

void AMainGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidget);
	CurrentWidget->AddToViewport();

}
