// Fill out your copyright notice in the Description page of Project Settings.


#include "w_SelectChess.h"
#include "Blueprint/WidgetTree.h"






void Uw_SelectChess::NativeConstruct()
{
	Super::NativeConstruct();

	GLog->Log(TEXT("WIDGET_WAS_CREATED"));
}


void Uw_SelectChess::SelectedKnight()
{
	GLog->Log(TEXT("SelectedKnight"));

	Del_SelectedKnight.Execute();
}

void Uw_SelectChess::SelectedBishop()
{
	GLog->Log(TEXT("SelectedBishop"));

	Del_SelectedBishop.Execute();
}

void Uw_SelectChess::SelectedRock()
{
	GLog->Log(TEXT("SelectedRock"));

	Del_SelectedRock.Execute();
}

void Uw_SelectChess::SelectedQueen()
{
	GLog->Log(TEXT("SelectedQueen"));

	//Del_SelectedQueen.Execute();
}

