// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildManagerComponent.h"

// Sets default values for this component's properties
UBuildManagerComponent::UBuildManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	isBuilding = false;
	// ...
}


// Called when the game starts
void UBuildManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	PlayerCamera = GetOwner()->FindComponentByClass<UCameraComponent>();
	// ...
	
}

// Called every frame
void UBuildManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (isBuilding)
	{
		FVector Location = getNextBuildLocation();
		FRotator Rotation = getNextBuildRotation();

		DrawDebugBox(GetWorld(), Location, FVector(100, 100, 100), Rotation.Quaternion(), FColor::Red, false, 0, 0, 10);
	}
	// ...
}

void UBuildManagerComponent::ToggleBuildMode()
{
	isBuilding = !isBuilding;

}

void UBuildManagerComponent::RequestBuild()
{
}


FVector UBuildManagerComponent::getNextBuildLocation() const
{
	FVector DirectionVetcor = PlayerCamera->GetForwardVector() * BuildDistance;
	DirectionVetcor += GetOwner()->GetActorLocation();
	return FVector(
		FMath::GridSnap(DirectionVetcor.X, GridSize),
		FMath::GridSnap(DirectionVetcor.Y, GridSize),
		FloorHeight
	);
}

FRotator UBuildManagerComponent::getNextBuildRotation() const
{
	FRotator Rotation = PlayerCamera->GetComponentRotation();
	return FRotator(0, FMath::GridSnap(Rotation.Yaw, 90.f), 0);
}

