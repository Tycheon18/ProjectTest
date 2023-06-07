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

        //        // FoundActors 배열에 AYourActorClass 클래스의 모든 액터들이 저장됩니다.

        //        // 예시: FoundActors 배열에 있는 모든 액터들을 순회하며 로그 출력하기
        //        for (AActor* Actor : FoundActors)
        //        {
        //            if (AYourActorClass* YourActor = Cast<AYourActorClass>(Actor))
        //            {
        //                // YourActor를 사용하여 원하는 작업을 수행할 수 있습니다.
        //                // 예를 들어, 로그 출력
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

