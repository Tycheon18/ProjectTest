// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuildManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VR12_TEAM3PROJECT_API UBuildManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuildManagerComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ToggleBuildMode();

	UFUNCTION(BlueprintCallable)
	void RequestBuild();

	UPROPERTY(VIsibleAnywhere, BlueprintReadWrite, Category = Building)
	float GridSize = 300.f;

	UPROPERTY(VIsibleAnywhere, BlueprintReadWrite, Category = Building)
	float BuildDistance = 500.f;

	UPROPERTY(VIsibleAnywhere, BlueprintReadWrite, Category = Building)
	float FloorHeight = 130.2f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	FVector getNextBuildLocation() const;
	FRotator getNextBuildRotation() const;

	bool isBuilding;

	UCameraComponent* PlayerCamera;

};
