// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KWJ_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class VR12_TEAM3PROJECT_API AKWJ_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AKWJ_PlayerController();

	void SetHUDHp(float CurHp, float MaxHp);
	void SetHUDScore(float Score);
	void SetHUDWeaponAmmo(int32 Ammo);
	void SetHUDCarriedAmmo(int32 Ammo);
	void SetHUDMatchCountdown(float CountdownTime);
	void SetHUDAnnouncementCountdown(float CountdownTime);
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; 

	virtual float GetServerTime();
	virtual void ReceivedPlayer() override;
	void OnMatchStateSet(FName State);
	void HandleMatchHasStarted();
	void HandleCooldown();
protected:
	virtual void BeginPlay() override;
	void SetHUDTime();
	void PollInit();

	UFUNCTION(Server, Reliable)
	void ServerRequestServerTime(float TimeOfClientRequest);
	
	UFUNCTION(Client, Reliable)
	void ClientReportServerTime(float TimeofClientRequest, float TimeServerReceivedClientRequest);

	float ClientServerDelta = 0.f;

	UPROPERTY(EditAnywhere , Category = "Time")
	float TimeSyncFrequency = 5.f;

	float TimeSyncRunningTime = 0.f;
	
	void CheckTimeSync(float DeltaTime);

	UFUNCTION(Server, Reliable)
	void ServerCheckMatchState();

	UFUNCTION(Client, Reliable)
	void ClientJoinMidgame(FName StateOfMatch, float Waiting, float Match, float Cooldown, float StartingTime);
private:
	UPROPERTY();
	class AKWJ_HUD* PlayerHUD;

	UPROPERTY();
	class AKWJ_GameMode* Team3GameMode;

	float LevelStartingTime = 0.f;
	float MatchTime = 0.f;
	float WaitingTime = 0.f;
	float CooldownTime = 0.f;
	uint32 CountdownInt = 0;

	UPROPERTY(ReplicatedUsing = OnRep_MatchState)
	FName MatchState;

	UFUNCTION()
	void OnRep_MatchState();

	UPROPERTY()
		class UKWJ_CharacterStateWidget* CharacterStateWidget;
	bool bInitializeCharacterOverlay = false;

	float HUDHp;
	float HUDMaxHp;
	float HUDScore;
	int32 HUDDefeats;
};
