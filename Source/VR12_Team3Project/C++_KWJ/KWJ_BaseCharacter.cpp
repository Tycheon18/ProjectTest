// Fill out your copyright notice in the Description page of Project Settings.


#include "KWJ_BaseCharacter.h"
#include "KWJ_PlayerController.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AKWJ_BaseCharacter::AKWJ_BaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//5PrimaryActorTick.bCanEverTick = true;

}

void AKWJ_BaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AKWJ_BaseCharacter, Weapon);
}

// Called when the game starts or when spawned
void AKWJ_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<AKWJ_PlayerController>(Controller);
	if (PlayerController)
	{
		PlayerController->SetHUDHp(CurHp, MaxHp);
	}
}

void AKWJ_BaseCharacter::OnRep_Health()
{

}

// Called every frame
void AKWJ_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKWJ_BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

