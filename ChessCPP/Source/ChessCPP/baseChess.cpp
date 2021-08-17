// Fill out your copyright notice in the Description page of Project Settings.


#include "baseChess.h"


// Sets default values
AbaseChess::AbaseChess()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//initialization capsule size
	GetCapsuleComponent()->InitCapsuleSize(55.f,96.f);
	//Set Collisions
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);


	//create static mesh and attach it to capsule component
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh", false);
	StaticMesh->SetupAttachment(GetCapsuleComponent());
	//Set Collisions
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	StaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);


}

// Called when the game starts or when spawned
void AbaseChess::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AbaseChess::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AbaseChess::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

