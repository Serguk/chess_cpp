// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "ChessCPPGameModeBase.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
//#include "Engine/Engine.h"



AChessCPPGameModeBase::AChessCPPGameModeBase()
{
	//Set Default Pawn Class
	DefaultPawnClass = APlayerPawn::StaticClass();

	//Wisget History
	static ConstructorHelpers::FClassFinder<UUserWidget>WidgetFind1(TEXT("/Game/Blueprints/w_History_bp"));
	WidgetClassWidgetHistory = WidgetFind1.Class;

	//Wisget CheckMate
	static ConstructorHelpers::FClassFinder<UUserWidget>WidgetFind2(TEXT("/Game/Blueprints/w_CheckMate_bp"));
	WidgetClassWidgetCheckMate = WidgetFind2.Class;

}





//===============================================================================
void AChessCPPGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//SetShowMouseCursor
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->bShowMouseCursor = true;

	WidgetCheckMate = CreateWidget<Uw_CheckMate>(UGameplayStatics::GetPlayerController(GetWorld(), 0), WidgetClassWidgetCheckMate);
	WidgetCheckMate->AddToViewport(0);

	WidgetHistory = CreateWidget<Uw_History>(UGameplayStatics::GetPlayerController(GetWorld(), 0), WidgetClassWidgetHistory);
	WidgetHistory->AddToViewport(0);

	//Set Chey Hod
	CheyHod = White;

	//Get Player Pawn
	PlayerPawn = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));

	//Get All Table Parts 
	//Set All Chess On Start
	TArray<AActor*> TablePartAll;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);

	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{

		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			TablePart->E_SetChess_OnStart();
		}
	}

	
}
//==========================================================================================================
void AChessCPPGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::FromInt(enumy_));
}




//==========================================================================================================
void AChessCPPGameModeBase::ChaingeChayHod()
{
	if(CheyHod == White)
	{
		//if CheyHod == White --> Set Black
		CheyHod = Black;

		//BituePole
		TArray<AActor*> TableParts;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TableParts);
		for (auto It = TableParts.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Chess_Name == Pawn && TablePart->Chess_Color == Black)
				{
					TablePart->Chess_FightPlace = false;
				}
			}

		}

		//Rotate after Delay(0.5f)
		GetWorldTimerManager().SetTimer(TimerDelay, this, &AChessCPPGameModeBase::RotateToBlack, 0.5f, false, 0.0f);
	}

	else if(CheyHod == Black)
	{
		CheyHod = White;

		TArray<AActor*> TableParts;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TableParts);
		for (auto It = TableParts.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Chess_Name == Pawn && TablePart->Chess_Color == White)
				{
					TablePart->Chess_FightPlace = false;
				}
			}
		}

		GetWorldTimerManager().SetTimer(TimerDelay, this, &AChessCPPGameModeBase::RotateToWhite, 0.5f, false, 0.0f);
	}

}
//-------------------------RotateToBlack---------------
void AChessCPPGameModeBase::RotateToBlack()
{
	GetWorldTimerManager().ClearTimer(TimerDelay);
	PlayerPawn->RotateToBlackPos();
}
//------------------------RotateToWhite----------------
void AChessCPPGameModeBase::RotateToWhite()
{
	GetWorldTimerManager().ClearTimer(TimerDelay);
	PlayerPawn->RotateToWhitePos();
}

//-----------------------------------------------------
void AChessCPPGameModeBase::F_ChessKing_CheckMate(bool bChessKing_CheckMate)
{
	if (bChessKing_CheckMate != ChessKing_CheckMate)
	{
		ChessKing_CheckMate = bChessKing_CheckMate;
		WidgetCheckMate->MassageSetVis(2);
	}
}

void AChessCPPGameModeBase::F_ChessKing_Check(bool bChessKing_Check)
{
	if (bChessKing_Check != ChessKing_Check)
	{
		ChessKing_Check = bChessKing_Check;
	}

	if (ChessKing_Check)
	{
		WidgetCheckMate->MassageSetVis(1);
	}
	else
	{
		WidgetCheckMate->MassageSetVis(0);
	}
}

void AChessCPPGameModeBase::F_ChessKing_Pat(bool bChessKing_Pat)
{
	if (bChessKing_Pat != ChessKing_Pat)
	{
		ChessKing_Pat = bChessKing_Pat;
        WidgetCheckMate->MassageSetVis(3);
	}	
}
