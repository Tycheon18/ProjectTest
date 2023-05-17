// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameModeBase.generated.h"

class UPlayerWidget;

/**
 * 
 */
UCLASS()
class VR12_TEAM3PROJECT_API AMainGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMainGameModeBase();
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	UUserWidget* CurrentWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	TSubclassOf<UUserWidget> HUDWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		UPlayerWidget* PlayerWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		TSubclassOf<UPlayerWidget> PlayerHUDWidget;
};
