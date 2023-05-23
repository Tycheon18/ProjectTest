// Fill out your copyright notice in the Description page of Project Settings.


#include "KWJ_GameModeBase.h"
#include "KWJ_HUD.h"

AKWJ_GameModeBase::AKWJ_GameModeBase()
{
	HUDClass = AKWJ_HUD::StaticClass();
}

void AKWJ_GameModeBase::Tick(float DeltaTime)
{
}

void AKWJ_GameModeBase::BeginPlay()
{
}

