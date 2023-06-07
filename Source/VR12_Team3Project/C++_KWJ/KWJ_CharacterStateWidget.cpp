// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "KWJ_CharacterStateWidget.h"
#include "Components/VerticalBox.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "KWJ_TeamStateWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UKWJ_CharacterStateWidget::AddTeamStateWidget(UVerticalBox* VerticalBox)
{
    if (VerticalBox)
    {
        VerticalBox->ClearChildren();

        //    UWorld* World = GetWorld();
        //    if (World)
        //    {
        //        TArray<AActor*> FoundActors;
        //        UGameplayStatics::GetAllActorsOfClass(World, AYourActorClass::StaticClass(), FoundActors);

        //        // FoundActors �迭�� AYourActorClass Ŭ������ ��� ���͵��� ����˴ϴ�.

        //        // ����: FoundActors �迭�� �ִ� ��� ���͵��� ��ȸ�ϸ� �α� ����ϱ�
        //        for (AActor* Actor : FoundActors)
        //        {
        //            if (AYourActorClass* YourActor = Cast<AYourActorClass>(Actor))
        //            {
        //                // YourActor�� ����Ͽ� ���ϴ� �۾��� ������ �� �ֽ��ϴ�.
        //                // ���� ���, �α� ���
        //                UE_LOG(LogTemp, Warning, TEXT("Found actor: %s"), *YourActor->GetName());
        //            }
        //        }
        //    }
        //}
    }

        // Create an instance of your widget class
        UKWJ_TeamStateWidget* TeamStateWidget = CreateWidget<UKWJ_TeamStateWidget>(GetWorld(), TeamStateWidgetClass);
        if (TeamStateWidget)
        {
            UWidget* WidgetToAdd = TeamStateWidget->GetRootWidget();
            if (WidgetToAdd)
            {
                VerticalBox->AddChild(WidgetToAdd);
            }
        }
 
}

