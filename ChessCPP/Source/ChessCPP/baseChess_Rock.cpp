// Fill out your copyright notice in the Description page of Project Settings.


#include "baseChess_Rock.h"

AbaseChess_Rock::AbaseChess_Rock()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>StaticMeshAsset(TEXT("StaticMesh'/Game/StaticMesh/StaticMesh_Rock.StaticMesh_Rock'"));
	StaticMesh->SetStaticMesh(StaticMeshAsset.Object);

	//FVector RelLocation = {0.f,0.f,-70.f};
	StaticMesh->SetRelativeLocation({ 0.f, 0.f, -70.f });

	//StaticMesh->RelativeLocation.X = 0.f;
	//StaticMesh->RelativeLocation.Y = 0.f;
	//StaticMesh->RelativeLocation.Z = -70.f;

	
}

void AbaseChess_Rock::BeginPlay()
{
	Super::BeginPlay();
}

