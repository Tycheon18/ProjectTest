// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KWJ_Announcement.generated.h"

/**
 * 
 */
UCLASS()
class VR12_TEAM3PROJECT_API UKWJ_Announcement : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BIndWidget))
		class UTextBlock* WaitingTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BIndWidget))
		class UTextBlock* AnnouncementText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BIndWidget))
		class UTextBlock* InfoText;
};
