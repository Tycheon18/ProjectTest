// Fill out your copyright notice in the Description page of Project Settings.


#include "KWJ_CharacterStateWidget.h"
#include "Components/VerticalBox.h"
#include "KWJ_TeamStateWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UKWJ_CharacterStateWidget::AddTeamStateWidget(UVerticalBox* VerticalBox)
{
    if (VerticalBox)
    {
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
}
