// Fill out your copyright notice in the Description page of Project Settings.


#include "baseChess_Bishop.h"

AbaseChess_Bishop::AbaseChess_Bishop()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>StaticMeshAsset(TEXT("StaticMesh'/Game/StaticMesh/StaticMesh_Bishop.StaticMesh_Bishop'"));
	StaticMesh->SetStaticMesh(StaticMeshAsset.Object);

	StaticMesh->SetRelativeLocation({ 0.f, 0.f, -70.f });

	//StaticMesh->RelativeLocation.X = 0.f;
	//StaticMesh->RelativeLocation.Y = 0.f;
	//StaticMesh->RelativeLocation.Z = -70.f;	
}

void AbaseChess_Bishop::BeginPlay()
{
	Super::BeginPlay();

	
}
