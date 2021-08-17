// Fill out your copyright notice in the Description page of Project Settings.


#include "baseChess_Pawn.h"

AbaseChess_Pawn::AbaseChess_Pawn()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>StaticMeshAsset(TEXT("StaticMesh'/Game/StaticMesh/StaticMesh_Pawn.StaticMesh_Pawn'"));
	StaticMesh->SetStaticMesh(StaticMeshAsset.Object);

	StaticMesh->SetRelativeLocation({ 0.f, 0.f, 0.f });

	//StaticMesh->RelativeLocation.X = 0.f;
	//StaticMesh->RelativeLocation.Y = 0.f;
	//StaticMesh->RelativeLocation.Z = 0.f;
}

void AbaseChess_Pawn::BeginPlay()
{
	Super::BeginPlay();
}
