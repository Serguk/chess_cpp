// Fill out your copyright notice in the Description page of Project Settings.


#include "baseChess_Queen.h"

AbaseChess_Queen::AbaseChess_Queen()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>StaticMeshAsset(TEXT("StaticMesh'/Game/StaticMesh/StaticMesh_Queen.StaticMesh_Queen'"));
	StaticMesh->SetStaticMesh(StaticMeshAsset.Object);
	
	StaticMesh->SetRelativeLocation({ 0.f, 0.f, -70.f });

	//StaticMesh->RelativeLocation.X = 0.f;
	//StaticMesh->RelativeLocation.Y = 0.f;
	//StaticMesh->RelativeLocation.Z = -70.f;
}

void AbaseChess_Queen::BeginPlay()
{
	Super::BeginPlay();
}