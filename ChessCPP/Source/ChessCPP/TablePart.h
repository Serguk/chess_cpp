// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Materials/Material.h"
#include "enum_ChessName.h"
#include "enum_ChessTeam.h"
#include "ConstructorHelpers.h"

#include "Blueprint/UserWidget.h"
#include "w_SelectChess.h"

#include "baseChess.h"
#include "baseChess_Pawn.h"
#include "baseChess_Knight.h"
#include "baseChess_Bishop.h"
#include "baseChess_Rock.h"
#include "baseChess_Queen.h"
#include "baseChess_King.h"

#include "w_SelectChess.h"

#include "TablePart.generated.h"



UCLASS()
class CHESSCPP_API ATablePart : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATablePart();

	//Scene Comp
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USceneComponent *SceneComp;
	//StaticMesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent *StaticMesh;

	UPROPERTY()
		ATablePart* TablePartCurrClick;
	
	//Materials
	UPROPERTY()
		UMaterial* Material_Black;
	UPROPERTY()
		UMaterial* Material_White;
	UPROPERTY()
		UMaterial* Material_Brown;
	UPROPERTY()
		UMaterial* Material_Yellow;
	UPROPERTY()
		UMaterial* Material_Green;
	UPROPERTY()
		UMaterial* Material_Red;
	UPROPERTY()
		UMaterial* Material_Orange;
	UPROPERTY()
		UMaterial* Material_Blue;

	//Game Mode
	//UPROPERTY()
	//	AChessCPPGameModeBase* GM_Base;
	//---
	UPROPERTY(EditInstanceOnly)
		FString Table_Pos_Name;

	UPROPERTY(EditInstanceOnly)
		FVector2D Table_Pos_Current;

	UPROPERTY(EditInstanceOnly)
		UMaterial* Table_Color;

	UPROPERTY(EditInstanceOnly)
		TEnumAsByte <enum_ChessName> Chess_Name = Note;
		
	UPROPERTY(EditInstanceOnly)
		TEnumAsByte <enum_ChessTeam> Chess_Color = None;

	UPROPERTY()
		bool Chess_FightPlace = false;

	UPROPERTY()
		TArray<ATablePart*> Enumy_Chess_Pawn;
	UPROPERTY()
		TArray<ATablePart*> Enumy_Chess_Knight;
	UPROPERTY()
		TArray<ATablePart*> Enumy_Chess_Bishop;
	UPROPERTY()
		TArray<ATablePart*> Enumy_Chess_Rock;
	UPROPERTY()
		TArray<ATablePart*> Enumy_Chess_Queen;
	UPROPERTY()
		TArray<ATablePart*> Enumy_Chess_King;
	UPROPERTY()
		TArray<ATablePart*> Enumy_Chess_All;

	UPROPERTY()
		Uw_SelectChess* Widget;
	UPROPERTY()
		TSubclassOf<UUserWidget>WidgetClassSelectChess;
	



	

	//FUNCTIONS

	//clear all table
	UFUNCTION()
		void F_ClearAllTable();
	
	//set all chess on start pos
	UFUNCTION()
		void E_SetChess_OnStart();
	
	//For Touch on Figure
	UFUNCTION()
		void InputTouchBegin(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

	//PAWN
	UFUNCTION()
		bool F_Pawn_Move();

	UFUNCTION()
		bool F_Pawn_Attack();

	UFUNCTION()
		void F_Pawn_Painting();

	//KNIGHT
	UFUNCTION()
		bool F_Knight_Move();

	UFUNCTION()
		bool F_Knight_Attack();

	UFUNCTION()
		void F_Knight_Painting();

	//BISHOP
	UFUNCTION()
		bool F_Bishop_Move();

	UFUNCTION()
		bool F_Bishop_Attack();

	UFUNCTION()
		void F_Bishop_Painting();

	//ROCK
	UFUNCTION()
		bool F_Rock_Move();

	UFUNCTION()
		bool F_Rock_Attack();

	UFUNCTION()
		void F_Rock_Painting();

	//QUEEN
	UFUNCTION()
		bool F_Queen_Move();

	UFUNCTION()
		bool F_Queen_Attack();

	UFUNCTION()
		void F_Queen_Painting();

	//KING
	UFUNCTION()
		bool F_King_Move();

	UFUNCTION()
		bool F_King_Attack();

	UFUNCTION()
		void F_King_Painting();

	//OTHER ALL CHESS
	UFUNCTION()
		void F_Chess_CheckPos(int32 NewParam);

	UFUNCTION()
		void F_Chess_CheckPos2();

	UFUNCTION()
		void F_Chess_Change(ATablePart* Point, enum_ChessName ChessName);

	UFUNCTION()
		void F_Chess_Chackmate();

	UFUNCTION()
		void F_Chess_Chackmate1();
	UFUNCTION()
		void F_Chess_Chackmate2(ATablePart* LEnemy);


	UFUNCTION()
		void F_Chess_Pat();

	UFUNCTION()
		void F_Chess_Casting_Painting();
	UFUNCTION()
		void F_Chess_Casting_Painting1();

	UFUNCTION()
		bool F_Chess_Casting_Move();

	UFUNCTION()
		void F_TablePart1(ATablePart* TablePart);

	UFUNCTION()
		void F_TablePart2(ATablePart* TablePart);

	UFUNCTION()
		void F_SelectedKnight();

	UFUNCTION()
		void F_SelectedBishop();

	UFUNCTION()
		void F_SelectedRock();

	UFUNCTION()
		void F_SelectedQueen();




	






protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
