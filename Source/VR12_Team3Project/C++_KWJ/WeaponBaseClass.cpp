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

void AWeaponBaseClass::SetOwningPawn(ABasicCharacter* NewOwner)
{
	if (MyPawn != NewOwner)
	{
		MyPawn = NewOwner;
	}
}

void AWeaponBaseClass::AttachMeshToPawn()
{
	if (MyPawn)
	{
		USkeletalMeshComponent* PawnMesh = MyPawn->GetSpecipicPawnMesh();
		FName AttachPoint = MyPawn -> GetWeaponAttachPoint();
		//WeaponMesh->AttachTo(PawnMesh, AttachPoint);
	}
}

void AWeaponBaseClass::OnEquip(const AWeaponBaseClass* LastWeapon)
{
	AttachMeshToPawn();
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

void AWeaponBaseClass::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->IsA(AActor::StaticClass()) && MyPawn->IsAttack && OtherActor != MyPawn)
	{
		UGameplayStatics::ApplyDamage(OtherActor, 10.f, NULL, this, UDamageType::StaticClass());
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "ApplyDamage!");
	}
}

