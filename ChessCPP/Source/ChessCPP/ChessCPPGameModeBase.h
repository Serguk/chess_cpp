// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerPawn.h"
#include "enum_ChessName.h"
#include "enum_ChessTeam.h"
#include "TimerManager.h"
#include "TablePart.h"

#include "Blueprint/UserWidget.h"
#include "w_History.h"
#include "w_CheckMate.h"

#include "ChessCPPGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CHESSCPP_API AChessCPPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AChessCPPGameModeBase();

	//-----CheyHod-------
	UPROPERTY()
	TEnumAsByte <enum_ChessTeam> CheyHod = White;

	//-----PlayerPawn------
	UPROPERTY()
		APlayerPawn* PlayerPawn;
	
	//-----BaseChess
	UPROPERTY()
		UObject* BaseChess;
	//-----ChessCurrent --> FirstClick
	UPROPERTY()
		ATablePart* Chess_Current;
	//-----ChessNext    --> SecondClick
	UPROPERTY()
		ATablePart* Chess_Next;
	//----------------------------------
	//
	UPROPERTY()
		bool ChessKing_Check;
	//
	UPROPERTY()
		bool ChessKing_CheckMate;
	//
	UPROPERTY()
		bool ChessKing_Pat;
	//----------------------------------
	//
	UPROPERTY()
		bool IsCanCasting_White;
	//
	UPROPERTY()
		bool IsCanCasting_Black;
	//
	UPROPERTY()
		TEnumAsByte <enum_ChessName> Last_Chess_Name = Note;
	//
	UPROPERTY()
		TEnumAsByte <enum_ChessTeam> Last_Chess_Color = None;
	
	//Widget History
	UPROPERTY()
		Uw_History* WidgetHistory;
	UPROPERTY()
		TSubclassOf<UUserWidget>WidgetClassWidgetHistory;
	//Widget CheckMate
	UPROPERTY()
		Uw_CheckMate* WidgetCheckMate;
	UPROPERTY()
		TSubclassOf<UUserWidget>WidgetClassWidgetCheckMate;




	//Change CheyHod AND Rotate
	UFUNCTION()
		void ChaingeChayHod();
	UFUNCTION()
		void RotateToBlack();
	UFUNCTION()
		void RotateToWhite();	
    UPROPERTY()
		FTimerHandle TimerDelay;

	//OnRep
	UFUNCTION()
		void F_ChessKing_CheckMate(bool bChessKing_CheckMate);
	UFUNCTION()
		void F_ChessKing_Check(bool bChessKing_Check);
	UFUNCTION()
		void F_ChessKing_Pat(bool bChessKing_Pat);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	

};
