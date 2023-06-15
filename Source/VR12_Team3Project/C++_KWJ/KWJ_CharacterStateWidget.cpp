// Fill out your copyright notice in the Description page of Project Settings.

#include "KWJ_CharacterStateWidget.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Components/VerticalBox.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "GameFramework/Character.h"
#include "KWJ_TeamStateWidget.h"
#include "KWJ_BaseCharacter.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UKWJ_CharacterStateWidget::AddTeamStateWidget()
{
    if (TeamStateList)
    {
        TeamStateList->ClearChildren();

        UWorld* World = GetWorld();
        if (World)
        {
            TArray<AActor*> FoundActors;
            UGameplayStatics::GetAllActorsOfClass(World, AKWJ_BaseCharacter::StaticClass(), FoundActors);

            //GEngine->AddOnScreenDebugMessage(
            //    1,
            //    60.f,
            //    FColor::Yellow,
            //    FString::Printf(TEXT("Actors Num = %d"), sizeof(FoundActors))
            //);

            for (AActor* Actor : FoundActors)
            {
                if (AKWJ_BaseCharacter* PlayerCharacter = Cast<AKWJ_BaseCharacter>(Actor))
                {
                    GEngine->AddOnScreenDebugMessage(
                        -1,
                        0.5f,
                        FColor::Yellow,
                        FString::Printf(TEXT("Hi, I Have BaseCharacter"))
                    );

                    float CurHp = PlayerCharacter->GetCurHp();
                    float MaxHp = PlayerCharacter->GetMaxHp();
                    float CurStamina = PlayerCharacter->GetCurStamina();
                    float MaxStamina = PlayerCharacter->GetMaxStamina();
                    FString Name = PlayerCharacter->PlayerName;


                    float HpPercent = CurHp / MaxHp;
                    float StaminaPercent = CurStamina / MaxStamina;

                    UKWJ_TeamStateWidget* TeamStateWidget = CreateWidget<UKWJ_TeamStateWidget>(GetWorld(), TeamStateWidgetClass);
                    if (TeamStateWidget)
                    {
                        GEngine->AddOnScreenDebugMessage(
                            -1,
                            0.5f,
                            FColor::Yellow,
                            FString::Printf(TEXT("Create My Team State"))
                        );

                        TeamStateList->AddChild(TeamStateWidget);
                        TeamStateWidget->PlayerName->SetText(FText::FromString(Name));
                        TeamStateWidget->HpBar->SetPercent(HpPercent);
                        TeamStateWidget->StaminaBar->SetPercent(StaminaPercent);
                    }
                }
            }
        }

    }

    // Create an instance of your widget class


}