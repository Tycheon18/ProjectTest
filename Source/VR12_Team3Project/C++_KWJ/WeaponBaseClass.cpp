// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBaseClass.h"
#include "Components/BoxComponent.h"
#include "Engine.h"


// Sets default values
AWeaponBaseClass::AWeaponBaseClass(const class FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("WeaponMesh"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = WeaponMesh;

	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
	WeaponCollision->SetBoxExtent(FVector(5.f, 5.f, 5.f));
	//WeaponCollision->AttachTo(WeaponMesh, "weapon");
}


// Called when the game starts or when spawned
void AWeaponBaseClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponBaseClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



