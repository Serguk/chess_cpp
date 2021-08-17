// Fill out your copyright notice in the Description page of Project Settings.


#include "TablePart.h"

#include "ChessCPPGameModeBase.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"





//================================================================================
// Sets default values
ATablePart::ATablePart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create SceneComponent and set int as root
	SceneComp = CreateDefaultSubobject<USceneComponent>("Scene", false);
	RootComponent = SceneComp;
	
	//Create StaticMeshComp and attach it to Scene
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh", false);
	StaticMesh->SetupAttachment(SceneComp);
	//set StaticMesh from content
	static ConstructorHelpers::FObjectFinder<UStaticMesh>StaticMeshAsset(TEXT("StaticMesh'/Game/StaticMesh/StaticMesh_TablePart.StaticMesh_TablePart'"));
	StaticMesh->SetStaticMesh(StaticMeshAsset.Object);
	//Set Collisions
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	StaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	//Get Materials Colors
	static ConstructorHelpers::FObjectFinder<UMaterial>MateralAsset_Black(TEXT("MaterialBlack'/Game/Materials/M_Black.M_Black'"));
	Material_Black = MateralAsset_Black.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial>MateralAsset_White(TEXT("MaterialWhite'/Game/Materials/M_White.M_White'"));
	Material_White = MateralAsset_White.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial>MateralAsset_Brown(TEXT("MaterialBrown'/Game/Materials/M_Brown.M_Brown'"));
	Material_Brown = MateralAsset_Brown.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial>MateralAsset_Yellow(TEXT("MaterialYellow'/Game/Materials/M_Yellow.M_Yellow'"));
	Material_Yellow = MateralAsset_Yellow.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial>MaterialAsset_Green(TEXT("MaterialGreen'/Game/Materials/M_Green.M_Green'"));
	Material_Green = MaterialAsset_Green.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial>MaterialAsset_Red(TEXT("MaterialRed'/Game/Materials/M_Red.M_Red'"));
	Material_Red = MaterialAsset_Red.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial>MaterialAsset_Orange(TEXT("MaterialOrange'/Game/Materials/M_Orange.M_Orange'"));
	Material_Orange = MaterialAsset_Orange.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial>MaterialAsset_Blue(TEXT("MaterialBlue'/Game/Materials/M_Blue.M_Blue'"));
	Material_Blue = MaterialAsset_Blue.Object;
	


	//get widget bluprint from content
	static ConstructorHelpers::FClassFinder<UUserWidget>WidgetFind1(TEXT("/Game/Blueprints/W_SelectChess_bp"));
	WidgetClassSelectChess = WidgetFind1.Class;
	


}

//================================================================================
// Called when the game starts or when spawned
void ATablePart::BeginPlay()
{
	Super::BeginPlay();

	//Set Base Material
	StaticMesh->SetMaterial(0, Table_Color);
	//Get Game Mode
	AChessCPPGameModeBase* GM_Base;
	GM_Base = Cast<AChessCPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	//On Input Touch Begin
	StaticMesh->OnInputTouchBegin.AddDynamic(this, &ATablePart::InputTouchBegin);

}


//================================================================================
// Called every frame
void ATablePart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


//================================================================================
void ATablePart::F_ClearAllTable()
{

	TArray<AActor*> TablePartAll;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);

	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			TablePart->StaticMesh->SetMaterial(0, TablePart->Table_Color);
		}
	}
}


//================================================================================
void ATablePart::E_SetChess_OnStart()
{
	FVector SpawnLocation = this->GetActorLocation();
	SpawnLocation.Z = 200.f;

	FQuat SpawnRotation;
	SpawnRotation.X = 0.f;
	SpawnRotation.Y = 0.f;
	SpawnRotation.Z = 0.f;

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SpawnLocation);

    FActorSpawnParameters SpawnParameters;


  switch (Chess_Name)
  {
	case Note:

		break;
		//---
	case Pawn: 
	{
		AbaseChess_Pawn* ChessPawn = GetWorld()->SpawnActor<AbaseChess_Pawn>(AbaseChess_Pawn::StaticClass(), SpawnTransform, SpawnParameters);
		ChessPawn->SetActorLocation(SpawnLocation);

		if (Chess_Color == White)
		{
            ChessPawn->StaticMesh->SetMaterial(0, Material_Yellow);
		}
		else if(Chess_Color == Black)
		{
			ChessPawn->StaticMesh->SetMaterial(0, Material_Brown);
		}
		
		break;
	}
		//---
	case Knight:
	{
		AbaseChess_Knight* ChessKnight = GetWorld()->SpawnActor<AbaseChess_Knight>(AbaseChess_Knight::StaticClass(), SpawnTransform, SpawnParameters);
		ChessKnight->SetActorLocation(SpawnLocation);
		if (Chess_Color == White)
		{
			ChessKnight->StaticMesh->SetMaterial(0, Material_Yellow);
		}
		else if (Chess_Color == Black)
		{
			ChessKnight->StaticMesh->SetMaterial(0, Material_Brown);

			//rotate black knight around to enemy
			FQuat DeltaRotation; 
			DeltaRotation.X = 0.f; DeltaRotation.Y = 0.f; DeltaRotation.Z = 180.f;
			ChessKnight->AddActorWorldRotation(DeltaRotation);
		}

		break;
	}
		//---
	case Bishop:
	{
		AbaseChess_Bishop* ChessBishop = GetWorld()->SpawnActor<AbaseChess_Bishop>(AbaseChess_Bishop::StaticClass(), SpawnTransform, SpawnParameters);
		ChessBishop->SetActorLocation(SpawnLocation);

		if (Chess_Color == White)
		{
			ChessBishop->StaticMesh->SetMaterial(0, Material_Yellow);
		}
		else if (Chess_Color == Black)
		{
			ChessBishop->StaticMesh->SetMaterial(0, Material_Brown);
		}
        
		break;
	}
		//---
	case Rock:
	{
		AbaseChess_Rock* ChessRock = GetWorld()->SpawnActor<AbaseChess_Rock>(AbaseChess_Rock::StaticClass(), SpawnTransform, SpawnParameters);
		ChessRock->SetActorLocation(SpawnLocation);

		if (Chess_Color == White)
		{
			ChessRock->StaticMesh->SetMaterial(0, Material_Yellow);
		}
		else if (Chess_Color == Black)
		{
			ChessRock->StaticMesh->SetMaterial(0, Material_Brown);
		}
        
		break;
	}
		//---
	case Queen:
	{

		AbaseChess_Queen* ChessQueen = GetWorld()->SpawnActor<AbaseChess_Queen>(AbaseChess_Queen::StaticClass(), SpawnTransform, SpawnParameters);
		ChessQueen->SetActorLocation(SpawnLocation);

		if (Chess_Color == White)
		{
			ChessQueen->StaticMesh->SetMaterial(0, Material_Yellow);
		}
		else if (Chess_Color == Black)
		{
			ChessQueen->StaticMesh->SetMaterial(0, Material_Brown);
		}

        break;
	}
		//---
	case King:
	{
		AbaseChess_King* ChessKing = GetWorld()->SpawnActor<AbaseChess_King>(AbaseChess_King::StaticClass(), SpawnTransform, SpawnParameters);
		ChessKing->SetActorLocation(SpawnLocation);

		if (Chess_Color == White)
		{
			ChessKing->StaticMesh->SetMaterial(0, Material_Yellow);
		}
		else if (Chess_Color == Black)
		{
			ChessKing->StaticMesh->SetMaterial(0, Material_Brown);
		}
		
		break;

	}
		//---
	default:

		break;
  }


}

//================================================================================
void ATablePart::InputTouchBegin(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{

	//Get Game Mode
	AChessCPPGameModeBase* GM_Base;
	GM_Base = Cast<AChessCPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	
	//Cast Owner from TouchedComponent
	ATablePart* TablePart = Cast<ATablePart>(TouchedComponent->GetOwner());
	
	if (TablePart)
	{
		TablePartCurrClick = TablePart;

		if (TablePart->Chess_Name != Note && TablePart->StaticMesh->GetMaterial(0) == Material_Green)
		{
			GM_Base->Chess_Next = TablePart;

			if (F_Chess_Casting_Move())
			{
				F_TablePart1(TablePart);
			}

		}

		else if (TablePart->Chess_Name != Note && GM_Base->CheyHod == TablePart->Chess_Color)
		{
			F_ClearAllTable();
			TablePart->StaticMesh->SetMaterial(0, Material_Orange);
			GM_Base->Chess_Current = TablePart;

			switch (Chess_Name)
			{
			    case Note: {break; }
			    //--
			    case Pawn:
			    {
				    F_Pawn_Painting();
				    break;
			    }
			    //--
			    case Knight:
			    {
				    F_Knight_Painting();
				    break;
			    }
			    //--
			    case Bishop:
			    {
				    F_Bishop_Painting();
				    break;
			    }
			    //--
			    case Rock:
			    {
				    F_Rock_Painting();
				    break;
			    }
			    //--
			    case Queen:
			    {
				    F_Queen_Painting();
				    break;
			    }
			    //--
			    case King:
			    {
				    F_Chess_CheckPos(0);
				    F_King_Painting();
				    F_Chess_Casting_Painting();
				    break;
			    }
			   	
			}


		}

		else if (TablePart->StaticMesh->GetMaterial(0) == Material_Green && TablePart->Chess_Name == Note)
		{
			GM_Base->Chess_Next = TablePart;

			switch (GM_Base->Chess_Current->Chess_Name)
			{
			    case Note:{break;}
			    //--
			    case Pawn:
			    {
				    if (F_Pawn_Move())
				    {
					    switch (GM_Base->CheyHod)
					    {
					        case None:
					        { break;}
							//--
					        case White:
					        {
						        if (TablePart->Table_Pos_Current.Y == 8.0f)
						        {
							        F_TablePart2(TablePart);
						        }
						        else
						        {
							        F_TablePart1(TablePart);
						        }
						     break;
						    }
							//--
					        case Black:
					        {
						        if (TablePart->Table_Pos_Current.Y == 1.0f)
						        {
							        F_TablePart2(TablePart);
						        }
						        else
						        {
							        F_TablePart1(TablePart);
						        }
						     break;
						    }
						}
					}
			    break;
			    }
				//--
			    case Knight:
			    {
				    if (F_Knight_Move())
				    {
					    F_TablePart1(TablePart);
				    }
			     break;
			    }
			    //--
			    case Bishop:
			    {
				    if (F_Bishop_Move())
				    {
					    F_TablePart1(TablePart);
				    }
			     break;
			    }
			    //--
			    case Rock:
			    {
				    if (F_Rock_Move())
				    {
					    F_TablePart1(TablePart);
				    }
			     break;
			    }
			    //--
			    case Queen:
			    {
				    if (F_Queen_Move())
				    {
					    F_TablePart1(TablePart);
				    }
			    break;
			    }
			    //--
			    case King:
			    {
				    if (F_King_Move())
				    {
					    F_TablePart1(TablePart);
				    }
			    break;
			    }	
		    }
		}
		
		else if(TablePart->StaticMesh->GetMaterial(0) == Material_Red)
		{
			GM_Base->Chess_Next = TablePart;

			switch (GM_Base->Chess_Current->Chess_Name)
			{
				case Note:{break;}
				//--
				case Pawn:
				{
					if (F_Pawn_Attack())
					{
						switch (GM_Base->CheyHod)
						    {
						    case None: { break;}
						    //--
						    case White:
						    {
							    if (TablePart->Table_Pos_Current.Y == 8.0f)
							    {
								    F_TablePart2(TablePart);
							    }
							    else
							    {
								    F_TablePart1(TablePart);
							    }
							 break;
							}
							//--
						    case Black:
						    {
							    if (TablePart->Table_Pos_Current.Y == 1.0f)
							    {
								    F_TablePart2(TablePart);
							    }
							    else
							    {
								    F_TablePart1(TablePart);
							    }
							    break;
						    }
						}
					}
					break;
				}
				//--
				case Knight:
				{
					if (F_Knight_Attack())
					{
						F_TablePart1(TablePart);
					}
					break;
				}
				//--
				case Bishop:
				{
					if (F_Bishop_Attack())
					{
						F_TablePart1(TablePart);
					}
					break;
				}
				//--
				case Rock:
				{
					if (F_Rock_Attack())
					{
						F_TablePart1(TablePart);
					}
					break;
				}
				//--
				case Queen:
				{
					if (F_Queen_Attack())
					{
						F_TablePart1(TablePart);
					}
					break;
				}
				//--
				case King:
				{
					if (F_King_Attack())
					{
						F_TablePart1(TablePart);
					}
					break;
				}
			}
		};
		




		/*
		//Show For Test
		FString ChessName;
		UEnum::GetValueAsString<enum_ChessName>(TablePart->Chess_Name, ChessName);
		FString ChessColor; 
		UEnum::GetValueAsString<enum_ChessTeam>(TablePart->Chess_Color, ChessColor);
		FString FBool = Chess_FightPlace ? FString("True") : FString("False");
		GLog->Log(FString(Table_Pos_Name) + FString(" : ") + FString(ChessName) + FString(" : ") + FString(ChessColor) + FString(" : ") + FBool);
		*/
			
	}

}

//--------------------------------------------------------------------------------
void ATablePart::F_TablePart1(ATablePart * TablePart)
{
	//Get Game Mode
	AChessCPPGameModeBase* GM_Base;
	GM_Base = Cast<AChessCPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	GM_Base->Last_Chess_Name = TablePart->Chess_Name;
	GM_Base->Last_Chess_Color = TablePart->Chess_Color;

	GM_Base->ChaingeChayHod();
	F_Chess_CheckPos(0);
	F_ClearAllTable();
	GM_Base->F_ChessKing_Check(false);
	//GM_Base->ChessKing_Check = false;

	for (auto It = Enumy_Chess_All.CreateIterator(); It; It++)
	{

		ATablePart* LTablePart = Cast<ATablePart>(*It);
		if (LTablePart)
		{
			if (LTablePart->Chess_Name == King)
			{
				//GM_Base->ChessKing_Check = true;
				GM_Base->F_ChessKing_Check(true);
				break;
			}
		}
	}

	//for test
	//if (GM_Base->ChessKing_Check)
	//{GLog->Log(FString("Check"));}
	//else { GLog->Log(FString("NotCheck")); };
	//


	if (GM_Base->ChessKing_Check)
	{
		F_Chess_Chackmate();
	}
	else
	{
		F_Chess_Pat();
		
	}

}

//--------------------------------------------------------------------------------
void ATablePart::F_TablePart2(ATablePart * TablePart)
{
	//create widget bluprint
	Widget = CreateWidget<Uw_SelectChess>(UGameplayStatics::GetPlayerController(GetWorld(), 0), WidgetClassSelectChess);
	Widget->AddToViewport(0);

	Widget->Del_SelectedKnight.BindUFunction(this, FName("F_SelectedKnight"));
	Widget->Del_SelectedBishop.BindUFunction(this, FName("F_SelectedBishop"));
	Widget->Del_SelectedRock.BindUFunction(this, FName("F_SelectedRock"));
	Widget->Del_SelectedQueen.BindUFunction(this, FName("F_SelectedQueen"));
}

//--------------------------------------------------------------------------------
void ATablePart::F_SelectedKnight()
{
	Widget->RemoveFromParent();
	F_Chess_Change(TablePartCurrClick, Knight);
	F_TablePart1(TablePartCurrClick);
}

//--------------------------------------------------------------------------------
void ATablePart::F_SelectedBishop()
{
	Widget->RemoveFromParent();
	F_Chess_Change(TablePartCurrClick, Bishop);
	F_TablePart1(TablePartCurrClick);
}

//--------------------------------------------------------------------------------
void ATablePart::F_SelectedRock()
{
	Widget->RemoveFromParent();
	F_Chess_Change(TablePartCurrClick, Rock);
	F_TablePart1(TablePartCurrClick);
}

//--------------------------------------------------------------------------------
void ATablePart::F_SelectedQueen()
{
	Widget->RemoveFromParent();
	F_Chess_Change(TablePartCurrClick, Queen);
	F_TablePart1(TablePartCurrClick);
}

//================================================================================
bool ATablePart::F_Pawn_Move() //ok
{
	//Get Game Mode
	AChessCPPGameModeBase* GM_Base;
	GM_Base = Cast<AChessCPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	//local var
	bool LCanMove = true;

	TEnumAsByte <enum_ChessName> LCurrent_Name = GM_Base->Chess_Current->Chess_Name;
	TEnumAsByte <enum_ChessTeam> LCurrent_Color = GM_Base->Chess_Current->Chess_Color;
	FString LCurrent_Names = GM_Base->Chess_Current->Table_Pos_Name;

	TEnumAsByte <enum_ChessName> LNext_Name = GM_Base->Chess_Next->Chess_Name;
	TEnumAsByte <enum_ChessTeam> LNext_Color = GM_Base->Chess_Next->Chess_Color;
	FString LNext_Names = GM_Base->Chess_Next->Table_Pos_Name;

	GM_Base->Chess_Next->Chess_Name = GM_Base->Chess_Current->Chess_Name;
	GM_Base->Chess_Next->Chess_Color = GM_Base->Chess_Current->Chess_Color;
	
	TArray<AActor*> TablePartAll;
	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			if (TablePart->Table_Pos_Current == GM_Base->Chess_Current->Table_Pos_Current)
			{
				TablePart->Chess_Name = Note;
				TablePart->Chess_Color = None;
				break;
			}
		}
	}

	F_Chess_CheckPos(0);

	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			if (TablePart->Chess_Name == King && TablePart->Chess_Color == GM_Base->CheyHod && Enumy_Chess_All.Contains(TablePart))
			{
				LCanMove = false;
			}
		}
	}

	if (LCanMove)
	{


		TArray<AActor*> BaseChessAll;
		BaseChessAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AbaseChess::StaticClass(), BaseChessAll);
		for (auto It = BaseChessAll.CreateIterator(); It; It++)
		{
			AbaseChess* BaseChess = Cast<AbaseChess>(*It);
			if (BaseChess)
			{
				if (BaseChess->GetActorLocation().X == GM_Base->Chess_Current->GetActorLocation().X && BaseChess->GetActorLocation().Y == GM_Base->Chess_Current->GetActorLocation().Y)
				{
					FVector NewLocation;
					NewLocation.X = GM_Base->Chess_Next->GetActorLocation().X;
					NewLocation.Y = GM_Base->Chess_Next->GetActorLocation().Y;
					NewLocation.Z = BaseChess->GetActorLocation().Z;

					BaseChess->SetActorLocation(NewLocation);

					break;
				}
			}
		}

		F_ClearAllTable();

		if (GM_Base->Chess_Current->Table_Pos_Current.Y + 2.0f == GM_Base->Chess_Next->Table_Pos_Current.Y || GM_Base->Chess_Current->Table_Pos_Current.Y - 2.0f == GM_Base->Chess_Next->Table_Pos_Current.Y)
		{
			Chess_FightPlace = true;
		}

		//gm_Base->wHistory->ENewZapis()
		GM_Base->WidgetHistory->E_NewZapis(LCurrent_Name, LCurrent_Names, LNext_Names, GM_Base->CheyHod);
		
		return true;

	}
	else
	{
		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == GM_Base->Chess_Next->Table_Pos_Current)
				{
					TablePart->Chess_Name = LNext_Name;
					TablePart->Chess_Color = LNext_Color;

					break;

				}
			}
		}

		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == GM_Base->Chess_Current->Table_Pos_Current)
				{
					TablePart->Chess_Name = LCurrent_Name;
					TablePart->Chess_Color = LCurrent_Color;
					
					break;
				}
			}
		}

		return false;

	}

	//return false;
}

//--------------------------------------------------------------------------------
bool ATablePart::F_Pawn_Attack() //Ok
{
	//Get Game Mode
	AChessCPPGameModeBase* GM_Base;
	GM_Base = Cast<AChessCPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	//local var
	bool CanMove = true;

	TEnumAsByte <enum_ChessName> Current_Name = GM_Base->Chess_Current->Chess_Name;
	TEnumAsByte <enum_ChessTeam> Current_Color = GM_Base->Chess_Current->Chess_Color;
	FString Current_Names = GM_Base->Chess_Current->Table_Pos_Name;

	TEnumAsByte <enum_ChessName> Next_Name = GM_Base->Chess_Next->Chess_Name;
	TEnumAsByte <enum_ChessTeam> Next_Color = GM_Base->Chess_Next->Chess_Color;
	FString Next_Names = GM_Base->Chess_Next->Table_Pos_Name;

	GM_Base->Chess_Next->Chess_Name = GM_Base->Chess_Current->Chess_Name;
	GM_Base->Chess_Next->Chess_Color = GM_Base->Chess_Current->Chess_Color;

	TArray<AActor*> TablePartAll;
	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			if (TablePart->Table_Pos_Current == GM_Base->Chess_Current->Table_Pos_Current)
			{
				TablePart->Chess_Name = Note;
				TablePart->Chess_Color = None;
				break;
			}
		}
	}

	F_Chess_CheckPos(0);

	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			if (TablePart->Chess_Name == King && TablePart->Chess_Color == GM_Base->CheyHod && Enumy_Chess_All.Contains(TablePart))
			{
				CanMove = false;
			}
		}
	}

	if (CanMove)
	{
		if (Next_Name != Note)
		{
			TArray<AActor*> BaseChessAll;
			BaseChessAll.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AbaseChess::StaticClass(), BaseChessAll);
			for (auto It = BaseChessAll.CreateIterator(); It; It++)
			{
				AbaseChess* BaseChess = Cast<AbaseChess>(*It);
				if (BaseChess)
				{
					if (BaseChess->GetActorLocation().X == GM_Base->Chess_Next->GetActorLocation().X && BaseChess->GetActorLocation().Y == GM_Base->Chess_Next->GetActorLocation().Y)
					{
						BaseChess->Destroy();
						break;
					}
				}
			}

			BaseChessAll.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AbaseChess::StaticClass(), BaseChessAll);
			for (auto It = BaseChessAll.CreateIterator(); It; It++)
			{
				AbaseChess* BaseChess = Cast<AbaseChess>(*It);
				if (BaseChess)
				{
					if (BaseChess->GetActorLocation().X == GM_Base->Chess_Current->GetActorLocation().X && BaseChess->GetActorLocation().Y == GM_Base->Chess_Current->GetActorLocation().Y)
					{
						FVector NewLocation;
						NewLocation.X = GM_Base->Chess_Next->GetActorLocation().X;
						NewLocation.Y = GM_Base->Chess_Next->GetActorLocation().Y;
						NewLocation.Z = BaseChess->GetActorLocation().Z;
						
						BaseChess->SetActorLocation(NewLocation);

						break;
					}
				}
			}

			F_ClearAllTable();

			//gm_Base->wHistory->ENewZapis()
			GM_Base->WidgetHistory->E_NewZapis(Current_Name, Current_Names, Next_Names, GM_Base->CheyHod);

			return true;

		}
		else
		{
			switch (GM_Base->CheyHod)
			{
			    case None: { break;}
				
				case White:
				{
					TablePartAll.Empty();
					UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
					for (auto It = TablePartAll.CreateIterator(); It; It++)
					{
						ATablePart* TablePart = Cast<ATablePart>(*It);
						if (TablePart)
						{
							FVector2D NewCheckLocation;
							NewCheckLocation.X = GM_Base->Chess_Next->Table_Pos_Current.X;
							NewCheckLocation.Y = GM_Base->Chess_Next->Table_Pos_Current.Y - 1.0f;

							if (TablePart->Table_Pos_Current == NewCheckLocation)
							{

								TArray<AActor*> BaseChessAll;
								BaseChessAll.Empty();
								UGameplayStatics::GetAllActorsOfClass(GetWorld(), AbaseChess::StaticClass(), BaseChessAll);
								for (auto It1 = BaseChessAll.CreateIterator(); It1; It1++)
								{
									AbaseChess* BaseChess = Cast<AbaseChess>(*It1);
									if (BaseChess)
									{
										if (BaseChess->GetActorLocation().X == TablePart->GetActorLocation().X && BaseChess->GetActorLocation().Y == TablePart->GetActorLocation().Y)
										{
											BaseChess->Destroy();

											break;
										}
									}
								}
								break;


							}
						}
					}

					TArray<AActor*> BaseChessAll;
					BaseChessAll.Empty();
					UGameplayStatics::GetAllActorsOfClass(GetWorld(), AbaseChess::StaticClass(), BaseChessAll);
					for (auto It = BaseChessAll.CreateIterator(); It; It++)
					{
						AbaseChess* BaseChess = Cast<AbaseChess>(*It);
						if (BaseChess)
						{
							if (BaseChess->GetActorLocation().X == GM_Base->Chess_Current->GetActorLocation().X && BaseChess->GetActorLocation().Y == GM_Base->Chess_Current->GetActorLocation().Y)
							{
								FVector NewLocation;
								NewLocation.X = GM_Base->Chess_Next->GetActorLocation().X;
								NewLocation.Y = GM_Base->Chess_Next->GetActorLocation().Y;
								NewLocation.Z = BaseChess->GetActorLocation().Z;

								BaseChess->SetActorLocation(NewLocation);
								
								break;
							}
						}
					}

					F_ClearAllTable();

					//gm_Base->wHistory->ENewZapis()
					GM_Base->WidgetHistory->E_NewZapis(Current_Name, Current_Names, Next_Names, GM_Base->CheyHod);

					return true;


				}
				case Black:
				{
					TablePartAll.Empty();
					UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
					for (auto It = TablePartAll.CreateIterator(); It; It++)
					{
						ATablePart* TablePart = Cast<ATablePart>(*It);
						if (TablePart)
						{
							FVector2D NewCheckLocation;
							NewCheckLocation.X = GM_Base->Chess_Next->Table_Pos_Current.X;
							NewCheckLocation.Y = GM_Base->Chess_Next->Table_Pos_Current.Y + 1.0f;

							if (TablePart->Table_Pos_Current == NewCheckLocation)
							{

								TArray<AActor*> BaseChessAll;
								BaseChessAll.Empty();
								UGameplayStatics::GetAllActorsOfClass(GetWorld(), AbaseChess::StaticClass(), BaseChessAll);
								for (auto It1 = BaseChessAll.CreateIterator(); It1; It1++)
								{
									AbaseChess* BaseChess = Cast<AbaseChess>(*It1);
									if (BaseChess)
									{
										if (BaseChess->GetActorLocation().X == TablePart->GetActorLocation().X && BaseChess->GetActorLocation().Y == TablePart->GetActorLocation().Y)
										{
											BaseChess->Destroy();

											break;
										}
									}
								}
								break;
							}
						}
					}

					TArray<AActor*> BaseChessAll;
					BaseChessAll.Empty();
					UGameplayStatics::GetAllActorsOfClass(GetWorld(), AbaseChess::StaticClass(), BaseChessAll);
					for (auto It = BaseChessAll.CreateIterator(); It; It++)
					{
						AbaseChess* BaseChess = Cast<AbaseChess>(*It);
						if (BaseChess)
						{
							if (BaseChess->GetActorLocation().X == GM_Base->Chess_Current->GetActorLocation().X && BaseChess->GetActorLocation().Y == GM_Base->Chess_Current->GetActorLocation().Y)
							{
								FVector NewLocation;
								NewLocation.X = GM_Base->Chess_Next->GetActorLocation().X;
								NewLocation.Y = GM_Base->Chess_Next->GetActorLocation().Y;
								NewLocation.Z = BaseChess->GetActorLocation().Z;

								BaseChess->SetActorLocation(NewLocation);

								break;
							}
						}
					}

					F_ClearAllTable();

					//gm_Base->wHistory->ENewZapis()
					GM_Base->WidgetHistory->E_NewZapis(Current_Name, Current_Names, Next_Names, GM_Base->CheyHod);

					return true;

				}

			}
		}
	}
	else
	{
		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == GM_Base->Chess_Next->Table_Pos_Current)
				{
					TablePart->Chess_Name = Next_Name;
					TablePart->Chess_Color = Next_Color;
					break;
				}
			}
		}

		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == GM_Base->Chess_Current->Table_Pos_Current)
				{
					TablePart->Chess_Name = Current_Name;
					TablePart->Chess_Color = Current_Color;
					break;
				}
			}
		}

		return false;
	}

	return false;
}

//--------------------------------------------------------------------------------
void ATablePart::F_Pawn_Painting() //Ok
{

	//Get Game Mode
	AChessCPPGameModeBase* GM_Base;
	GM_Base = Cast<AChessCPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	bool LPregrada = false;

	//---- Painting Move To
	switch (Chess_Color)
	{
	    case None: {break; }
		
		case White:
		{
			TArray<AActor*> TablePartAll;
			TablePartAll.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
			for (auto It = TablePartAll.CreateIterator(); It; It++)
			{
				ATablePart* TablePart = Cast<ATablePart>(*It);
				if (TablePart)
				{
					FVector2D NewCheckLocation;
					NewCheckLocation.X = Table_Pos_Current.X;
					NewCheckLocation.Y = Table_Pos_Current.Y + 1.0f;
					
					if (TablePart->Table_Pos_Current == NewCheckLocation)
					{
						if (TablePart->Chess_Name == Note)
						{
							TablePart->StaticMesh->SetMaterial(0, Material_Green);
						}
						else { LPregrada = true; };
						
					}
				}
			}

			if (Table_Pos_Current.Y == 2.0f)
			{
				if (!LPregrada)
				{				
					TablePartAll.Empty();
				    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
				    for (auto It = TablePartAll.CreateIterator(); It; It++)
				    {
					    ATablePart* TablePart = Cast<ATablePart>(*It);
					    if (TablePart)
					    {
						    FVector2D NewCheckLocation;
						    NewCheckLocation.X = Table_Pos_Current.X;
						    NewCheckLocation.Y = Table_Pos_Current.Y + 2.0f;

						    if (TablePart->Table_Pos_Current == NewCheckLocation && TablePart->Chess_Name == Note)
						    {
							    TablePart->StaticMesh->SetMaterial(0, Material_Green);
						    }
					    }
				    }

				}

			}
			
			break;
		}
		case Black:
		{
			TArray<AActor*> TablePartAll;
			TablePartAll.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
			for (auto It = TablePartAll.CreateIterator(); It; It++)
			{
				ATablePart* TablePart = Cast<ATablePart>(*It);
				if (TablePart)
				{
					FVector2D NewCheckLocation;
					NewCheckLocation.X = Table_Pos_Current.X;
					NewCheckLocation.Y = Table_Pos_Current.Y - 1.0f;

					if (TablePart->Table_Pos_Current == NewCheckLocation)
					{
						if (TablePart->Chess_Name == Note)
						{
							TablePart->StaticMesh->SetMaterial(0, Material_Green);
						}
						else { LPregrada = true; };
					}
				}
			}

			if (Table_Pos_Current.Y == 7.0f)
			{
				if (!LPregrada)
				{
					TablePartAll.Empty();
					UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
					for (auto It = TablePartAll.CreateIterator(); It; It++)
					{
						ATablePart* TablePart = Cast<ATablePart>(*It);
						if (TablePart)
						{
							FVector2D NewCheckLocation;
							NewCheckLocation.X = Table_Pos_Current.X;
							NewCheckLocation.Y = Table_Pos_Current.Y - 2.0f;

							if (TablePart->Table_Pos_Current == NewCheckLocation && TablePart->Chess_Name == Note)
							{
								TablePart->StaticMesh->SetMaterial(0, Material_Green);
							}
						}
					}
				}


			}

			break;
		}

	}
	//---- Painting Attack
	switch (Chess_Color)
	{
	    case None: {break; }

	    case White:
	    {
			TArray<AActor*> TablePartAll;
			TablePartAll.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
			for (auto It = TablePartAll.CreateIterator(); It; It++)
			{
				ATablePart* TablePart = Cast<ATablePart>(*It);
				if (TablePart)
				{
					FVector2D NewCheckLocation;
					NewCheckLocation.X = Table_Pos_Current.X + 1.0f;
					NewCheckLocation.Y = Table_Pos_Current.Y + 1.0f;
					
					if (TablePart->Table_Pos_Current == NewCheckLocation && TablePart->Chess_Name != Note && TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Red);
						break;
					}
				}
			}

			TablePartAll.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
			for (auto It = TablePartAll.CreateIterator(); It; It++)
			{
				ATablePart* TablePart = Cast<ATablePart>(*It);
				if (TablePart)
				{
					FVector2D NewCheckLocation;
					NewCheckLocation.X = Table_Pos_Current.X - 1.0f;
					NewCheckLocation.Y = Table_Pos_Current.Y + 1.0f;

					if (TablePart->Table_Pos_Current == NewCheckLocation && TablePart->Chess_Name != Note && TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Red);
						break;
					}
				}
			}


		    break;
	    }
	    case Black:
	    {
			TArray<AActor*> TablePartAll;
			TablePartAll.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
			for (auto It = TablePartAll.CreateIterator(); It; It++)
			{
				ATablePart* TablePart = Cast<ATablePart>(*It);
				if (TablePart)
				{
					FVector2D NewCheckLocation;
					NewCheckLocation.X = Table_Pos_Current.X + 1.0f;
					NewCheckLocation.Y = Table_Pos_Current.Y - 1.0f;

					if (TablePart->Table_Pos_Current == NewCheckLocation && TablePart->Chess_Name != Note && TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Red);
						break;
					}
				}
			}

			TablePartAll.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
			for (auto It = TablePartAll.CreateIterator(); It; It++)
			{
				ATablePart* TablePart = Cast<ATablePart>(*It);
				if (TablePart)
				{
					FVector2D NewCheckLocation;
					NewCheckLocation.X = Table_Pos_Current.X - 1.0f;
					NewCheckLocation.Y = Table_Pos_Current.Y - 1.0f;

					if (TablePart->Table_Pos_Current == NewCheckLocation && TablePart->Chess_Name != Note && TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Red);
						break;
					}
				}
			}

		    break;
	    }

	}
	//---- Attack For FightPlace
	switch (Chess_Color)
	{
	    case None: {break; }

	    case White:
	    {
			TArray<AActor*> TablePartAll;
			TablePartAll.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
			for (auto It = TablePartAll.CreateIterator(); It; It++)
			{
				FVector2D NewCheckLocation;
				NewCheckLocation.X = Table_Pos_Current.X + 1.0f;
				NewCheckLocation.Y = Table_Pos_Current.Y;

				ATablePart* TablePart = Cast<ATablePart>(*It);
				if (TablePart)
				{
					if (TablePart->Table_Pos_Current == NewCheckLocation && TablePart->Chess_Name == Pawn && TablePart->Chess_FightPlace == true)
					{
						TArray<AActor*> TablePartAll_1;
						TablePartAll_1.Empty();
						UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
						for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
						{
							FVector2D NewCheckLocation_1;
							NewCheckLocation_1.X = Table_Pos_Current.X + 1.0f;
							NewCheckLocation_1.Y = Table_Pos_Current.Y + 1.0f;

							ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
							if (TablePart_1)
							{
								if (TablePart_1->Table_Pos_Current == NewCheckLocation_1)
								{
									TablePart_1->StaticMesh->SetMaterial(0, Material_Red);
								}
							}
						}
					}
				}
			}

			TablePartAll.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
			for (auto It = TablePartAll.CreateIterator(); It; It++)
			{
				FVector2D NewCheckLocation;
				NewCheckLocation.X = Table_Pos_Current.X - 1.0f;
				NewCheckLocation.Y = Table_Pos_Current.Y;

				ATablePart* TablePart = Cast<ATablePart>(*It);
				if (TablePart)
				{
					if (TablePart->Table_Pos_Current == NewCheckLocation && TablePart->Chess_Name == Pawn && TablePart->Chess_FightPlace == true)
					{
						TArray<AActor*> TablePartAll_1;
						TablePartAll_1.Empty();
						UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
						for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
						{
							FVector2D NewCheckLocation_1;
							NewCheckLocation_1.X = Table_Pos_Current.X - 1.0f;
							NewCheckLocation_1.Y = Table_Pos_Current.Y + 1.0f;

							ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
							if (TablePart_1)
							{
								if (TablePart_1->Table_Pos_Current == NewCheckLocation_1)
								{
									TablePart_1->StaticMesh->SetMaterial(0, Material_Red);
								}
							}
						}
					}
				}
			}

		    break;
	    }
	    case Black:
	    {
			TArray<AActor*> TablePartAll;
			TablePartAll.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
			for (auto It = TablePartAll.CreateIterator(); It; It++)
			{
				FVector2D NewCheckLocation;
				NewCheckLocation.X = Table_Pos_Current.X + 1.0f;
				NewCheckLocation.Y = Table_Pos_Current.Y;

				ATablePart* TablePart = Cast<ATablePart>(*It);
				if (TablePart)
				{
					if (TablePart->Table_Pos_Current == NewCheckLocation && TablePart->Chess_Name == Pawn && TablePart->Chess_FightPlace == true)
					{
						TArray<AActor*> TablePartAll_1;
						TablePartAll_1.Empty();
						UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
						for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
						{
							FVector2D NewCheckLocation_1;
							NewCheckLocation_1.X = Table_Pos_Current.X + 1.0f;
							NewCheckLocation_1.Y = Table_Pos_Current.Y - 1.0f;

							ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
							if (TablePart_1)
							{
								if (TablePart_1->Table_Pos_Current == NewCheckLocation_1)
								{
									TablePart_1->StaticMesh->SetMaterial(0, Material_Red);
								}
							}
						}
					}
				}
			}

			TablePartAll.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
			for (auto It = TablePartAll.CreateIterator(); It; It++)
			{
				FVector2D NewCheckLocation;
				NewCheckLocation.X = Table_Pos_Current.X - 1.0f;
				NewCheckLocation.Y = Table_Pos_Current.Y;

				ATablePart* TablePart = Cast<ATablePart>(*It);
				if (TablePart)
				{
					if (TablePart->Table_Pos_Current == NewCheckLocation && TablePart->Chess_Name == Pawn && TablePart->Chess_FightPlace == true)
					{
						TArray<AActor*> TablePartAll_1;
						TablePartAll_1.Empty();
						UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
						for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
						{
							FVector2D NewCheckLocation_1;
							NewCheckLocation_1.X = Table_Pos_Current.X - 1.0f;
							NewCheckLocation_1.Y = Table_Pos_Current.Y - 1.0f;

							ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
							if (TablePart_1)
							{
								if (TablePart_1->Table_Pos_Current == NewCheckLocation_1)
								{
									TablePart_1->StaticMesh->SetMaterial(0, Material_Red);
								}
							}
						}
					}
				}
			}

		    break;
	    }

	}


}

//--------------------------------------------------------------------------------
bool ATablePart::F_Knight_Move()
{
	//Get Game Mode
	AChessCPPGameModeBase* GM_Base;
	GM_Base = Cast<AChessCPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	//local var
	bool LCanMove = true;

	TEnumAsByte <enum_ChessName> LCurrent_Name = GM_Base->Chess_Current->Chess_Name;
	TEnumAsByte <enum_ChessTeam> LCurrent_Color = GM_Base->Chess_Current->Chess_Color;
	FString LCurrent_Names = GM_Base->Chess_Current->Table_Pos_Name;

	TEnumAsByte <enum_ChessName> LNext_Name = GM_Base->Chess_Next->Chess_Name;
	TEnumAsByte <enum_ChessTeam> LNext_Color = GM_Base->Chess_Next->Chess_Color;
	FString LNext_Names = GM_Base->Chess_Next->Table_Pos_Name;

	GM_Base->Chess_Next->Chess_Name = GM_Base->Chess_Current->Chess_Name;
	GM_Base->Chess_Next->Chess_Color = GM_Base->Chess_Current->Chess_Color;

	TArray<AActor*> TablePartAll;
	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			if (TablePart->Table_Pos_Current == GM_Base->Chess_Current->Table_Pos_Current)
			{
				TablePart->Chess_Name = Note;
				TablePart->Chess_Color = None;
				
				break;
			}
		}
	}

	F_Chess_CheckPos(0);

	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			if (TablePart->Chess_Name == King && TablePart->Chess_Color == GM_Base->CheyHod && Enumy_Chess_All.Contains(TablePart))
			{
				LCanMove = false;
			}
		}
	}

	if (LCanMove)
	{
		TArray<AActor*> BaseChessAll;
		BaseChessAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AbaseChess::StaticClass(), BaseChessAll);
		for (auto It = BaseChessAll.CreateIterator(); It; It++)
		{
			AbaseChess* BaseChess = Cast<AbaseChess>(*It);
			if (BaseChess)
			{
				if (BaseChess->GetActorLocation().X == GM_Base->Chess_Current->GetActorLocation().X && BaseChess->GetActorLocation().Y == GM_Base->Chess_Current->GetActorLocation().Y)
				{				
					FVector NewLocation;
				    NewLocation.X = GM_Base->Chess_Next->GetActorLocation().X;
				    NewLocation.Y = GM_Base->Chess_Next->GetActorLocation().Y;
				    NewLocation.Z = BaseChess->GetActorLocation().Z;

					BaseChess->SetActorLocation(NewLocation);

					break;
				}
			}
		}

		F_ClearAllTable();

		//gm_Base->wHistory->ENewZapis()
		GM_Base->WidgetHistory->E_NewZapis(LCurrent_Name, LCurrent_Names, LNext_Names, GM_Base->CheyHod);

		return true;
	}

	else
	{
		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == GM_Base->Chess_Next->Table_Pos_Current)
				{
					TablePart->Chess_Name = LNext_Name;
					TablePart->Chess_Color = LNext_Color;

					break;
				}
			}
		}

		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == GM_Base->Chess_Current->Table_Pos_Current)
				{
					TablePart->Chess_Name = LCurrent_Name;
					TablePart->Chess_Color = LCurrent_Color;

					break;
				}
			}
		}

		return false;
	};

	//return false;
}

//--------------------------------------------------------------------------------
bool ATablePart::F_Knight_Attack()
{
	//Get Game Mode
	AChessCPPGameModeBase* GM_Base;
	GM_Base = Cast<AChessCPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	//local var
	bool LCanMove = true;

	TEnumAsByte <enum_ChessName> LCurrent_Name = GM_Base->Chess_Current->Chess_Name;
	TEnumAsByte <enum_ChessTeam> LCurrent_Color = GM_Base->Chess_Current->Chess_Color;
	FString LCurrent_Names = GM_Base->Chess_Current->Table_Pos_Name;

	TEnumAsByte <enum_ChessName> LNext_Name = GM_Base->Chess_Next->Chess_Name;
	TEnumAsByte <enum_ChessTeam> LNext_Color = GM_Base->Chess_Next->Chess_Color;
	FString LNext_Names = GM_Base->Chess_Next->Table_Pos_Name;

	GM_Base->Chess_Next->Chess_Name = GM_Base->Chess_Current->Chess_Name;
	GM_Base->Chess_Next->Chess_Color = GM_Base->Chess_Current->Chess_Color;

	TArray<AActor*> TablePartAll;
	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			if (TablePart->Table_Pos_Current == GM_Base->Chess_Current->Table_Pos_Current)
			{
				TablePart->Chess_Name = Note;
				TablePart->Chess_Color = None;

				break;
			}
		}
	}

	F_Chess_CheckPos(0);

	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			if (TablePart->Chess_Name == King && TablePart->Chess_Color == GM_Base->CheyHod && Enumy_Chess_All.Contains(TablePart))
			{
				LCanMove = false;
			}
		}
	}

	if (LCanMove)
	{
		TArray<AActor*> BaseChessAll;
		BaseChessAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AbaseChess::StaticClass(), BaseChessAll);
		for (auto It = BaseChessAll.CreateIterator(); It; It++)
		{
			AbaseChess* BaseChess = Cast<AbaseChess>(*It);
			if (BaseChess)
			{
				if (BaseChess->GetActorLocation().X == GM_Base->Chess_Next->GetActorLocation().X && BaseChess->GetActorLocation().Y == GM_Base->Chess_Next->GetActorLocation().Y)
				{
					BaseChess->Destroy();

					break;
				}
			}
		}		
		
		BaseChessAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AbaseChess::StaticClass(), BaseChessAll);
		for (auto It = BaseChessAll.CreateIterator(); It; It++)
		{
			AbaseChess* BaseChess = Cast<AbaseChess>(*It);
			if (BaseChess)
			{
				if (BaseChess->GetActorLocation().X == GM_Base->Chess_Current->GetActorLocation().X && BaseChess->GetActorLocation().Y == GM_Base->Chess_Current->GetActorLocation().Y)
				{
					FVector NewLocation;
					NewLocation.X = GM_Base->Chess_Next->GetActorLocation().X;
					NewLocation.Y = GM_Base->Chess_Next->GetActorLocation().Y;
					NewLocation.Z = BaseChess->GetActorLocation().Z;

					BaseChess->SetActorLocation(NewLocation);
					
					break;
				}
			}
		}

		F_ClearAllTable();

		//gm_Base->wHistory->ENewZapis()
		GM_Base->WidgetHistory->E_NewZapis(LCurrent_Name, LCurrent_Names, LNext_Names, GM_Base->CheyHod);

		return true;
	}
	else
	{
		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == GM_Base->Chess_Next->Table_Pos_Current)
				{
					TablePart->Chess_Name = LNext_Name;
					TablePart->Chess_Color = LNext_Color;

					break;
				}
			}
		}

		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == GM_Base->Chess_Current->Table_Pos_Current)
				{
					TablePart->Chess_Name = LCurrent_Name;
					TablePart->Chess_Color = LCurrent_Color;

					break;
				}
			}
		}

		return false;
	};

	//return false;
}

//--------------------------------------------------------------------------------
void ATablePart::F_Knight_Painting()
{
	//Get Game Mode
	AChessCPPGameModeBase* GM_Base;
	GM_Base = Cast<AChessCPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	//1
	TArray<AActor*> TablePartAll;
	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			FVector2D NewLocation;
			NewLocation.X = Table_Pos_Current.X - 1.0f;
			NewLocation.Y = Table_Pos_Current.Y + 2.0f;

			if (TablePart->Table_Pos_Current == NewLocation)
			{
				if (TablePart->Chess_Name == Note)
				{
					TablePart->StaticMesh->SetMaterial(0, Material_Green);
				}
				else if (TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
				{
					TablePart->StaticMesh->SetMaterial(0, Material_Red);
				}		
			}
		}
	}
	//2
	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			FVector2D NewLocation;
			NewLocation.X = Table_Pos_Current.X + 1.0f;
			NewLocation.Y = Table_Pos_Current.Y + 2.0f;

			if (TablePart->Table_Pos_Current == NewLocation)
			{
				if (TablePart->Chess_Name == Note)
				{
					TablePart->StaticMesh->SetMaterial(0, Material_Green);
				}
				else if (TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
				{
					TablePart->StaticMesh->SetMaterial(0, Material_Red);
				}
			}
		}
	}
	//3
	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			FVector2D NewLocation;
			NewLocation.X = Table_Pos_Current.X + 2.0f;
			NewLocation.Y = Table_Pos_Current.Y + 1.0f;

			if (TablePart->Table_Pos_Current == NewLocation)
			{
				if (TablePart->Chess_Name == Note)
				{
					TablePart->StaticMesh->SetMaterial(0, Material_Green);
				}
				else if (TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
				{
					TablePart->StaticMesh->SetMaterial(0, Material_Red);
				}
			}
		}
	}
	//4
	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			FVector2D NewLocation;
			NewLocation.X = Table_Pos_Current.X + 2.0f;
			NewLocation.Y = Table_Pos_Current.Y - 1.0f;

			if (TablePart->Table_Pos_Current == NewLocation)
			{
				if (TablePart->Chess_Name == Note)
				{
					TablePart->StaticMesh->SetMaterial(0, Material_Green);
				}
				else if (TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
				{
					TablePart->StaticMesh->SetMaterial(0, Material_Red);
				}
			}
		}
	}
	//5
	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			FVector2D NewLocation;
			NewLocation.X = Table_Pos_Current.X + 1.0f;
			NewLocation.Y = Table_Pos_Current.Y - 2.0f;

			if (TablePart->Table_Pos_Current == NewLocation)
			{
				if (TablePart->Chess_Name == Note)
				{
					TablePart->StaticMesh->SetMaterial(0, Material_Green);
				}
				else if (TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
				{
					TablePart->StaticMesh->SetMaterial(0, Material_Red);
				}
			}
		}
	}
	//6
	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			FVector2D NewLocation;
			NewLocation.X = Table_Pos_Current.X - 1.0f;
			NewLocation.Y = Table_Pos_Current.Y - 2.0f;

			if (TablePart->Table_Pos_Current == NewLocation)
			{
				if (TablePart->Chess_Name == Note)
				{
					TablePart->StaticMesh->SetMaterial(0, Material_Green);
				}
				else if (TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
				{
					TablePart->StaticMesh->SetMaterial(0, Material_Red);
				}
			}
		}
	}
	//7
	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			FVector2D NewLocation;
			NewLocation.X = Table_Pos_Current.X - 2.0f;
			NewLocation.Y = Table_Pos_Current.Y + 1.0f;

			if (TablePart->Table_Pos_Current == NewLocation)
			{
				if (TablePart->Chess_Name == Note)
				{
					TablePart->StaticMesh->SetMaterial(0, Material_Green);
				}
				else if (TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
				{
					TablePart->StaticMesh->SetMaterial(0, Material_Red);
				}
			}
		}
	}
	//8
	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			FVector2D NewLocation;
			NewLocation.X = Table_Pos_Current.X - 2.0f;
			NewLocation.Y = Table_Pos_Current.Y - 1.0f;

			if (TablePart->Table_Pos_Current == NewLocation)
			{
				if (TablePart->Chess_Name == Note)
				{
					TablePart->StaticMesh->SetMaterial(0, Material_Green);
				}
				else if (TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
				{
					TablePart->StaticMesh->SetMaterial(0, Material_Red);
				}
			}
		}
	}
}

//--------------------------------------------------------------------------------
bool ATablePart::F_Bishop_Move()
{
	//Get Game Mode
	AChessCPPGameModeBase* GM_Base;
	GM_Base = Cast<AChessCPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	//local var
	bool LCanMove = true;

	TEnumAsByte <enum_ChessName> LCurrent_Name = GM_Base->Chess_Current->Chess_Name;
	TEnumAsByte <enum_ChessTeam> LCurrent_Color = GM_Base->Chess_Current->Chess_Color;
	FString LCurrent_Names = GM_Base->Chess_Current->Table_Pos_Name;

	TEnumAsByte <enum_ChessName> LNext_Name = GM_Base->Chess_Next->Chess_Name;
	TEnumAsByte <enum_ChessTeam> LNext_Color = GM_Base->Chess_Next->Chess_Color;
	FString LNext_Names = GM_Base->Chess_Next->Table_Pos_Name;

	GM_Base->Chess_Next->Chess_Name = GM_Base->Chess_Current->Chess_Name;
	GM_Base->Chess_Next->Chess_Color = GM_Base->Chess_Current->Chess_Color;

	TArray<AActor*> TablePartAll;
	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			if (TablePart->Table_Pos_Current == GM_Base->Chess_Current->Table_Pos_Current)
			{
				TablePart->Chess_Name = Note;
				TablePart->Chess_Color = None;

				break;
			}
		}
	}

	F_Chess_CheckPos(0);

	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			if (TablePart->Chess_Name == King && TablePart->Chess_Color == GM_Base->CheyHod && Enumy_Chess_All.Contains(TablePart))
			{
				LCanMove = false;
			}
		}
	}

	if (LCanMove)
	{
		TArray<AActor*> BaseChessAll;
		BaseChessAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AbaseChess::StaticClass(), BaseChessAll);
		for (auto It = BaseChessAll.CreateIterator(); It; It++)
		{
			AbaseChess* BaseChess = Cast<AbaseChess>(*It);
			if (BaseChess)
			{
				if (BaseChess->GetActorLocation().X == GM_Base->Chess_Current->GetActorLocation().X && BaseChess->GetActorLocation().Y == GM_Base->Chess_Current->GetActorLocation().Y)
				{
					FVector NewLocation;
					NewLocation.X = GM_Base->Chess_Next->GetActorLocation().X;
					NewLocation.Y = GM_Base->Chess_Next->GetActorLocation().Y;
					NewLocation.Z = BaseChess->GetActorLocation().Z;

					BaseChess->SetActorLocation(NewLocation);
					
					break;
				}
			}
		}

		F_ClearAllTable();

		//gm_Base->wHistory->ENewZapis()
		GM_Base->WidgetHistory->E_NewZapis(LCurrent_Name, LCurrent_Names, LNext_Names, GM_Base->CheyHod);

		return true;
	}
	else
	{
		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == GM_Base->Chess_Next->Table_Pos_Current)
				{
					TablePart->Chess_Name = LNext_Name;
					TablePart->Chess_Color = LNext_Color;

					break;
				}
			}
		}

		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == GM_Base->Chess_Current->Table_Pos_Current)
				{
					TablePart->Chess_Name = LCurrent_Name;
					TablePart->Chess_Color = LCurrent_Color;

					break;
				}
			}
		}

		return false;
	};


	//return false;
}

//--------------------------------------------------------------------------------
bool ATablePart::F_Bishop_Attack()
{
	//Get Game Mode
	AChessCPPGameModeBase* GM_Base;
	GM_Base = Cast<AChessCPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	//local var
	bool LCanMove = true;

	TEnumAsByte <enum_ChessName> LCurrent_Name = GM_Base->Chess_Current->Chess_Name;
	TEnumAsByte <enum_ChessTeam> LCurrent_Color = GM_Base->Chess_Current->Chess_Color;
	FString LCurrent_Names = GM_Base->Chess_Current->Table_Pos_Name;

	TEnumAsByte <enum_ChessName> LNext_Name = GM_Base->Chess_Next->Chess_Name;
	TEnumAsByte <enum_ChessTeam> LNext_Color = GM_Base->Chess_Next->Chess_Color;
	FString LNext_Names = GM_Base->Chess_Next->Table_Pos_Name;

	GM_Base->Chess_Next->Chess_Name = GM_Base->Chess_Current->Chess_Name;
	GM_Base->Chess_Next->Chess_Color = GM_Base->Chess_Current->Chess_Color;

	TArray<AActor*> TablePartAll;
	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			if (TablePart->Table_Pos_Current == GM_Base->Chess_Current->Table_Pos_Current)
			{
				TablePart->Chess_Name = Note;
				TablePart->Chess_Color = None;

				break;
			}
		}
	}

	F_Chess_CheckPos(0);

	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			if (TablePart->Chess_Name == King && TablePart->Chess_Color == GM_Base->CheyHod && Enumy_Chess_All.Contains(TablePart))
			{
				LCanMove = false;
			}
		}
	}

	if (LCanMove)
	{
		TArray<AActor*> BaseChessAll;
		BaseChessAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AbaseChess::StaticClass(), BaseChessAll);
		for (auto It = BaseChessAll.CreateIterator(); It; It++)
		{
			AbaseChess* BaseChess = Cast<AbaseChess>(*It);
			if (BaseChess)
			{
				if (BaseChess->GetActorLocation().X == GM_Base->Chess_Next->GetActorLocation().X && BaseChess->GetActorLocation().Y == GM_Base->Chess_Next->GetActorLocation().Y)
				{
					BaseChess->Destroy();

					break;
				}
			}
		}

		BaseChessAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AbaseChess::StaticClass(), BaseChessAll);
		for (auto It = BaseChessAll.CreateIterator(); It; It++)
		{
			AbaseChess* BaseChess = Cast<AbaseChess>(*It);
			if (BaseChess)
			{
				if (BaseChess->GetActorLocation().X == GM_Base->Chess_Current->GetActorLocation().X && BaseChess->GetActorLocation().Y == GM_Base->Chess_Current->GetActorLocation().Y)
				{
					FVector NewLocation;
					NewLocation.X = GM_Base->Chess_Next->GetActorLocation().X;
					NewLocation.Y = GM_Base->Chess_Next->GetActorLocation().Y;
					NewLocation.Z = BaseChess->GetActorLocation().Z;

					BaseChess->SetActorLocation(NewLocation);

					break;
				}
			}
		}

		F_ClearAllTable();

		//gm_Base->wHistory->ENewZapis()
		GM_Base->WidgetHistory->E_NewZapis(LCurrent_Name, LCurrent_Names, LNext_Names, GM_Base->CheyHod);

		return true;
	}
	else
	{
		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == GM_Base->Chess_Next->Table_Pos_Current)
				{
					TablePart->Chess_Name = LNext_Name;
					TablePart->Chess_Color = LNext_Color;

					break;
				}
			}
		}

		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == GM_Base->Chess_Current->Table_Pos_Current)
				{
					TablePart->Chess_Name = LCurrent_Name;
					TablePart->Chess_Color = LCurrent_Color;

					break;
				}
			}
		}
		return false;
	};
	//return false;
}

//--------------------------------------------------------------------------------
void ATablePart::F_Bishop_Painting()
{
	//Get Game Mode
	AChessCPPGameModeBase* GM_Base;
	GM_Base = Cast<AChessCPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	TArray<AActor*> TablePartAll;
	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);

	FVector2D LCountPos;
	LCountPos.X = Table_Pos_Current.X + 1.0f;
	LCountPos.Y = Table_Pos_Current.Y + 1.0f;

	for (int32 i = 0; i <= 7; i++)
	{
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == LCountPos)
				{
					if (TablePart->Chess_Name == Note)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Green);
						
						LCountPos.X = LCountPos.X + 1.0f;
						LCountPos.Y = LCountPos.Y + 1.0f;
					}
					else if (TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Red);

						//break;
					}
				}
			}
		}
		//break;
	}

	LCountPos.X = Table_Pos_Current.X + 1.0f;
	LCountPos.Y = Table_Pos_Current.Y - 1.0f;

	for (int32 i = 0; i <= 7; i++)
	{
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == LCountPos)
				{
					if (TablePart->Chess_Name == Note)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Green);

						LCountPos.X = LCountPos.X + 1.0f;
						LCountPos.Y = LCountPos.Y - 1.0f;
					}
					else if (TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Red);

						//break;
					}
				}
			}
		} 
		//break;
	}

	LCountPos.X = Table_Pos_Current.X - 1.0f;
	LCountPos.Y = Table_Pos_Current.Y + 1.0f;

	for (int32 i = 0; i <= 7; i++)
	{
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == LCountPos)
				{
					if (TablePart->Chess_Name == Note)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Green);

						LCountPos.X = LCountPos.X - 1.0f;
						LCountPos.Y = LCountPos.Y + 1.0f;
					}
					else if (TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Red);

						//break;
					}
				}
			}
		}
		//break;
	}

	LCountPos.X = Table_Pos_Current.X - 1.0f;
	LCountPos.Y = Table_Pos_Current.Y - 1.0f;

	for (int32 i = 0; i <= 7; i++)
	{
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == LCountPos)
				{
					if (TablePart->Chess_Name == Note)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Green);

						LCountPos.X = LCountPos.X - 1.0f;
						LCountPos.Y = LCountPos.Y - 1.0f;
					}
					else if (TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Red);

						//break;
					}
				}
			}
		}
		//break;
	}
				
}

//--------------------------------------------------------------------------------
bool ATablePart::F_Rock_Move()
{
	//Get Game Mode
	AChessCPPGameModeBase* GM_Base;
	GM_Base = Cast<AChessCPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	//local var
	bool LCanMove = true;

	TEnumAsByte <enum_ChessName> LCurrent_Name = GM_Base->Chess_Current->Chess_Name;
	TEnumAsByte <enum_ChessTeam> LCurrent_Color = GM_Base->Chess_Current->Chess_Color;
	FString LCurrent_Names = GM_Base->Chess_Current->Table_Pos_Name;

	TEnumAsByte <enum_ChessName> LNext_Name = GM_Base->Chess_Next->Chess_Name;
	TEnumAsByte <enum_ChessTeam> LNext_Color = GM_Base->Chess_Next->Chess_Color;
	FString LNext_Names = GM_Base->Chess_Next->Table_Pos_Name;

	GM_Base->Chess_Next->Chess_Name = GM_Base->Chess_Current->Chess_Name;
	GM_Base->Chess_Next->Chess_Color = GM_Base->Chess_Current->Chess_Color;

	TArray<AActor*> TablePartAll;
	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			if (TablePart->Table_Pos_Current == GM_Base->Chess_Current->Table_Pos_Current)
			{
				TablePart->Chess_Name = Note;
				TablePart->Chess_Color = None;

				break;
			}
		}
	}

	F_Chess_CheckPos(0);

	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			if (TablePart->Chess_Name == King && TablePart->Chess_Color == GM_Base->CheyHod && Enumy_Chess_All.Contains(TablePart))
			{
				LCanMove = false;
			}
		}
	}

	if (LCanMove)
	{
		TArray<AActor*> BaseChessAll;
		BaseChessAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AbaseChess::StaticClass(), BaseChessAll);
		for (auto It = BaseChessAll.CreateIterator(); It; It++)
		{
			AbaseChess* BaseChess = Cast<AbaseChess>(*It);
			if (BaseChess)
			{
				if (BaseChess->GetActorLocation().X == GM_Base->Chess_Current->GetActorLocation().X && BaseChess->GetActorLocation().Y == GM_Base->Chess_Current->GetActorLocation().Y)
				{
					FVector NewLocation;
					NewLocation.X = GM_Base->Chess_Next->GetActorLocation().X;
					NewLocation.Y = GM_Base->Chess_Next->GetActorLocation().Y;
					NewLocation.Z = BaseChess->GetActorLocation().Z;

					BaseChess->SetActorLocation(NewLocation);

					break;
				}
			}
		}
		F_ClearAllTable();

		//gm_Base->wHistory->ENewZapis()
		GM_Base->WidgetHistory->E_NewZapis(LCurrent_Name, LCurrent_Names, LNext_Names, GM_Base->CheyHod);

		return true;
	}

	else
	{
		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == GM_Base->Chess_Next->Table_Pos_Current)
				{
					TablePart->Chess_Name = LNext_Name;
					TablePart->Chess_Color = LNext_Color;

					break;
				}
			}
		}

		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == GM_Base->Chess_Current->Table_Pos_Current)
				{
					TablePart->Chess_Name = LCurrent_Name;
					TablePart->Chess_Color = LCurrent_Color;

					break;
				}
			}
		}

		return false;
	}


	//return false;
}

//--------------------------------------------------------------------------------
bool ATablePart::F_Rock_Attack()
{
	//Get Game Mode
	AChessCPPGameModeBase* GM_Base;
	GM_Base = Cast<AChessCPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	//local var
	bool LCanMove = true;

	TEnumAsByte <enum_ChessName> LCurrent_Name = GM_Base->Chess_Current->Chess_Name;
	TEnumAsByte <enum_ChessTeam> LCurrent_Color = GM_Base->Chess_Current->Chess_Color;
	FString LCurrent_Names = GM_Base->Chess_Current->Table_Pos_Name;

	TEnumAsByte <enum_ChessName> LNext_Name = GM_Base->Chess_Next->Chess_Name;
	TEnumAsByte <enum_ChessTeam> LNext_Color = GM_Base->Chess_Next->Chess_Color;
	FString LNext_Names = GM_Base->Chess_Next->Table_Pos_Name;

	GM_Base->Chess_Next->Chess_Name = GM_Base->Chess_Current->Chess_Name;
	GM_Base->Chess_Next->Chess_Color = GM_Base->Chess_Current->Chess_Color;

	TArray<AActor*> TablePartAll;
	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			if (TablePart->Table_Pos_Current == GM_Base->Chess_Current->Table_Pos_Current)
			{
				TablePart->Chess_Name = Note;
				TablePart->Chess_Color = None;

				break;
			}
		}
	}

	F_Chess_CheckPos(0);

	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			if (TablePart->Chess_Name == King && TablePart->Chess_Color == GM_Base->CheyHod && Enumy_Chess_All.Contains(TablePart))
			{
				LCanMove = false;
			}
		}
	}

	if (LCanMove)
	{
		TArray<AActor*> BaseChessAll;
		BaseChessAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AbaseChess::StaticClass(), BaseChessAll);
		for (auto It = BaseChessAll.CreateIterator(); It; It++)
		{
			AbaseChess* BaseChess = Cast<AbaseChess>(*It);
			if (BaseChess)
			{
				if (BaseChess->GetActorLocation().X == GM_Base->Chess_Next->GetActorLocation().X && BaseChess->GetActorLocation().Y == GM_Base->Chess_Next->GetActorLocation().Y)
				{
					BaseChess->Destroy();

					break;
				}
			}
		}

		//TArray<AActor*> BaseChessAll;
		BaseChessAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AbaseChess::StaticClass(), BaseChessAll);
		for (auto It = BaseChessAll.CreateIterator(); It; It++)
		{
			AbaseChess* BaseChess = Cast<AbaseChess>(*It);
			if (BaseChess)
			{
				if (BaseChess->GetActorLocation().X == GM_Base->Chess_Current->GetActorLocation().X && BaseChess->GetActorLocation().Y == GM_Base->Chess_Current->GetActorLocation().Y)
				{
					FVector NewLocation;
					NewLocation.X = GM_Base->Chess_Next->GetActorLocation().X;
					NewLocation.Y = GM_Base->Chess_Next->GetActorLocation().Y;
					NewLocation.Z = BaseChess->GetActorLocation().Z;

					BaseChess->SetActorLocation(NewLocation);
				}
			}
		}

		F_ClearAllTable();

		//gm_Base->wHistory->ENewZapis()
		GM_Base->WidgetHistory->E_NewZapis(LCurrent_Name, LCurrent_Names, LNext_Names, GM_Base->CheyHod);

		return true;
	}
	else
	{
		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == GM_Base->Chess_Next->Table_Pos_Current)
				{
					TablePart->Chess_Name = LNext_Name;
					TablePart->Chess_Color = LNext_Color;

					break;
				}
			}
		}

		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == GM_Base->Chess_Current->Table_Pos_Current)
				{
					TablePart->Chess_Name = LCurrent_Name;
					TablePart->Chess_Color = LCurrent_Color;

					break;
				}
			}
		}

		return false;
	};

	//return false;
}

//--------------------------------------------------------------------------------
void ATablePart::F_Rock_Painting()
{
	//Get Game Mode
	AChessCPPGameModeBase* GM_Base;
	GM_Base = Cast<AChessCPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	TArray<AActor*> TablePartAll;
	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);

	FVector2D LCountPos;
	LCountPos.X = Table_Pos_Current.X + 1.0f;
	LCountPos.Y = Table_Pos_Current.Y;

	for (int32 i = 0; i <= 7; i++)
	{
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == LCountPos)
				{
					if (TablePart->Chess_Name == Note)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Green);

						LCountPos.X = LCountPos.X + 1.0f;
						LCountPos.Y = LCountPos.Y;
					}
					else if (TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Red);

						//break;
					}
				}
			}
		}
		//break;
	}

	LCountPos.X = Table_Pos_Current.X - 1.0f;
	LCountPos.Y = Table_Pos_Current.Y;

	for (int32 i = 0; i <= 7; i++)
	{
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == LCountPos)
				{
					if (TablePart->Chess_Name == Note)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Green);

						LCountPos.X = LCountPos.X - 1.0f;
						LCountPos.Y = LCountPos.Y;
					}
					else if (TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Red);

						//break;
					}
				}
			}
		}
		//break;
	}

	LCountPos.X = Table_Pos_Current.X;
	LCountPos.Y = Table_Pos_Current.Y + 1.0f;

	for (int32 i = 0; i <= 7; i++)
	{
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == LCountPos)
				{
					if (TablePart->Chess_Name == Note)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Green);

						LCountPos.X = LCountPos.X;
						LCountPos.Y = LCountPos.Y + 1.0f;
					}
					else if (TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Red);

						//break;
					}
				}
			}
		}
		//break;
	}

	LCountPos.X = Table_Pos_Current.X;
	LCountPos.Y = Table_Pos_Current.Y - 1.0f;

	for (int32 i = 0; i <= 7; i++)
	{
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == LCountPos)
				{
					if (TablePart->Chess_Name == Note)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Green);

						LCountPos.X = LCountPos.X;
						LCountPos.Y = LCountPos.Y - 1.0f;
					}
					else if (TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Red);

						//break;
					}
				}
			}
		}
		//break;
	}

}

//--------------------------------------------------------------------------------
bool ATablePart::F_Queen_Move()
{
	//Get Game Mode
	AChessCPPGameModeBase* GM_Base;
	GM_Base = Cast<AChessCPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	//local var
	bool LCanMove = true;

	TEnumAsByte <enum_ChessName> LCurrent_Name = GM_Base->Chess_Current->Chess_Name;
	TEnumAsByte <enum_ChessTeam> LCurrent_Color = GM_Base->Chess_Current->Chess_Color;
	FString LCurrent_Names = GM_Base->Chess_Current->Table_Pos_Name;

	TEnumAsByte <enum_ChessName> LNext_Name = GM_Base->Chess_Next->Chess_Name;
	TEnumAsByte <enum_ChessTeam> LNext_Color = GM_Base->Chess_Next->Chess_Color;
	FString LNext_Names = GM_Base->Chess_Next->Table_Pos_Name;

	GM_Base->Chess_Next->Chess_Name = GM_Base->Chess_Current->Chess_Name;
	GM_Base->Chess_Next->Chess_Color = GM_Base->Chess_Current->Chess_Color;

	TArray<AActor*> TablePartAll;
	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			if (TablePart->Table_Pos_Current == GM_Base->Chess_Current->Table_Pos_Current)
			{
				TablePart->Chess_Name = Note;
				TablePart->Chess_Color = None;

				break;
			}
		}
	}

	F_Chess_CheckPos(0);

	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			if (TablePart->Chess_Name == King && TablePart->Chess_Color == GM_Base->CheyHod && Enumy_Chess_All.Contains(TablePart))
			{
				LCanMove = false;
			}
		}
	}

	if (LCanMove)
	{
		TArray<AActor*> BaseChessAll;
		BaseChessAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AbaseChess::StaticClass(), BaseChessAll);
		for (auto It = BaseChessAll.CreateIterator(); It; It++)
		{
			AbaseChess* BaseChess = Cast<AbaseChess>(*It);
			if (BaseChess)
			{
				if (BaseChess->GetActorLocation().X == GM_Base->Chess_Current->GetActorLocation().X && BaseChess->GetActorLocation().Y == GM_Base->Chess_Current->GetActorLocation().Y)
				{
					FVector NewLocation;
					NewLocation.X = GM_Base->Chess_Next->GetActorLocation().X;
					NewLocation.Y = GM_Base->Chess_Next->GetActorLocation().Y;
					NewLocation.Z = BaseChess->GetActorLocation().Z;

					BaseChess->SetActorLocation(NewLocation);

				}
			}
		}

		F_ClearAllTable();

		//gm_Base->wHistory->ENewZapis()
		GM_Base->WidgetHistory->E_NewZapis(LCurrent_Name, LCurrent_Names, LNext_Names, GM_Base->CheyHod);

		return true;
	}
	else
	{
		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == GM_Base->Chess_Next->Table_Pos_Current)
				{
					TablePart->Chess_Name = LNext_Name;
					TablePart->Chess_Color = LNext_Color;

					break;
				}
			}
		}

		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == GM_Base->Chess_Current->Table_Pos_Current)
				{
					TablePart->Chess_Name = LCurrent_Name;
					TablePart->Chess_Color = LCurrent_Color;

					break;
				}
			}
		}

		return false;
	}

	//return false;
}

//--------------------------------------------------------------------------------
bool ATablePart::F_Queen_Attack()
{
	//Get Game Mode
	AChessCPPGameModeBase* GM_Base;
	GM_Base = Cast<AChessCPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	//local var
	bool LCanMove = true;

	TEnumAsByte <enum_ChessName> LCurrent_Name = GM_Base->Chess_Current->Chess_Name;
	TEnumAsByte <enum_ChessTeam> LCurrent_Color = GM_Base->Chess_Current->Chess_Color;
	FString LCurrent_Names = GM_Base->Chess_Current->Table_Pos_Name;

	TEnumAsByte <enum_ChessName> LNext_Name = GM_Base->Chess_Next->Chess_Name;
	TEnumAsByte <enum_ChessTeam> LNext_Color = GM_Base->Chess_Next->Chess_Color;
	FString LNext_Names = GM_Base->Chess_Next->Table_Pos_Name;

	GM_Base->Chess_Next->Chess_Name = GM_Base->Chess_Current->Chess_Name;
	GM_Base->Chess_Next->Chess_Color = GM_Base->Chess_Current->Chess_Color;

	TArray<AActor*> TablePartAll;
	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			if (TablePart->Table_Pos_Current == GM_Base->Chess_Current->Table_Pos_Current)
			{
				TablePart->Chess_Name = Note;
				TablePart->Chess_Color = None;

				break;
			}
		}
	}

	F_Chess_CheckPos(0);

	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			if (TablePart->Chess_Name == King && TablePart->Chess_Color == GM_Base->CheyHod && Enumy_Chess_All.Contains(TablePart))
			{
				LCanMove = false;
			}
		}
	}

	if (LCanMove)
	{
		TArray<AActor*> BaseChessAll;
		BaseChessAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AbaseChess::StaticClass(), BaseChessAll);
		for (auto It = BaseChessAll.CreateIterator(); It; It++)
		{
			AbaseChess* BaseChess = Cast<AbaseChess>(*It);
			if (BaseChess)
			{
				if (BaseChess->GetActorLocation().X == GM_Base->Chess_Next->GetActorLocation().X && BaseChess->GetActorLocation().Y == GM_Base->Chess_Next->GetActorLocation().Y)
				{
					BaseChess->Destroy();
				}
			}
		}

		BaseChessAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AbaseChess::StaticClass(), BaseChessAll);
		for (auto It = BaseChessAll.CreateIterator(); It; It++)
		{
			AbaseChess* BaseChess = Cast<AbaseChess>(*It);
			if (BaseChess)
			{
				if (BaseChess->GetActorLocation().X == GM_Base->Chess_Current->GetActorLocation().X && BaseChess->GetActorLocation().Y == GM_Base->Chess_Current->GetActorLocation().Y)
				{
					FVector NewLocation;
					NewLocation.X = GM_Base->Chess_Next->GetActorLocation().X;
					NewLocation.Y = GM_Base->Chess_Next->GetActorLocation().Y;
					NewLocation.Z = BaseChess->GetActorLocation().Z;
					
					BaseChess->SetActorLocation(NewLocation);

					break;

				}
			}
		}

		F_ClearAllTable();

		//gm_Base->wHistory->ENewZapis()
		GM_Base->WidgetHistory->E_NewZapis(LCurrent_Name, LCurrent_Names, LNext_Names, GM_Base->CheyHod);

		return true;
	}
	else
	{
		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == GM_Base->Chess_Next->Table_Pos_Current)
				{
					TablePart->Chess_Name = LNext_Name;
					TablePart->Chess_Color = LNext_Color;

					break;
				}
			}
		}

		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == GM_Base->Chess_Current->Table_Pos_Current)
				{
					TablePart->Chess_Name = LCurrent_Name;
					TablePart->Chess_Color = LCurrent_Color;

					break;
				}
			}
		}

		return false;
	};

	//return false;
}

//--------------------------------------------------------------------------------
void ATablePart::F_Queen_Painting()
{
	//Get Game Mode
	AChessCPPGameModeBase* GM_Base;
	GM_Base = Cast<AChessCPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	TArray<AActor*> TablePartAll;
	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);

	FVector2D LCountPos;
	LCountPos.X = Table_Pos_Current.X + 1.0f;
	LCountPos.Y = Table_Pos_Current.Y + 1.0f;

	for (int32 i = 0; i <= 7; i++)
	{
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == LCountPos)
				{
					if (TablePart->Chess_Name == Note)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Green);

						LCountPos.X = LCountPos.X + 1.0f;
						LCountPos.Y = LCountPos.Y + 1.0f;
					}
					else if (TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Red);

						//break;
					}
				}
			}
		}
		//break;
	}

	LCountPos.X = Table_Pos_Current.X + 1.0f;
	LCountPos.Y = Table_Pos_Current.Y - 1.0f;

	for (int32 i = 0; i <= 7; i++)
	{
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == LCountPos)
				{
					if (TablePart->Chess_Name == Note)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Green);

						LCountPos.X = LCountPos.X + 1.0f;
						LCountPos.Y = LCountPos.Y - 1.0f;
					}
					else if (TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Red);

						//break;
					}
				}
			}
		}
		//break;
	}

	LCountPos.X = Table_Pos_Current.X - 1.0f;
	LCountPos.Y = Table_Pos_Current.Y + 1.0f;

	for (int32 i = 0; i <= 7; i++)
	{
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == LCountPos)
				{
					if (TablePart->Chess_Name == Note)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Green);

						LCountPos.X = LCountPos.X - 1.0f;
						LCountPos.Y = LCountPos.Y + 1.0f;
					}
					else if (TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Red);

						//break;
					}
				}
			}
		}
		//break;
	}

	LCountPos.X = Table_Pos_Current.X - 1.0f;
	LCountPos.Y = Table_Pos_Current.Y - 1.0f;

	for (int32 i = 0; i <= 7; i++)
	{
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == LCountPos)
				{
					if (TablePart->Chess_Name == Note)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Green);

						LCountPos.X = LCountPos.X - 1.0f;
						LCountPos.Y = LCountPos.Y - 1.0f;
					}
					else if (TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Red);

						//break;
					}
				}
			}
		}
		//break;
	}

	LCountPos.X = Table_Pos_Current.X + 1.0f;
	LCountPos.Y = Table_Pos_Current.Y;

	for (int32 i = 0; i <= 7; i++)
	{
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == LCountPos)
				{
					if (TablePart->Chess_Name == Note)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Green);

						LCountPos.X = LCountPos.X + 1.0f;
						LCountPos.Y = LCountPos.Y;
					}
					else if (TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Red);

						//break;
					}
				}
			}
		}
		//break;
	}

	LCountPos.X = Table_Pos_Current.X - 1.0f;
	LCountPos.Y = Table_Pos_Current.Y;

	for (int32 i = 0; i <= 7; i++)
	{
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == LCountPos)
				{
					if (TablePart->Chess_Name == Note)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Green);

						LCountPos.X = LCountPos.X - 1.0f;
						LCountPos.Y = LCountPos.Y;
					}
					else if (TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Red);

						//break;
					}
				}
			}
		}
		//break;
	}

	LCountPos.X = Table_Pos_Current.X;
	LCountPos.Y = Table_Pos_Current.Y + 1.0f;

	for (int32 i = 0; i <= 7; i++)
	{
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == LCountPos)
				{
					if (TablePart->Chess_Name == Note)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Green);

						LCountPos.X = LCountPos.X;
						LCountPos.Y = LCountPos.Y + 1.0f;
					}
					else if (TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Red);

						//break;
					}
				}
			}
		}
		//break;
	}

	LCountPos.X = Table_Pos_Current.X;
	LCountPos.Y = Table_Pos_Current.Y - 1.0f;

	for (int32 i = 0; i <= 7; i++)
	{
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == LCountPos)
				{
					if (TablePart->Chess_Name == Note)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Green);

						LCountPos.X = LCountPos.X;
						LCountPos.Y = LCountPos.Y - 1.0f;
					}
					else if (TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
					{
						TablePart->StaticMesh->SetMaterial(0, Material_Red);

						//break;
					}
				}
			}
		}
		//break;
	}
}

//--------------------------------------------------------------------------------
bool ATablePart::F_King_Move()
{
	//Get Game Mode
	AChessCPPGameModeBase* GM_Base;
	GM_Base = Cast<AChessCPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	//local var
	bool LCanMove = true;

	TEnumAsByte <enum_ChessName> LCurrent_Name = GM_Base->Chess_Current->Chess_Name;
	TEnumAsByte <enum_ChessTeam> LCurrent_Color = GM_Base->Chess_Current->Chess_Color;
	FString LCurrent_Names = GM_Base->Chess_Current->Table_Pos_Name;

	TEnumAsByte <enum_ChessName> LNext_Name = GM_Base->Chess_Next->Chess_Name;
	TEnumAsByte <enum_ChessTeam> LNext_Color = GM_Base->Chess_Next->Chess_Color;
	FString LNext_Names = GM_Base->Chess_Next->Table_Pos_Name;

	GM_Base->Chess_Next->Chess_Name = GM_Base->Chess_Current->Chess_Name;
	GM_Base->Chess_Next->Chess_Color = GM_Base->Chess_Current->Chess_Color;

	TArray<AActor*> TablePartAll;
	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			if (TablePart->Table_Pos_Current == GM_Base->Chess_Current->Table_Pos_Current)
			{
				TablePart->Chess_Name = Note;
				TablePart->Chess_Color = None;

				break;
			}
		}
	}

	F_Chess_CheckPos(0);

	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			if (TablePart->Chess_Name == King && TablePart->Chess_Color == GM_Base->CheyHod && Enumy_Chess_All.Contains(TablePart))
			{
				LCanMove = false;
			}
		}
	}

	if (LCanMove)
	{
		TArray<AActor*> BaseChessAll;
		BaseChessAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AbaseChess::StaticClass(), BaseChessAll);
		for (auto It = BaseChessAll.CreateIterator(); It; It++)
		{
			AbaseChess* BaseChess = Cast<AbaseChess>(*It);
			if (BaseChess)
			{
				if (BaseChess->GetActorLocation().X == GM_Base->Chess_Current->GetActorLocation().X && BaseChess->GetActorLocation().Y == GM_Base->Chess_Current->GetActorLocation().Y)
				{
					FVector NewLocation;
					NewLocation.X = GM_Base->Chess_Next->GetActorLocation().X;
					NewLocation.Y = GM_Base->Chess_Next->GetActorLocation().Y;
					NewLocation.Z = BaseChess->GetActorLocation().Z;

					BaseChess->SetActorLocation(NewLocation);

					break;
				}
			}
		}

		F_ClearAllTable();

		switch (GM_Base->CheyHod)
		{
		    //case Note: {break; }
			case White:
			{
				GM_Base->IsCanCasting_White = true;
				break;
			}
			case Black:
			{
				GM_Base->IsCanCasting_Black = true;
				break;
			}
		}

		//gm_Base->wHistory->ENewZapis()
		GM_Base->WidgetHistory->E_NewZapis(LCurrent_Name, LCurrent_Names, LNext_Names, GM_Base->CheyHod);

		return true;
	}
	else
	{
		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == GM_Base->Chess_Next->Table_Pos_Current)
				{
					TablePart->Chess_Name = LNext_Name;
					TablePart->Chess_Color = LNext_Color;

					break;
				}
			}
		}

		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == GM_Base->Chess_Current->Table_Pos_Current)
				{
					TablePart->Chess_Name = LCurrent_Name;
					TablePart->Chess_Color = LCurrent_Color;

					break;
				}
			}
		}

		return false;
	};


	//return false;
}

//--------------------------------------------------------------------------------
bool ATablePart::F_King_Attack()
{
	//Get Game Mode
	AChessCPPGameModeBase* GM_Base;
	GM_Base = Cast<AChessCPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	//local var
	bool LCanMove = true;

	TEnumAsByte <enum_ChessName> LCurrent_Name = GM_Base->Chess_Current->Chess_Name;
	TEnumAsByte <enum_ChessTeam> LCurrent_Color = GM_Base->Chess_Current->Chess_Color;
	FString LCurrent_Names = GM_Base->Chess_Current->Table_Pos_Name;

	TEnumAsByte <enum_ChessName> LNext_Name = GM_Base->Chess_Next->Chess_Name;
	TEnumAsByte <enum_ChessTeam> LNext_Color = GM_Base->Chess_Next->Chess_Color;
	FString LNext_Names = GM_Base->Chess_Next->Table_Pos_Name;

	GM_Base->Chess_Next->Chess_Name = GM_Base->Chess_Current->Chess_Name;
	GM_Base->Chess_Next->Chess_Color = GM_Base->Chess_Current->Chess_Color;

	TArray<AActor*> TablePartAll;
	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			if (TablePart->Table_Pos_Current == GM_Base->Chess_Current->Table_Pos_Current)
			{
				TablePart->Chess_Name = Note;
				TablePart->Chess_Color = None;

				break;
			}
		}
	}

	F_Chess_CheckPos(0);

	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			if (TablePart->Chess_Name == King && TablePart->Chess_Color == GM_Base->CheyHod && Enumy_Chess_All.Contains(TablePart))
			{
				LCanMove = false;
			}
		}
	}

	if (LCanMove)
	{
		TArray<AActor*> BaseChessAll;
		BaseChessAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AbaseChess::StaticClass(), BaseChessAll);
		for (auto It = BaseChessAll.CreateIterator(); It; It++)
		{
			AbaseChess* BaseChess = Cast<AbaseChess>(*It);
			if (BaseChess)
			{
				if (BaseChess->GetActorLocation().X == GM_Base->Chess_Next->GetActorLocation().X && BaseChess->GetActorLocation().Y == GM_Base->Chess_Next->GetActorLocation().Y)
				{
					BaseChess->Destroy();
					
					break;
				}
			}
		}

		BaseChessAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AbaseChess::StaticClass(), BaseChessAll);
		for (auto It = BaseChessAll.CreateIterator(); It; It++)
		{
			AbaseChess* BaseChess = Cast<AbaseChess>(*It);
			if (BaseChess)
			{
				if (BaseChess->GetActorLocation().X == GM_Base->Chess_Current->GetActorLocation().X && BaseChess->GetActorLocation().Y == GM_Base->Chess_Current->GetActorLocation().Y)
				{
					FVector NewLocation;
					NewLocation.X = GM_Base->Chess_Next->GetActorLocation().X;
					NewLocation.Y = GM_Base->Chess_Next->GetActorLocation().Y;
					NewLocation.Z = BaseChess->GetActorLocation().Z;

					BaseChess->SetActorLocation(NewLocation);

					break;
				}
			}
		}

		F_ClearAllTable();

		switch (GM_Base->CheyHod)
		{
		//case Note: {break; }
		case White:
		{
			GM_Base->IsCanCasting_White = true;
			break;
		}
		case Black:
		{
			GM_Base->IsCanCasting_Black = false;
			break;
		}
		}

		//gm_Base->wHistory->ENewZapis()
		GM_Base->WidgetHistory->E_NewZapis(LCurrent_Name, LCurrent_Names, LNext_Names, GM_Base->CheyHod);

		return true;
	}

	else
	{
		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == GM_Base->Chess_Next->Table_Pos_Current)
				{
					TablePart->Chess_Name = LNext_Name;
					TablePart->Chess_Color = LNext_Color;

					break;
				}
			}
		}

		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == GM_Base->Chess_Current->Table_Pos_Current)
				{
					TablePart->Chess_Name = LCurrent_Name;
					TablePart->Chess_Color = LCurrent_Color;

					break;
				}
			}
		}

		return false;
	};


	//return false;
}

//--------------------------------------------------------------------------------
void ATablePart::F_King_Painting()
{
	//Get Game Mode
	AChessCPPGameModeBase* GM_Base;
	GM_Base = Cast<AChessCPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	TArray<AActor*> TablePartAll;
	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);

	FVector2D LCountPos;
	LCountPos.X = Table_Pos_Current.X + 1.0f;
	LCountPos.Y = Table_Pos_Current.Y + 1.0f;

	for (int32 i = 0; i <= 0; i++)
	{
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (!Enumy_Chess_All.Contains(TablePart))
				{
					if (TablePart->Table_Pos_Current == LCountPos)
					{
						if (TablePart->Chess_Name == Note)
						{
							TablePart->StaticMesh->SetMaterial(0, Material_Green);

							//LCountPos.X = LCountPos.X + 1.0f;
							//LCountPos.Y = LCountPos.Y + 1.0f;
						}
						else if (TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
						{
							TablePart->StaticMesh->SetMaterial(0, Material_Red);

							break;
						}
					}

				}
			}
		}
		break;
	}

	LCountPos.X = Table_Pos_Current.X + 1.0f;
	LCountPos.Y = Table_Pos_Current.Y - 1.0f;

	for (int32 i = 0; i <= 0; i++)
	{
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (!Enumy_Chess_All.Contains(TablePart))
				{
					if (TablePart->Table_Pos_Current == LCountPos)
					{
						if (TablePart->Chess_Name == Note)
						{
							TablePart->StaticMesh->SetMaterial(0, Material_Green);

							//LCountPos.X = LCountPos.X + 1.0f;
							//LCountPos.Y = LCountPos.Y - 1.0f;
						}
						else if (TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
						{
							TablePart->StaticMesh->SetMaterial(0, Material_Red);

							break;
						}
					}
				}
			}
		}
		break;
	}

	LCountPos.X = Table_Pos_Current.X - 1.0f;
	LCountPos.Y = Table_Pos_Current.Y + 1.0f;

	for (int32 i = 0; i <= 0; i++)
	{
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (!Enumy_Chess_All.Contains(TablePart))
				{
					if (TablePart->Table_Pos_Current == LCountPos)
					{
						if (TablePart->Chess_Name == Note)
						{
							TablePart->StaticMesh->SetMaterial(0, Material_Green);

							//LCountPos.X = LCountPos.X - 1.0f;
							//LCountPos.Y = LCountPos.Y + 1.0f;
						}
						else if (TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
						{
							TablePart->StaticMesh->SetMaterial(0, Material_Red);

							break;
						}
					}
				}
			}
		}
		break;
	}

	LCountPos.X = Table_Pos_Current.X - 1.0f;
	LCountPos.Y = Table_Pos_Current.Y - 1.0f;

	for (int32 i = 0; i <= 0; i++)
	{
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (!Enumy_Chess_All.Contains(TablePart))
				{
					if (TablePart->Table_Pos_Current == LCountPos)
					{
						if (TablePart->Chess_Name == Note)
						{
							TablePart->StaticMesh->SetMaterial(0, Material_Green);

							//LCountPos.X = LCountPos.X - 1.0f;
							//LCountPos.Y = LCountPos.Y - 1.0f;
						}
						else if (TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
						{
							TablePart->StaticMesh->SetMaterial(0, Material_Red);

							break;
						}
					}
				}
			}
		}
		break;
	}

	LCountPos.X = Table_Pos_Current.X + 1.0f;
	LCountPos.Y = Table_Pos_Current.Y;

	for (int32 i = 0; i <= 0; i++)
	{
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (!Enumy_Chess_All.Contains(TablePart))
				{
					if (TablePart->Table_Pos_Current == LCountPos)
					{
						if (TablePart->Chess_Name == Note)
						{
							TablePart->StaticMesh->SetMaterial(0, Material_Green);

							//LCountPos.X = LCountPos.X + 1.0f;
							//LCountPos.Y = LCountPos.Y;
						}
						else if (TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
						{
							TablePart->StaticMesh->SetMaterial(0, Material_Red);

							break;
						}
					}
				}
			}
		}
		break;
	}

	LCountPos.X = Table_Pos_Current.X - 1.0f;
	LCountPos.Y = Table_Pos_Current.Y;

	for (int32 i = 0; i <= 0; i++)
	{
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (!Enumy_Chess_All.Contains(TablePart))
				{
					if (TablePart->Table_Pos_Current == LCountPos)
					{
						if (TablePart->Chess_Name == Note)
						{
							TablePart->StaticMesh->SetMaterial(0, Material_Green);

							//LCountPos.X = LCountPos.X - 1.0f;
							//LCountPos.Y = LCountPos.Y;
						}
						else if (TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
						{
							TablePart->StaticMesh->SetMaterial(0, Material_Red);

							break;
						}
					}
				}
			}
		}
		break;
	}

	LCountPos.X = Table_Pos_Current.X;
	LCountPos.Y = Table_Pos_Current.Y + 1.0f;

	for (int32 i = 0; i <= 0; i++)
	{
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (!Enumy_Chess_All.Contains(TablePart))
				{
					if (TablePart->Table_Pos_Current == LCountPos)
					{
						if (TablePart->Chess_Name == Note)
						{
							TablePart->StaticMesh->SetMaterial(0, Material_Green);

							//LCountPos.X = LCountPos.X;
							//LCountPos.Y = LCountPos.Y + 1.0f;
						}
						else if (TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
						{
							TablePart->StaticMesh->SetMaterial(0, Material_Red);

							break;
						}
					}
				}
			}
		}
		break;
	}

	LCountPos.X = Table_Pos_Current.X;
	LCountPos.Y = Table_Pos_Current.Y - 1.0f;

	for (int32 i = 0; i <= 0; i++)
	{
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (!Enumy_Chess_All.Contains(TablePart))
				{
					if (TablePart->Table_Pos_Current == LCountPos)
					{
						if (TablePart->Chess_Name == Note)
						{
							TablePart->StaticMesh->SetMaterial(0, Material_Green);

							//LCountPos.X = LCountPos.X;
							//LCountPos.Y = LCountPos.Y - 1.0f;
						}
						else if (TablePart->Chess_Color != GM_Base->Chess_Current->Chess_Color)
						{
							TablePart->StaticMesh->SetMaterial(0, Material_Red);

							break;
						}
					}
				}
			}
		}
		break;
	}

}

//--------------------------------------------------------------------------------
void ATablePart::F_Chess_CheckPos(int32 NewParam)
{
	//Get Game Mode
	AChessCPPGameModeBase* GM_Base;
	GM_Base = Cast<AChessCPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	Enumy_Chess_Pawn.Empty();
	Enumy_Chess_Knight.Empty();
	Enumy_Chess_Bishop.Empty();
	Enumy_Chess_Rock.Empty();
	Enumy_Chess_Queen.Empty();
	Enumy_Chess_King.Empty();
	Enumy_Chess_All.Empty();

	switch (NewParam)
	{
	    case 0:
	    {
			TArray<AActor*> TablePartAll;
			TablePartAll.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
			for (auto It = TablePartAll.CreateIterator(); It; It++)
			{
				ATablePart* TablePart = Cast<ATablePart>(*It);
				if (TablePart)
				{
					if (TablePart->Chess_Color != GM_Base->CheyHod)
					{
						switch (TablePart->Chess_Name)
						{
						    //case None:{break;}
							case Pawn:
							{
								Enumy_Chess_Pawn.Add(TablePart);
								break;
							}
							case Knight:
							{
								Enumy_Chess_Knight.Add(TablePart);
								break;
							}
							case Bishop:
							{
								Enumy_Chess_Bishop.Add(TablePart);
								break;
							}
							case Rock:
							{
								Enumy_Chess_Rock.Add(TablePart);
								break;
							}
							case Queen:
							{
								Enumy_Chess_Queen.Add(TablePart);
								break;
							}
							case King:
							{
								Enumy_Chess_King.Add(TablePart);
								break;
							}
						}
					}
				}
			}

			F_Chess_CheckPos2();

		    break;
	    }
	    case 1:
	    {
			TArray<AActor*> TablePartAll;
			TablePartAll.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
			for (auto It = TablePartAll.CreateIterator(); It; It++)
			{
				ATablePart* TablePart = Cast<ATablePart>(*It);
				if (TablePart)
				{
					if (TablePart->Chess_Color == GM_Base->CheyHod)
					{
						switch (TablePart->Chess_Name)
						{
						//case None:{break;}
						case Pawn:
						{
							Enumy_Chess_Pawn.Add(TablePart);
							break;
						}
						case Knight:
						{
							Enumy_Chess_Knight.Add(TablePart);
							break;
						}
						case Bishop:
						{
							Enumy_Chess_Bishop.Add(TablePart);
							break;
						}
						case Rock:
						{
							Enumy_Chess_Rock.Add(TablePart);
							break;
						}
						case Queen:
						{
							Enumy_Chess_Queen.Add(TablePart);
							break;
						}
						case King:
						{
							Enumy_Chess_King.Add(TablePart);
							break;
						}
						}
					}
				}
			}

			F_Chess_CheckPos2();

		    break;
	    }

	    default:
		    break;
	}
}

void ATablePart::F_Chess_CheckPos2()
{
	//Get Game Mode
	AChessCPPGameModeBase* GM_Base;
	GM_Base = Cast<AChessCPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	//---- Pawn
	switch (GM_Base->CheyHod)
	{
	    //case Note:{ break;}
		
		case White:
		{
			
			for (auto It = Enumy_Chess_Pawn.CreateIterator(); It; It++)
			{
				//ATablePart* TablePart = *It;
				ATablePart* TablePart = Cast<ATablePart>(*It);
				if (TablePart)
				{
					TArray<AActor*> TablePartAll_1;
					TablePartAll_1.Empty();
					UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
					for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
					{
						ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
						if (TablePart_1)
						{
					        FVector2D NewChechLocation;
					        NewChechLocation.X = TablePart->Table_Pos_Current.X - 1.0f;
					        NewChechLocation.Y = TablePart->Table_Pos_Current.Y - 1.0f;

							if (TablePart_1->Table_Pos_Current == NewChechLocation && TablePart_1->Chess_Color != TablePart->Chess_Color)
							{
								//TablePart_1->StaticMesh->SetMaterial(0, Material_Blue);

								if (!Enumy_Chess_All.Contains(TablePart_1))
								{
									Enumy_Chess_All.Add(TablePart_1);
								}
							}
						}
					}

				}
			}


			for (auto It = Enumy_Chess_Pawn.CreateIterator(); It; It++)
			{
				//ATablePart* TablePart = *It;
				ATablePart* TablePart = Cast<ATablePart>(*It);
				if (TablePart)
				{
					TArray<AActor*> TablePartAll_1;
					TablePartAll_1.Empty();
					UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
					for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
					{
						ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
						if (TablePart_1)
						{
							FVector2D NewChechLocation;
							NewChechLocation.X = TablePart->Table_Pos_Current.X + 1.0f;
							NewChechLocation.Y = TablePart->Table_Pos_Current.Y - 1.0f;

							if (TablePart_1->Table_Pos_Current == NewChechLocation && TablePart_1->Chess_Color != TablePart->Chess_Color)
							{
								//TablePart_1->StaticMesh->SetMaterial(0, Material_Blue);

								if (!Enumy_Chess_All.Contains(TablePart_1))
								{
									Enumy_Chess_All.Add(TablePart_1);
								}
							}
						}
					}

				}
			}

			break;
		}
		case Black:
		{
			
			for (auto It = Enumy_Chess_Pawn.CreateIterator(); It; It++)
			{
				//ATablePart* TablePart = *It;
				ATablePart* TablePart = Cast<ATablePart>(*It);
				if (TablePart)
				{
					TArray<AActor*> TablePartAll_1;
					TablePartAll_1.Empty();
					UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
					for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
					{
						ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
						if (TablePart_1)
						{
							FVector2D NewChechLocation;
							NewChechLocation.X = TablePart->Table_Pos_Current.X - 1.0f;
							NewChechLocation.Y = TablePart->Table_Pos_Current.Y + 1.0f;

							if (TablePart_1->Table_Pos_Current == NewChechLocation && TablePart_1->Chess_Color != TablePart->Chess_Color)
							{
								//TablePart_1->StaticMesh->SetMaterial(0, Material_Blue);

								if (!Enumy_Chess_All.Contains(TablePart_1))
								{
									Enumy_Chess_All.Add(TablePart_1);
								}
							}
						}
					}

				}
			}

			for (auto It = Enumy_Chess_Pawn.CreateIterator(); It; It++)
			{
				//ATablePart* TablePart = *It;
				ATablePart* TablePart = Cast<ATablePart>(*It);
				if (TablePart)
				{
					TArray<AActor*> TablePartAll_1;
					TablePartAll_1.Empty();
					UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
					for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
					{
						ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
						if (TablePart_1)
						{
							FVector2D NewChechLocation;
							NewChechLocation.X = TablePart->Table_Pos_Current.X + 1.0f;
							NewChechLocation.Y = TablePart->Table_Pos_Current.Y + 1.0f;

							if (TablePart_1->Table_Pos_Current == NewChechLocation && TablePart_1->Chess_Color != TablePart->Chess_Color)
							{
								//TablePart_1->StaticMesh->SetMaterial(0, Material_Blue);

								if (!Enumy_Chess_All.Contains(TablePart_1))
								{
									Enumy_Chess_All.Add(TablePart_1);
								}
							}
						}
					}

				}
			}

			break;
		}


	}

	//---- Knight
	//1
	for (auto It = Enumy_Chess_Knight.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = *It;
		if (TablePart)
		{
			FVector2D NewChechLocation;
			NewChechLocation.X = TablePart->Table_Pos_Current.X - 1.0f;
			NewChechLocation.Y = TablePart->Table_Pos_Current.Y + 2.0f;

			TArray<AActor*> TablePartAll_1;
			TablePartAll_1.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
			for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
			{
				ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
				if (TablePart_1)
				{
					if (TablePart_1->Table_Pos_Current == NewChechLocation && TablePart_1->Chess_Color != TablePart->Chess_Color)
					{
						//TablePart_1->StaticMesh->SetMaterial(0, Material_Blue);

						if (!Enumy_Chess_All.Contains(TablePart_1))
						{
							Enumy_Chess_All.Add(TablePart_1);
						}
					}
				}
			}
		}
	}
	//2
	for (auto It = Enumy_Chess_Knight.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = *It;
		if (TablePart)
		{
			FVector2D NewChechLocation;
			NewChechLocation.X = TablePart->Table_Pos_Current.X + 1.0f;
			NewChechLocation.Y = TablePart->Table_Pos_Current.Y + 2.0f;

			TArray<AActor*> TablePartAll_1;
			TablePartAll_1.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
			for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
			{
				ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
				if (TablePart_1)
				{
					if (TablePart_1->Table_Pos_Current == NewChechLocation && TablePart_1->Chess_Color != TablePart->Chess_Color)
					{
						//TablePart_1->StaticMesh->SetMaterial(0, Material_Blue);

						if (!Enumy_Chess_All.Contains(TablePart_1))
						{
							Enumy_Chess_All.Add(TablePart_1);
						}
					}
				}
			}
		}
	}
	//3
	for (auto It = Enumy_Chess_Knight.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = *It;
		if (TablePart)
		{
			FVector2D NewChechLocation;
			NewChechLocation.X = TablePart->Table_Pos_Current.X + 2.0f;
			NewChechLocation.Y = TablePart->Table_Pos_Current.Y + 1.0f;

			TArray<AActor*> TablePartAll_1;
			TablePartAll_1.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
			for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
			{
				ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
				if (TablePart_1)
				{
					if (TablePart_1->Table_Pos_Current == NewChechLocation && TablePart_1->Chess_Color != TablePart->Chess_Color)
					{
						//TablePart_1->StaticMesh->SetMaterial(0, Material_Blue);

						if (!Enumy_Chess_All.Contains(TablePart_1))
						{
							Enumy_Chess_All.Add(TablePart_1);
						}
					}
				}
			}
		}
	}
	//4
	for (auto It = Enumy_Chess_Knight.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = *It;
		if (TablePart)
		{
			FVector2D NewChechLocation;
			NewChechLocation.X = TablePart->Table_Pos_Current.X + 2.0f;
			NewChechLocation.Y = TablePart->Table_Pos_Current.Y - 1.0f;

			TArray<AActor*> TablePartAll_1;
			TablePartAll_1.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
			for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
			{
				ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
				if (TablePart_1)
				{
					if (TablePart_1->Table_Pos_Current == NewChechLocation && TablePart_1->Chess_Color != TablePart->Chess_Color)
					{
						//TablePart_1->StaticMesh->SetMaterial(0, Material_Blue);

						if (!Enumy_Chess_All.Contains(TablePart_1))
						{
							Enumy_Chess_All.Add(TablePart_1);
						}
					}
				}
			}
		}
	}

	//5
	for (auto It = Enumy_Chess_Knight.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = *It;
		if (TablePart)
		{
			FVector2D NewChechLocation;
			NewChechLocation.X = TablePart->Table_Pos_Current.X + 1.0f;
			NewChechLocation.Y = TablePart->Table_Pos_Current.Y - 2.0f;

			TArray<AActor*> TablePartAll_1;
			TablePartAll_1.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
			for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
			{
				ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
				if (TablePart_1)
				{
					if (TablePart_1->Table_Pos_Current == NewChechLocation && TablePart_1->Chess_Color != TablePart->Chess_Color)
					{
						//TablePart_1->StaticMesh->SetMaterial(0, Material_Blue);

						if (!Enumy_Chess_All.Contains(TablePart_1))
						{
							Enumy_Chess_All.Add(TablePart_1);
						}
					}
				}
			}
		}
	}
	//6
	for (auto It = Enumy_Chess_Knight.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = *It;
		if (TablePart)
		{
			FVector2D NewChechLocation;
			NewChechLocation.X = TablePart->Table_Pos_Current.X - 1.0f;
			NewChechLocation.Y = TablePart->Table_Pos_Current.Y - 2.0f;

			TArray<AActor*> TablePartAll_1;
			TablePartAll_1.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
			for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
			{
				ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
				if (TablePart_1)
				{
					if (TablePart_1->Table_Pos_Current == NewChechLocation && TablePart_1->Chess_Color != TablePart->Chess_Color)
					{
						//TablePart_1->StaticMesh->SetMaterial(0, Material_Blue);

						if (!Enumy_Chess_All.Contains(TablePart_1))
						{
							Enumy_Chess_All.Add(TablePart_1);
						}
					}
				}
			}
		}
	}
	//7
	for (auto It = Enumy_Chess_Knight.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = *It;
		if (TablePart)
		{
			FVector2D NewChechLocation;
			NewChechLocation.X = TablePart->Table_Pos_Current.X - 2.0f;
			NewChechLocation.Y = TablePart->Table_Pos_Current.Y + 1.0f;

			TArray<AActor*> TablePartAll_1;
			TablePartAll_1.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
			for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
			{
				ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
				if (TablePart_1)
				{
					if (TablePart_1->Table_Pos_Current == NewChechLocation && TablePart_1->Chess_Color != TablePart->Chess_Color)
					{
						//TablePart_1->StaticMesh->SetMaterial(0, Material_Blue);

						if (!Enumy_Chess_All.Contains(TablePart_1))
						{
							Enumy_Chess_All.Add(TablePart_1);
						}
					}
				}
			}
		}
	}
	//8
	for (auto It = Enumy_Chess_Knight.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = *It;
		if (TablePart)
		{
			FVector2D NewChechLocation;
			NewChechLocation.X = TablePart->Table_Pos_Current.X - 2.0f;
			NewChechLocation.Y = TablePart->Table_Pos_Current.Y - 1.0f;

			TArray<AActor*> TablePartAll_1;
			TablePartAll_1.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
			for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
			{
				ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
				if (TablePart_1)
				{
					if (TablePart_1->Table_Pos_Current == NewChechLocation && TablePart_1->Chess_Color != TablePart->Chess_Color)
					{
						//TablePart_1->StaticMesh->SetMaterial(0, Material_Blue);

						if (!Enumy_Chess_All.Contains(TablePart_1))
						{
							Enumy_Chess_All.Add(TablePart_1);
						}
					}
				}
			}
		}
	}

	//---- Bishop
	//1
	for (auto It = Enumy_Chess_Bishop.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = *It;
		if (TablePart)
		{
			FVector2D NewChechLocation;
			NewChechLocation.X = TablePart->Table_Pos_Current.X + 1.0f;
			NewChechLocation.Y = TablePart->Table_Pos_Current.Y + 1.0f;

			for (int32 i = 0; i <= 7; i++)
			{
				TArray<AActor*> TablePartAll_1;
				TablePartAll_1.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
				for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
				{
					ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
					if (TablePart_1)
					{
						if (TablePart_1->Table_Pos_Current == NewChechLocation)
						{
							if (TablePart_1->Chess_Name == Note || (TablePart_1->Chess_Name == King && TablePart_1->Chess_Color != TablePart->Chess_Color))
							{
								//TablePart_1->StaticMesh->SetMaterial(0, Material_Blue);

								NewChechLocation.X = NewChechLocation.X + 1.0f;
								NewChechLocation.Y = NewChechLocation.Y + 1.0f;

								if (!Enumy_Chess_All.Contains(TablePart_1))
								{
									Enumy_Chess_All.Add(TablePart_1);
								}
							}
							else { break; }
						}
					}
				} break;

			} //break;
			
		}
	}
	//2
	for (auto It = Enumy_Chess_Bishop.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = *It;
		if (TablePart)
		{
			FVector2D NewChechLocation;
			NewChechLocation.X = TablePart->Table_Pos_Current.X + 1.0f;
			NewChechLocation.Y = TablePart->Table_Pos_Current.Y - 1.0f;

			for (int32 i = 0; i <= 7; i++)
			{
				TArray<AActor*> TablePartAll_1;
				TablePartAll_1.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
				for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
				{
					ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
					if (TablePart_1)
					{
						if (TablePart_1->Table_Pos_Current == NewChechLocation)
						{
							if (TablePart_1->Chess_Name == Note || (TablePart_1->Chess_Name == King && TablePart_1->Chess_Color != TablePart->Chess_Color))
							{
								//TablePart_1->StaticMesh->SetMaterial(0, Material_Blue);

								NewChechLocation.X = NewChechLocation.X + 1.0f;
								NewChechLocation.Y = NewChechLocation.Y - 1.0f;

								if (!Enumy_Chess_All.Contains(TablePart_1))
								{
									Enumy_Chess_All.Add(TablePart_1);
								}
							}
							else { break; }
						}
					}
				} break;

			} //break;

		}
	}
	//3
	for (auto It = Enumy_Chess_Bishop.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = *It;
		if (TablePart)
		{
			FVector2D NewChechLocation;
			NewChechLocation.X = TablePart->Table_Pos_Current.X - 1.0f;
			NewChechLocation.Y = TablePart->Table_Pos_Current.Y + 1.0f;

			for (int32 i = 0; i <= 7; i++)
			{
				TArray<AActor*> TablePartAll_1;
				TablePartAll_1.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
				for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
				{
					ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
					if (TablePart_1)
					{
						if (TablePart_1->Table_Pos_Current == NewChechLocation)
						{
							if (TablePart_1->Chess_Name == Note || (TablePart_1->Chess_Name == King && TablePart_1->Chess_Color != TablePart->Chess_Color))
							{
								//TablePart_1->StaticMesh->SetMaterial(0, Material_Blue);

								NewChechLocation.X = NewChechLocation.X - 1.0f;
								NewChechLocation.Y = NewChechLocation.Y + 1.0f;

								if (!Enumy_Chess_All.Contains(TablePart_1))
								{
									Enumy_Chess_All.Add(TablePart_1);
								}
							}
							else { break; }
						}
					}
				} break;

			} //break;

		}
	}
	//4
	for (auto It = Enumy_Chess_Bishop.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = *It;
		if (TablePart)
		{
			FVector2D NewChechLocation;
			NewChechLocation.X = TablePart->Table_Pos_Current.X - 1.0f;
			NewChechLocation.Y = TablePart->Table_Pos_Current.Y - 1.0f;

			for (int32 i = 0; i <= 7; i++)
			{
				TArray<AActor*> TablePartAll_1;
				TablePartAll_1.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
				for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
				{
					ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
					if (TablePart_1)
					{
						if (TablePart_1->Table_Pos_Current == NewChechLocation)
						{
							if (TablePart_1->Chess_Name == Note || (TablePart_1->Chess_Name == King && TablePart_1->Chess_Color != TablePart->Chess_Color))
							{
								//TablePart_1->StaticMesh->SetMaterial(0, Material_Blue);

								NewChechLocation.X = NewChechLocation.X - 1.0f;
								NewChechLocation.Y = NewChechLocation.Y - 1.0f;

								if (!Enumy_Chess_All.Contains(TablePart_1))
								{
									Enumy_Chess_All.Add(TablePart_1);
								}
							}
							else { break; }
						}
					}
				} break;

			} //break;

		}
	}

	//---- Rock
		//1
	for (auto It = Enumy_Chess_Rock.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = *It;
		if (TablePart)
		{
			FVector2D NewChechLocation;
			NewChechLocation.X = TablePart->Table_Pos_Current.X + 1.0f;
			NewChechLocation.Y = TablePart->Table_Pos_Current.Y;

			for (int32 i = 0; i <= 7; i++)
			{
				TArray<AActor*> TablePartAll_1;
				TablePartAll_1.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
				for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
				{
					ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
					if (TablePart_1)
					{
						if (TablePart_1->Table_Pos_Current == NewChechLocation)
						{
							if (TablePart_1->Chess_Name == Note || (TablePart_1->Chess_Name == King && TablePart_1->Chess_Color != TablePart->Chess_Color))
							{
								//TablePart_1->StaticMesh->SetMaterial(0, Material_Blue);

								NewChechLocation.X = NewChechLocation.X + 1.0f;
								NewChechLocation.Y = NewChechLocation.Y;

								if (!Enumy_Chess_All.Contains(TablePart_1))
								{
									Enumy_Chess_All.Add(TablePart_1);
								}
							}
							else {/*break;*/}
						}
					}
				} //break;

			} //break;

		}
	}
	//2
	for (auto It = Enumy_Chess_Rock.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = *It;
		if (TablePart)
		{
			FVector2D NewChechLocation;
			NewChechLocation.X = TablePart->Table_Pos_Current.X;
			NewChechLocation.Y = TablePart->Table_Pos_Current.Y - 1.0f;

			for (int32 i = 0; i <= 7; i++)
			{
				TArray<AActor*> TablePartAll_1;
				TablePartAll_1.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
				for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
				{
					ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
					if (TablePart_1)
					{
						if (TablePart_1->Table_Pos_Current == NewChechLocation)
						{
							if (TablePart_1->Chess_Name == Note || (TablePart_1->Chess_Name == King && TablePart_1->Chess_Color != TablePart->Chess_Color))
							{
								//TablePart_1->StaticMesh->SetMaterial(0, Material_Blue);

								NewChechLocation.X = NewChechLocation.X;
								NewChechLocation.Y = NewChechLocation.Y - 1.0f;

								if (!Enumy_Chess_All.Contains(TablePart_1))
								{
									Enumy_Chess_All.Add(TablePart_1);
								}
							}
							else {/*break;*/}
						}
					}
				} //break;

			} //break;

		}
	}
	//3
	for (auto It = Enumy_Chess_Rock.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = *It;
		if (TablePart)
		{
			FVector2D NewChechLocation;
			NewChechLocation.X = TablePart->Table_Pos_Current.X - 1.0f;
			NewChechLocation.Y = TablePart->Table_Pos_Current.Y;

			for (int32 i = 0; i <= 7; i++)
			{
				TArray<AActor*> TablePartAll_1;
				TablePartAll_1.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
				for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
				{
					ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
					if (TablePart_1)
					{
						if (TablePart_1->Table_Pos_Current == NewChechLocation)
						{
							if (TablePart_1->Chess_Name == Note || (TablePart_1->Chess_Name == King && TablePart_1->Chess_Color != TablePart->Chess_Color))
							{
								//TablePart_1->StaticMesh->SetMaterial(0, Material_Blue);

								NewChechLocation.X = NewChechLocation.X - 1.0f;
								NewChechLocation.Y = NewChechLocation.Y;

								if (!Enumy_Chess_All.Contains(TablePart_1))
								{
									Enumy_Chess_All.Add(TablePart_1);
								}
							}
							else {/*break;*/}
						}
					}
				} //break;

			} //break;

		}
	}
	//4
	for (auto It = Enumy_Chess_Rock.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = *It;
		if (TablePart)
		{
			FVector2D NewChechLocation;
			NewChechLocation.X = TablePart->Table_Pos_Current.X;
			NewChechLocation.Y = TablePart->Table_Pos_Current.Y + 1.0f;

			for (int32 i = 0; i <= 7; i++)
			{
				TArray<AActor*> TablePartAll_1;
				TablePartAll_1.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
				for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
				{
					ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
					if (TablePart_1)
					{
						if (TablePart_1->Table_Pos_Current == NewChechLocation)
						{
							if (TablePart_1->Chess_Name == Note || (TablePart_1->Chess_Name == King && TablePart_1->Chess_Color != TablePart->Chess_Color))
							{
								//TablePart_1->StaticMesh->SetMaterial(0, Material_Blue);

								NewChechLocation.X = NewChechLocation.X;
								NewChechLocation.Y = NewChechLocation.Y + 1.0f;

								if (!Enumy_Chess_All.Contains(TablePart_1))
								{
									Enumy_Chess_All.Add(TablePart_1);
								}
							}
							else {/*break;*/}
						}
					}
				} //break;

			} //break;

		}
	}

	//---- Queen
		//1
	for (auto It = Enumy_Chess_Queen.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = *It;
		if (TablePart)
		{
			FVector2D NewChechLocation;
			NewChechLocation.X = TablePart->Table_Pos_Current.X + 1.0f;
			NewChechLocation.Y = TablePart->Table_Pos_Current.Y + 1.0f;

			for (int32 i = 0; i <= 7; i++)
			{
				TArray<AActor*> TablePartAll_1;
				TablePartAll_1.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
				for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
				{
					ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
					if (TablePart_1)
					{
						if (TablePart_1->Table_Pos_Current == NewChechLocation)
						{
							if (TablePart_1->Chess_Name == Note || (TablePart_1->Chess_Name == King && TablePart_1->Chess_Color != TablePart->Chess_Color))
							{
								//TablePart_1->StaticMesh->SetMaterial(0, Material_Blue);

								NewChechLocation.X = NewChechLocation.X + 1.0f;
								NewChechLocation.Y = NewChechLocation.Y + 1.0f;

								if (!Enumy_Chess_All.Contains(TablePart_1))
								{
									Enumy_Chess_All.Add(TablePart_1);
								}
							}
							else {/*break;*/}
						}
					}
				} //break;

			} //break;

		}
	}
	//2
	for (auto It = Enumy_Chess_Queen.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = *It;
		if (TablePart)
		{
			FVector2D NewChechLocation;
			NewChechLocation.X = TablePart->Table_Pos_Current.X + 1.0f;
			NewChechLocation.Y = TablePart->Table_Pos_Current.Y - 1.0f;

			for (int32 i = 0; i <= 7; i++)
			{
				TArray<AActor*> TablePartAll_1;
				TablePartAll_1.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
				for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
				{
					ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
					if (TablePart_1)
					{
						if (TablePart_1->Table_Pos_Current == NewChechLocation)
						{
							if (TablePart_1->Chess_Name == Note || (TablePart_1->Chess_Name == King && TablePart_1->Chess_Color != TablePart->Chess_Color))
							{
								//TablePart_1->StaticMesh->SetMaterial(0, Material_Blue);

								NewChechLocation.X = NewChechLocation.X + 1.0f;
								NewChechLocation.Y = NewChechLocation.Y - 1.0f;

								if (!Enumy_Chess_All.Contains(TablePart_1))
								{
									Enumy_Chess_All.Add(TablePart_1);
								}
							}
							else {/*break;*/}
						}
					}
				} //break;

			} //break;

		}
	}
	//3
	for (auto It = Enumy_Chess_Queen.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = *It;
		if (TablePart)
		{
			FVector2D NewChechLocation;
			NewChechLocation.X = TablePart->Table_Pos_Current.X - 1.0f;
			NewChechLocation.Y = TablePart->Table_Pos_Current.Y + 1.0f;

			for (int32 i = 0; i <= 7; i++)
			{
				TArray<AActor*> TablePartAll_1;
				TablePartAll_1.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
				for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
				{
					ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
					if (TablePart_1)
					{
						if (TablePart_1->Table_Pos_Current == NewChechLocation)
						{
							if (TablePart_1->Chess_Name == Note || (TablePart_1->Chess_Name == King && TablePart_1->Chess_Color != TablePart->Chess_Color))
							{
								//TablePart_1->StaticMesh->SetMaterial(0, Material_Blue);

								NewChechLocation.X = NewChechLocation.X - 1.0f;
								NewChechLocation.Y = NewChechLocation.Y + 1.0f;

								if (!Enumy_Chess_All.Contains(TablePart_1))
								{
									Enumy_Chess_All.Add(TablePart_1);
								}
							}
							else {/*break;*/}
						}
					}
				} //break;

			} //break;

		}
	}
	//4
	for (auto It = Enumy_Chess_Queen.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = *It;
		if (TablePart)
		{
			FVector2D NewChechLocation;
			NewChechLocation.X = TablePart->Table_Pos_Current.X - 1.0f;
			NewChechLocation.Y = TablePart->Table_Pos_Current.Y - 1.0f;

			for (int32 i = 0; i <= 7; i++)
			{
				TArray<AActor*> TablePartAll_1;
				TablePartAll_1.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
				for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
				{
					ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
					if (TablePart_1)
					{
						if (TablePart_1->Table_Pos_Current == NewChechLocation)
						{
							if (TablePart_1->Chess_Name == Note || (TablePart_1->Chess_Name == King && TablePart_1->Chess_Color != TablePart->Chess_Color))
							{
								//TablePart_1->StaticMesh->SetMaterial(0, Material_Blue);

								NewChechLocation.X = NewChechLocation.X - 1.0f;
								NewChechLocation.Y = NewChechLocation.Y - 1.0f;

								if (!Enumy_Chess_All.Contains(TablePart_1))
								{
									Enumy_Chess_All.Add(TablePart_1);
								}
							}
							else {/*break;*/}
						}
					}
				} //break;

			} //break;

		}
	}

	//5
	for (auto It = Enumy_Chess_Queen.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = *It;
		if (TablePart)
		{
			FVector2D NewChechLocation;
			NewChechLocation.X = TablePart->Table_Pos_Current.X + 1.0f;
			NewChechLocation.Y = TablePart->Table_Pos_Current.Y;

			for (int32 i = 0; i <= 7; i++)
			{
				TArray<AActor*> TablePartAll_1;
				TablePartAll_1.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
				for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
				{
					ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
					if (TablePart_1)
					{
						if (TablePart_1->Table_Pos_Current == NewChechLocation)
						{
							if (TablePart_1->Chess_Name == Note || (TablePart_1->Chess_Name == King && TablePart_1->Chess_Color != TablePart->Chess_Color))
							{
								//TablePart_1->StaticMesh->SetMaterial(0, Material_Blue);

								NewChechLocation.X = NewChechLocation.X + 1.0f;
								NewChechLocation.Y = NewChechLocation.Y;

								if (!Enumy_Chess_All.Contains(TablePart_1))
								{
									Enumy_Chess_All.Add(TablePart_1);
								}
							}
							else {/*break;*/}
						}
					}
				} //break;

			} //break;

		}
	}
	//6
	for (auto It = Enumy_Chess_Queen.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = *It;
		if (TablePart)
		{
			FVector2D NewChechLocation;
			NewChechLocation.X = TablePart->Table_Pos_Current.X;
			NewChechLocation.Y = TablePart->Table_Pos_Current.Y - 1.0f;

			for (int32 i = 0; i <= 7; i++)
			{
				TArray<AActor*> TablePartAll_1;
				TablePartAll_1.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
				for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
				{
					ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
					if (TablePart_1)
					{
						if (TablePart_1->Table_Pos_Current == NewChechLocation)
						{
							if (TablePart_1->Chess_Name == Note || (TablePart_1->Chess_Name == King && TablePart_1->Chess_Color != TablePart->Chess_Color))
							{
								//TablePart_1->StaticMesh->SetMaterial(0, Material_Blue);

								NewChechLocation.X = NewChechLocation.X;
								NewChechLocation.Y = NewChechLocation.Y - 1.0f;

								if (!Enumy_Chess_All.Contains(TablePart_1))
								{
									Enumy_Chess_All.Add(TablePart_1);
								}
							}
							else {/*break;*/ }
						}
					}
				} //break;

			} //break;

		}
	}
	//7
	for (auto It = Enumy_Chess_Queen.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = *It;
		if (TablePart)
		{
			FVector2D NewChechLocation;
			NewChechLocation.X = TablePart->Table_Pos_Current.X - 1.0f;
			NewChechLocation.Y = TablePart->Table_Pos_Current.Y;

			for (int32 i = 0; i <= 7; i++)
			{
				TArray<AActor*> TablePartAll_1;
				TablePartAll_1.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
				for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
				{
					ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
					if (TablePart_1)
					{
						if (TablePart_1->Table_Pos_Current == NewChechLocation)
						{
							if (TablePart_1->Chess_Name == Note || (TablePart_1->Chess_Name == King && TablePart_1->Chess_Color != TablePart->Chess_Color))
							{
								//TablePart_1->StaticMesh->SetMaterial(0, Material_Blue);

								NewChechLocation.X = NewChechLocation.X - 1.0f;
								NewChechLocation.Y = NewChechLocation.Y;

								if (!Enumy_Chess_All.Contains(TablePart_1))
								{
									Enumy_Chess_All.Add(TablePart_1);
								}
							}
							else { /*break;*/ }
						}
					}
				} //break;

			} //break;

		}
	}
	//8
	for (auto It = Enumy_Chess_Queen.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = *It;
		if (TablePart)
		{
			FVector2D NewChechLocation;
			NewChechLocation.X = TablePart->Table_Pos_Current.X;
			NewChechLocation.Y = TablePart->Table_Pos_Current.Y + 1.0f;

			for (int32 i = 0; i <= 7; i++)
			{
				TArray<AActor*> TablePartAll_1;
				TablePartAll_1.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
				for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
				{
					ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
					if (TablePart_1)
					{
						if (TablePart_1->Table_Pos_Current == NewChechLocation)
						{
							if (TablePart_1->Chess_Name == Note || (TablePart_1->Chess_Name == King && TablePart_1->Chess_Color != TablePart->Chess_Color))
							{
								//TablePart_1->StaticMesh->SetMaterial(0, Material_Blue);

								NewChechLocation.X = NewChechLocation.X;
								NewChechLocation.Y = NewChechLocation.Y + 1.0f;

								if (!Enumy_Chess_All.Contains(TablePart_1))
								{
									Enumy_Chess_All.Add(TablePart_1);
								}
							}
							else { /*break;*/ }
						}
					}
				} //break;

			} //break;

		}
	}

	//---- King
	//1
	for (auto It = Enumy_Chess_King.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = *It;
		if (TablePart)
		{
			FVector2D NewChechLocation;
			NewChechLocation.X = TablePart->Table_Pos_Current.X + 1.0f;
			NewChechLocation.Y = TablePart->Table_Pos_Current.Y + 1.0f;

			TArray<AActor*> TablePartAll_1;
			TablePartAll_1.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
			for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
			{
				ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
				if (TablePart_1)
				{
					if (TablePart_1->Table_Pos_Current == NewChechLocation)
					{
						if (TablePart_1->Chess_Name == Note || (TablePart_1->Chess_Name == King && TablePart_1->Chess_Color != TablePart->Chess_Color))
						{
							//TablePart_1->StaticMesh->SetMaterial(0, Material_Blue);
							
							if (!Enumy_Chess_All.Contains(TablePart_1))
							{
								Enumy_Chess_All.Add(TablePart_1);
							}
						}
					}
				}
			}
		}
	}
	//2
	for (auto It = Enumy_Chess_King.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = *It;
		if (TablePart)
		{
			FVector2D NewChechLocation;
			NewChechLocation.X = TablePart->Table_Pos_Current.X + 1.0f;
			NewChechLocation.Y = TablePart->Table_Pos_Current.Y - 1.0f;

			TArray<AActor*> TablePartAll_1;
			TablePartAll_1.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
			for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
			{
				ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
				if (TablePart_1)
				{
					if (TablePart_1->Table_Pos_Current == NewChechLocation)
					{
						if (TablePart_1->Chess_Name == Note || (TablePart_1->Chess_Name == King && TablePart_1->Chess_Color != TablePart->Chess_Color))
						{
							//TablePart_1->StaticMesh->SetMaterial(0, Material_Blue);

							if (!Enumy_Chess_All.Contains(TablePart_1))
							{
								Enumy_Chess_All.Add(TablePart_1);
							}
						}
					}
				}
			}
		}
	}
	//3
	for (auto It = Enumy_Chess_King.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = *It;
		if (TablePart)
		{
			FVector2D NewChechLocation;
			NewChechLocation.X = TablePart->Table_Pos_Current.X - 1.0f;
			NewChechLocation.Y = TablePart->Table_Pos_Current.Y + 1.0f;

			TArray<AActor*> TablePartAll_1;
			TablePartAll_1.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
			for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
			{
				ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
				if (TablePart_1)
				{
					if (TablePart_1->Table_Pos_Current == NewChechLocation)
					{
						if (TablePart_1->Chess_Name == Note || (TablePart_1->Chess_Name == King && TablePart_1->Chess_Color != TablePart->Chess_Color))
						{
							//TablePart_1->StaticMesh->SetMaterial(0, Material_Blue);

							if (!Enumy_Chess_All.Contains(TablePart_1))
							{
								Enumy_Chess_All.Add(TablePart_1);
							}
						}
					}
				}
			}
		}
	}
	//4
	for (auto It = Enumy_Chess_King.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = *It;
		if (TablePart)
		{
			FVector2D NewChechLocation;
			NewChechLocation.X = TablePart->Table_Pos_Current.X - 1.0f;
			NewChechLocation.Y = TablePart->Table_Pos_Current.Y - 1.0f;

			TArray<AActor*> TablePartAll_1;
			TablePartAll_1.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll_1);
			for (auto It_1 = TablePartAll_1.CreateIterator(); It_1; It_1++)
			{
				ATablePart* TablePart_1 = Cast<ATablePart>(*It_1);
				if (TablePart_1)
				{
					if (TablePart_1->Table_Pos_Current == NewChechLocation)
					{
						if (TablePart_1->Chess_Name == Note || (TablePart_1->Chess_Name == King && TablePart_1->Chess_Color != TablePart->Chess_Color))
						{
							//TablePart_1->StaticMesh->SetMaterial(0, Material_Blue);

							if (!Enumy_Chess_All.Contains(TablePart_1))
							{
								Enumy_Chess_All.Add(TablePart_1);
							}
						}
					}
				}
			}
		}
	}

}

//--------------------------------------------------------------------------------
void ATablePart::F_Chess_Change(ATablePart * Point, enum_ChessName ChessName)
{
	//Get Game Mode
	AChessCPPGameModeBase* GM_Base;
	GM_Base = Cast<AChessCPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	TArray<AActor*> BaseChessAll;
	BaseChessAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AbaseChess::StaticClass(), BaseChessAll);
	for (auto It = BaseChessAll.CreateIterator(); It; It++)
	{
		AbaseChess* BaseChess = Cast<AbaseChess>(*It);
		if (BaseChess)
		{
			if (BaseChess->GetActorLocation().X == Point->GetActorLocation().X && BaseChess->GetActorLocation().Y == Point->GetActorLocation().Y)
			{
				BaseChess->Destroy();

				switch (ChessName)
				{
				    //case None: { break; }

				    case Pawn:
				    {
					
					    break;
				    }
				    case Knight:
				    {
						FVector SpawnLocation = Point->GetActorLocation();
						SpawnLocation.Z = 200.f;

						FQuat SpawnRotation;
						SpawnRotation.X = 0.f;
						SpawnRotation.Y = 0.f;
						SpawnRotation.Z = 0.f;

						FTransform SpawnTransform;
						SpawnTransform.SetLocation(SpawnLocation);

						FActorSpawnParameters SpawnParameters;
						SpawnParameters.Owner = BaseChess;

						AbaseChess_Knight* ChessKnihgt = GetWorld()->SpawnActor<AbaseChess_Knight>(AbaseChess_Knight::StaticClass(), SpawnTransform, SpawnParameters);
						ChessKnihgt->SetActorLocation(SpawnLocation);

						switch (Chess_Color)
						{
						    //case Note: {break; }

							case White:
							{
								ChessKnihgt->StaticMesh->SetMaterial(0, Material_Yellow);
								break;
							}
							case Black:
							{
								ChessKnihgt->StaticMesh->SetMaterial(0, Material_Brown);
								break;
							}
						}
					    break;
				    }
				    case Bishop:
				    {
						FVector SpawnLocation = Point->GetActorLocation();
						SpawnLocation.Z = 200.f;

						FQuat SpawnRotation;
						SpawnRotation.X = 0.f;
						SpawnRotation.Y = 0.f;
						SpawnRotation.Z = 0.f;

						FTransform SpawnTransform;
						SpawnTransform.SetLocation(SpawnLocation);

						FActorSpawnParameters SpawnParameters;
						SpawnParameters.Owner = BaseChess;

						AbaseChess_Bishop* ChessBishopt = GetWorld()->SpawnActor<AbaseChess_Bishop>(AbaseChess_Bishop::StaticClass(), SpawnTransform, SpawnParameters);
						ChessBishopt->SetActorLocation(SpawnLocation);

						switch (Chess_Color)
						{
						    //case Note: {break; }

						    case White:
						    {
								ChessBishopt->StaticMesh->SetMaterial(0, Material_Yellow);
							    break;
						    }
						    case Black:
						    {
								ChessBishopt->StaticMesh->SetMaterial(0, Material_Brown);
							    break;
						    }
						}
					
					    break;
				    }
				    case Rock:
				    {
						FVector SpawnLocation = Point->GetActorLocation();
						SpawnLocation.Z = 200.f;

						FQuat SpawnRotation;
						SpawnRotation.X = 0.f;
						SpawnRotation.Y = 0.f;
						SpawnRotation.Z = 0.f;

						FTransform SpawnTransform;
						SpawnTransform.SetLocation(SpawnLocation);

						FActorSpawnParameters SpawnParameters;
						SpawnParameters.Owner = BaseChess;

						AbaseChess_Rock* ChessRock = GetWorld()->SpawnActor<AbaseChess_Rock>(AbaseChess_Rock::StaticClass(), SpawnTransform, SpawnParameters);
						ChessRock->SetActorLocation(SpawnLocation);

						switch (Chess_Color)
						{
						    //case Note: {break; }

						    case White:
						    {
								ChessRock->StaticMesh->SetMaterial(0, Material_Yellow);
							    break;
						    }
						    case Black:
						    {
								ChessRock->StaticMesh->SetMaterial(0, Material_Brown);
							    break;
						    }
						}
					
					    break;
				    }
				    case Queen:
				    {
						FVector SpawnLocation = Point->GetActorLocation();
						SpawnLocation.Z = 200.f;

						FQuat SpawnRotation;
						SpawnRotation.X = 0.f;
						SpawnRotation.Y = 0.f;
						SpawnRotation.Z = 0.f;

						FTransform SpawnTransform;
						SpawnTransform.SetLocation(SpawnLocation);

						FActorSpawnParameters SpawnParameters;
						SpawnParameters.Owner = BaseChess;

						AbaseChess_Queen* ChessQueen = GetWorld()->SpawnActor<AbaseChess_Queen>(AbaseChess_Queen::StaticClass(), SpawnTransform, SpawnParameters);
						ChessQueen->SetActorLocation(SpawnLocation);

						switch (Chess_Color)
						{
						    //case Note: {break; }

						    case White:
						    {
							    ChessQueen->StaticMesh->SetMaterial(0, Material_Yellow);
							    break;
						    }
						    case Black:
						    {
							    ChessQueen->StaticMesh->SetMaterial(0, Material_Brown);
							    break;
						    }
						}
					
					    break;
				    }
				    case King:
				    {
					
					    break;
				    }
				}
				
				break;
			}
		}
	} 


	Point->Chess_Name = ChessName;

}

//--------------------------------------------------------------------------------
void ATablePart::F_Chess_Chackmate()
{
	F_Chess_Chackmate1();
}

//Chech All Enemys Pos
void ATablePart::F_Chess_Chackmate1()
{

	//Get Game Mode
	AChessCPPGameModeBase* GM_Base;
	GM_Base = Cast<AChessCPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	//Local var
	ATablePart* LEnemy = nullptr;
	bool LHasWay = false;

	TArray<AActor*> TablePartAll;
	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			if(TablePart->Chess_Name == GM_Base->Last_Chess_Name && TablePart->Chess_Color == GM_Base->Last_Chess_Color)
		    {
				LEnemy = TablePart;

				break;
		    }
		}
	}

	Enumy_Chess_Pawn.Empty();
	Enumy_Chess_Knight.Empty();
	Enumy_Chess_Bishop.Empty();
	Enumy_Chess_Rock.Empty();
	Enumy_Chess_Queen.Empty();
	Enumy_Chess_King.Empty();
	Enumy_Chess_All.Empty();

	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			if (TablePart->Chess_Color != GM_Base->CheyHod)
			{
				switch (TablePart->Chess_Name)
				{
				    case Note: {break; }
					case Pawn:
					{
						Enumy_Chess_Pawn.Add(TablePart);
						break;
					}
					case Knight:
					{
						Enumy_Chess_Knight.Add(TablePart);
						break;
					}
					case Bishop:
					{
						Enumy_Chess_Bishop.Add(TablePart);
						break;
					}
					case Rock:
					{
						Enumy_Chess_Rock.Add(TablePart);
						break;
					}
					case Queen:
					{
						Enumy_Chess_Queen.Add(TablePart);
						break;
					}
					case King:
					{
						Enumy_Chess_King.Add(TablePart);
						break;
					}
				}	
			}
		}
	}

	switch (LEnemy->Chess_Name)
	{
	    case Note: {break; }
	    case Pawn:
	    {
			switch (GM_Base->CheyHod)
			{
			    case None: {break; }
			    case White:
			    {
					//1
					for (auto It1 = Enumy_Chess_Pawn.CreateIterator(); It1; It1++)
					{
						ATablePart* TablePart1 = Cast<ATablePart>(*It1);
						if (TablePart1)
						{
							TArray<AActor*> TablePartAll2;
							TablePartAll2.Empty();
							UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
							for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
							{
								ATablePart* TablePart2 = Cast<ATablePart>(*It2);
								if (TablePart2)
								{
									FVector2D NewLocation;
									NewLocation.X = TablePart1->Table_Pos_Current.X - 1.0f;
									NewLocation.Y = TablePart1->Table_Pos_Current.Y - 1.0f;

									if (TablePart2->Table_Pos_Current == NewLocation && TablePart2->Chess_Color != TablePart1->Chess_Color)
									{
										//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

										if (!Enumy_Chess_All.Contains(TablePart2))
										{
											Enumy_Chess_All.Add(TablePart2);
										}
									}
								}
							}
						}
					}

					for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
					{
						ATablePart* TablePart1 = Cast<ATablePart>(*It1);
						if (TablePart1)
						{
							if (TablePart1->Chess_Name == King)
							{
								LHasWay = true;
							}
						}
					}

					if (LHasWay)
					{
						F_Chess_Chackmate2(LEnemy);
					}

					else
					{
						Enumy_Chess_All.Empty();
						F_ClearAllTable();

						//2
						for (auto It1 = Enumy_Chess_Pawn.CreateIterator(); It1; It1++)
						{
							ATablePart* TablePart1 = Cast<ATablePart>(*It1);
							if (TablePart1)
							{
								TArray<AActor*> TablePartAll2;
								TablePartAll2.Empty();
								UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
								for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
								{
									ATablePart* TablePart2 = Cast<ATablePart>(*It2);
									if (TablePart2)
									{
										FVector2D NewLocation;
										NewLocation.X = TablePart1->Table_Pos_Current.X + 1.0f;
										NewLocation.Y = TablePart1->Table_Pos_Current.Y - 1.0f;

										if (TablePart2->Table_Pos_Current == NewLocation && TablePart2->Chess_Color != TablePart1->Chess_Color)
										{
											//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

											if (!Enumy_Chess_All.Contains(TablePart2))
											{
												Enumy_Chess_All.Add(TablePart2);
											}
										}
									}
								}
							}
						}

						for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
						{
							ATablePart* TablePart1 = Cast<ATablePart>(*It1);
							if (TablePart1)
							{
								if (TablePart1->Chess_Name == King)
								{
									LHasWay = true;
								}
							}
						}

						if (LHasWay)
						{
							F_Chess_Chackmate2(LEnemy);
						}

						else
						{
							Enumy_Chess_All.Empty();
							F_ClearAllTable();

						}

					}

				    
					break;
			    }
				case Black:
				{
					//1
					for (auto It1 = Enumy_Chess_Pawn.CreateIterator(); It1; It1++)
					{
						ATablePart* TablePart1 = Cast<ATablePart>(*It1);
						if (TablePart1)
						{
							TArray<AActor*> TablePartAll2;
							TablePartAll2.Empty();
							UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
							for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
							{
								ATablePart* TablePart2 = Cast<ATablePart>(*It2);
								if (TablePart2)
								{
									FVector2D NewLocation;
									NewLocation.X = TablePart1->Table_Pos_Current.X - 1.0f;
									NewLocation.Y = TablePart1->Table_Pos_Current.Y + 1.0f;

									if (TablePart2->Table_Pos_Current == NewLocation && TablePart2->Chess_Color != TablePart1->Chess_Color)
									{
										//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

										if (!Enumy_Chess_All.Contains(TablePart2))
										{
											Enumy_Chess_All.Add(TablePart2);
										}
									}
								}
							}
						}
					}

					for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
					{
						ATablePart* TablePart1 = Cast<ATablePart>(*It1);
						if (TablePart1)
						{
							if (TablePart1->Chess_Name == King)
							{
								LHasWay = true;
							}
						}
					}

					if (LHasWay)
					{
						F_Chess_Chackmate2(LEnemy);
					}

					else
					{
						Enumy_Chess_All.Empty();
						F_ClearAllTable();

						//2
						for (auto It1 = Enumy_Chess_Pawn.CreateIterator(); It1; It1++)
						{
							ATablePart* TablePart1 = Cast<ATablePart>(*It1);
							if (TablePart1)
							{
								TArray<AActor*> TablePartAll2;
								TablePartAll2.Empty();
								UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
								for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
								{
									ATablePart* TablePart2 = Cast<ATablePart>(*It2);
									if (TablePart2)
									{
										FVector2D NewLocation;
										NewLocation.X = TablePart1->Table_Pos_Current.X + 1.0f;
										NewLocation.Y = TablePart1->Table_Pos_Current.Y + 1.0f;

										if (TablePart2->Table_Pos_Current == NewLocation && TablePart2->Chess_Color != TablePart1->Chess_Color)
										{
											//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

											if (!Enumy_Chess_All.Contains(TablePart2))
											{
												Enumy_Chess_All.Add(TablePart2);
											}
										}
									}
								}
							}
						}

						for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
						{
							ATablePart* TablePart1 = Cast<ATablePart>(*It1);
							if (TablePart1)
							{
								if (TablePart1->Chess_Name == King)
								{
									LHasWay = true;
								}
							}
						}

						if (LHasWay)
						{
							F_Chess_Chackmate2(LEnemy);
						}

						else
						{
							Enumy_Chess_All.Empty();
							F_ClearAllTable();

						}

					}



					break;
				}
			}
		
		    break;
	    }

		//------------
	    case Knight:
	    {
			//1
			for (auto It1 = Enumy_Chess_Knight.CreateIterator(); It1; It1++)
			{
				ATablePart* TablePart1 = Cast<ATablePart>(*It1);
				if (TablePart1)
				{
					TArray<AActor*> TablePartAll2;
					TablePartAll2.Empty();
					UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
					for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
					{
						ATablePart* TablePart2 = Cast<ATablePart>(*It2);
						if (TablePart2)
						{
							FVector2D NewLocation;
							NewLocation.X = TablePart1->Table_Pos_Current.X - 1.0f;
							NewLocation.Y = TablePart1->Table_Pos_Current.Y + 2.0f;

							if (TablePart2->Table_Pos_Current == NewLocation && TablePart2->Chess_Color != TablePart1->Chess_Color)
							{
								//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

								if (!Enumy_Chess_All.Contains(TablePart2))
								{
									Enumy_Chess_All.Add(TablePart2);
								}
							}
						}
					}
				}
			}

			for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
			{
				ATablePart* TablePart1 = Cast<ATablePart>(*It1);
				if (TablePart1)
				{
					if (TablePart1->Chess_Name == King)
					{
						LHasWay = true;
					}
				}
			}

			if (LHasWay)
			{
				F_Chess_Chackmate2(LEnemy);
			}

			else
			{
				Enumy_Chess_All.Empty();
				F_ClearAllTable();

				//2
				for (auto It1 = Enumy_Chess_Knight.CreateIterator(); It1; It1++)
				{
					ATablePart* TablePart1 = Cast<ATablePart>(*It1);
					if (TablePart1)
					{
						TArray<AActor*> TablePartAll2;
						TablePartAll2.Empty();
						UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
						for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
						{
							ATablePart* TablePart2 = Cast<ATablePart>(*It2);
							if (TablePart2)
							{
								FVector2D NewLocation;
								NewLocation.X = TablePart1->Table_Pos_Current.X + 1.0f;
								NewLocation.Y = TablePart1->Table_Pos_Current.Y + 2.0f;

								if (TablePart2->Table_Pos_Current == NewLocation && TablePart2->Chess_Color != TablePart1->Chess_Color)
								{
									//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

									if (!Enumy_Chess_All.Contains(TablePart2))
									{
										Enumy_Chess_All.Add(TablePart2);
									}
								}
							}
						}
					}
				}

				for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
				{
					ATablePart* TablePart1 = Cast<ATablePart>(*It1);
					if (TablePart1)
					{
						if (TablePart1->Chess_Name == King)
						{
							LHasWay = true;
						}
					}
				}

				if (LHasWay)
				{
					F_Chess_Chackmate2(LEnemy);
				}

				else
				{
					Enumy_Chess_All.Empty();
					F_ClearAllTable();

					//3
					for (auto It1 = Enumy_Chess_Knight.CreateIterator(); It1; It1++)
					{
						ATablePart* TablePart1 = Cast<ATablePart>(*It1);
						if (TablePart1)
						{
							TArray<AActor*> TablePartAll2;
							TablePartAll2.Empty();
							UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
							for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
							{
								ATablePart* TablePart2 = Cast<ATablePart>(*It2);
								if (TablePart2)
								{
									FVector2D NewLocation;
									NewLocation.X = TablePart1->Table_Pos_Current.X + 2.0f;
									NewLocation.Y = TablePart1->Table_Pos_Current.Y + 1.0f;

									if (TablePart2->Table_Pos_Current == NewLocation && TablePart2->Chess_Color != TablePart1->Chess_Color)
									{
										//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

										if (!Enumy_Chess_All.Contains(TablePart2))
										{
											Enumy_Chess_All.Add(TablePart2);
										}
									}
								}
							}
						}
					}

					for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
					{
						ATablePart* TablePart1 = Cast<ATablePart>(*It1);
						if (TablePart1)
						{
							if (TablePart1->Chess_Name == King)
							{
								LHasWay = true;
							}
						}
					}

					if (LHasWay)
					{
						F_Chess_Chackmate2(LEnemy);
					}

					else
					{
						Enumy_Chess_All.Empty();
						F_ClearAllTable();

						//4
						for (auto It1 = Enumy_Chess_Knight.CreateIterator(); It1; It1++)
						{
							ATablePart* TablePart1 = Cast<ATablePart>(*It1);
							if (TablePart1)
							{
								TArray<AActor*> TablePartAll2;
								TablePartAll2.Empty();
								UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
								for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
								{
									ATablePart* TablePart2 = Cast<ATablePart>(*It2);
									if (TablePart2)
									{
										FVector2D NewLocation;
										NewLocation.X = TablePart1->Table_Pos_Current.X + 2.0f;
										NewLocation.Y = TablePart1->Table_Pos_Current.Y - 1.0f;

										if (TablePart2->Table_Pos_Current == NewLocation && TablePart2->Chess_Color != TablePart1->Chess_Color)
										{
											//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

											if (!Enumy_Chess_All.Contains(TablePart2))
											{
												Enumy_Chess_All.Add(TablePart2);
											}
										}
									}
								}
							}
						}

						for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
						{
							ATablePart* TablePart1 = Cast<ATablePart>(*It1);
							if (TablePart1)
							{
								if (TablePart1->Chess_Name == King)
								{
									LHasWay = true;
								}
							}
						}

						if (LHasWay)
						{
							F_Chess_Chackmate2(LEnemy);
						}

						else
						{
							Enumy_Chess_All.Empty();
							F_ClearAllTable();

							//5
							for (auto It1 = Enumy_Chess_Knight.CreateIterator(); It1; It1++)
							{
								ATablePart* TablePart1 = Cast<ATablePart>(*It1);
								if (TablePart1)
								{
									TArray<AActor*> TablePartAll2;
									TablePartAll2.Empty();
									UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
									for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
									{
										ATablePart* TablePart2 = Cast<ATablePart>(*It2);
										if (TablePart2)
										{
											FVector2D NewLocation;
											NewLocation.X = TablePart1->Table_Pos_Current.X + 1.0f;
											NewLocation.Y = TablePart1->Table_Pos_Current.Y - 2.0f;

											if (TablePart2->Table_Pos_Current == NewLocation && TablePart2->Chess_Color != TablePart1->Chess_Color)
											{
												//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

												if (!Enumy_Chess_All.Contains(TablePart2))
												{
													Enumy_Chess_All.Add(TablePart2);
												}
											}
										}
									}
								}
							}

							for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
							{
								ATablePart* TablePart1 = Cast<ATablePart>(*It1);
								if (TablePart1)
								{
									if (TablePart1->Chess_Name == King)
									{
										LHasWay = true;
									}
								}
							}

							if (LHasWay)
							{
								F_Chess_Chackmate2(LEnemy);
							}

							else
							{
								Enumy_Chess_All.Empty();
								F_ClearAllTable();

								//6
								for (auto It1 = Enumy_Chess_Knight.CreateIterator(); It1; It1++)
								{
									ATablePart* TablePart1 = Cast<ATablePart>(*It1);
									if (TablePart1)
									{
										TArray<AActor*> TablePartAll2;
										TablePartAll2.Empty();
										UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
										for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
										{
											ATablePart* TablePart2 = Cast<ATablePart>(*It2);
											if (TablePart2)
											{
												FVector2D NewLocation;
												NewLocation.X = TablePart1->Table_Pos_Current.X - 1.0f;
												NewLocation.Y = TablePart1->Table_Pos_Current.Y - 2.0f;

												if (TablePart2->Table_Pos_Current == NewLocation && TablePart2->Chess_Color != TablePart1->Chess_Color)
												{
													//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

													if (!Enumy_Chess_All.Contains(TablePart2))
													{
														Enumy_Chess_All.Add(TablePart2);
													}
												}
											}
										}
									}
								}

								for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
								{
									ATablePart* TablePart1 = Cast<ATablePart>(*It1);
									if (TablePart1)
									{
										if (TablePart1->Chess_Name == King)
										{
											LHasWay = true;
										}
									}
								}

								if (LHasWay)
								{
									F_Chess_Chackmate2(LEnemy);
								}

								else
								{
									Enumy_Chess_All.Empty();
									F_ClearAllTable();

									//7
									for (auto It1 = Enumy_Chess_Knight.CreateIterator(); It1; It1++)
									{
										ATablePart* TablePart1 = Cast<ATablePart>(*It1);
										if (TablePart1)
										{
											TArray<AActor*> TablePartAll2;
											TablePartAll2.Empty();
											UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
											for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
											{
												ATablePart* TablePart2 = Cast<ATablePart>(*It2);
												if (TablePart2)
												{
													FVector2D NewLocation;
													NewLocation.X = TablePart1->Table_Pos_Current.X - 2.0f;
													NewLocation.Y = TablePart1->Table_Pos_Current.Y + 1.0f;

													if (TablePart2->Table_Pos_Current == NewLocation && TablePart2->Chess_Color != TablePart1->Chess_Color)
													{
														//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

														if (!Enumy_Chess_All.Contains(TablePart2))
														{
															Enumy_Chess_All.Add(TablePart2);
														}
													}
												}
											}
										}
									}

									for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
									{
										ATablePart* TablePart1 = Cast<ATablePart>(*It1);
										if (TablePart1)
										{
											if (TablePart1->Chess_Name == King)
											{
												LHasWay = true;
											}
										}
									}

									if (LHasWay)
									{
										F_Chess_Chackmate2(LEnemy);
									}

									else
									{
										Enumy_Chess_All.Empty();
										F_ClearAllTable();

										//8
										for (auto It1 = Enumy_Chess_Knight.CreateIterator(); It1; It1++)
										{
											ATablePart* TablePart1 = Cast<ATablePart>(*It1);
											if (TablePart1)
											{
												TArray<AActor*> TablePartAll2;
												TablePartAll2.Empty();
												UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
												for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
												{
													ATablePart* TablePart2 = Cast<ATablePart>(*It2);
													if (TablePart2)
													{
														FVector2D NewLocation;
														NewLocation.X = TablePart1->Table_Pos_Current.X - 2.0f;
														NewLocation.Y = TablePart1->Table_Pos_Current.Y - 1.0f;

														if (TablePart2->Table_Pos_Current == NewLocation && TablePart2->Chess_Color != TablePart1->Chess_Color)
														{
															//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

															if (!Enumy_Chess_All.Contains(TablePart2))
															{
																Enumy_Chess_All.Add(TablePart2);
															}
														}
													}
												}
											}
										}

										for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
										{
											ATablePart* TablePart1 = Cast<ATablePart>(*It1);
											if (TablePart1)
											{
												if (TablePart1->Chess_Name == King)
												{
													LHasWay = true;
												}
											}
										}

										if (LHasWay)
										{
											F_Chess_Chackmate2(LEnemy);
										}

										else
										{
											Enumy_Chess_All.Empty();
											F_ClearAllTable();

										}
									}
								}
							}
						}
					}
				}
			}

		
		    break;
	    }

		//------------
	    case Bishop:
	    {
			//1
			for (auto It1 = Enumy_Chess_Bishop.CreateIterator(); It1; It1++)
			{
				ATablePart* TablePart1 = Cast<ATablePart>(*It1);
				if (TablePart1)
				{
					FVector2D NewLocation;
					NewLocation.X = TablePart1->Table_Pos_Current.X + 1.0f;
					NewLocation.Y = TablePart1->Table_Pos_Current.Y + 1.0f;

					for (int32 It2 = 0; It2 <= 7; It2++)
					{
						TArray<AActor*> TablePartAll3;
						TablePartAll3.Empty();
						UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll3);
						for (auto It3 = TablePartAll3.CreateIterator(); It3; It3++)
						{
							ATablePart* TablePart3 = Cast<ATablePart>(*It3);
							if (TablePart3)
							{
								if (TablePart3->Table_Pos_Current == NewLocation)
								{
									if (TablePart3->Chess_Name == Note || (TablePart3->Chess_Name == King && TablePart3->Chess_Color != TablePart1->Chess_Color))
									{
										//TablePart3->StaticMesh->SetMaterial(0, Material_Blue);

										NewLocation.X = NewLocation.X + 1.0f;
										NewLocation.Y = NewLocation.Y + 1.0f;

										if (!Enumy_Chess_All.Contains(TablePart3))
										{
											Enumy_Chess_All.Add(TablePart3);
										}

									}
									else {/* break; */ }
								}
							}
						}
						//break;
					}
					//break;
				}
			}

			for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
			{
				ATablePart* TablePart1 = Cast<ATablePart>(*It1);
				if (TablePart1)
				{
					if (TablePart1->Chess_Name == King)
					{
						LHasWay = true;
					}
				}
			}

			if (LHasWay)
			{
				F_Chess_Chackmate2(LEnemy);
			}

			else
			{
				Enumy_Chess_All.Empty();
				F_ClearAllTable();

				//2
				for (auto It1 = Enumy_Chess_Bishop.CreateIterator(); It1; It1++)
				{
					ATablePart* TablePart1 = Cast<ATablePart>(*It1);
					if (TablePart1)
					{
						FVector2D NewLocation;
						NewLocation.X = TablePart1->Table_Pos_Current.X - 1.0f;
						NewLocation.Y = TablePart1->Table_Pos_Current.Y + 1.0f;

						for (int32 It2 = 0; It2 <= 7; It2++)
						{
							TArray<AActor*> TablePartAll3;
							TablePartAll3.Empty();
							UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll3);
							for (auto It3 = TablePartAll3.CreateIterator(); It3; It3++)
							{
								ATablePart* TablePart3 = Cast<ATablePart>(*It3);
								if (TablePart3)
								{
									if (TablePart3->Table_Pos_Current == NewLocation)
									{
										if (TablePart3->Chess_Name == Note || (TablePart3->Chess_Name == King && TablePart3->Chess_Color != TablePart1->Chess_Color))
										{
											//TablePart3->StaticMesh->SetMaterial(0, Material_Blue);

											NewLocation.X = NewLocation.X - 1.0f;
											NewLocation.Y = NewLocation.Y + 1.0f;

											if (!Enumy_Chess_All.Contains(TablePart3))
											{
												Enumy_Chess_All.Add(TablePart3);
											}

										}
										else {/* break; */ }
									}
								}
							}
							//break;
						}
						//break;
					}
				}

				for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
				{
					ATablePart* TablePart1 = Cast<ATablePart>(*It1);
					if (TablePart1)
					{
						if (TablePart1->Chess_Name == King)
						{
							LHasWay = true;
						}
					}
				}

				if (LHasWay)
				{
					F_Chess_Chackmate2(LEnemy);
				}

				else
				{
					Enumy_Chess_All.Empty();
					F_ClearAllTable();

					//3
					for (auto It1 = Enumy_Chess_Bishop.CreateIterator(); It1; It1++)
					{
						ATablePart* TablePart1 = Cast<ATablePart>(*It1);
						if (TablePart1)
						{
							FVector2D NewLocation;
							NewLocation.X = TablePart1->Table_Pos_Current.X + 1.0f;
							NewLocation.Y = TablePart1->Table_Pos_Current.Y - 1.0f;

							for (int32 It2 = 0; It2 <= 7; It2++)
							{
								TArray<AActor*> TablePartAll3;
								TablePartAll3.Empty();
								UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll3);
								for (auto It3 = TablePartAll3.CreateIterator(); It3; It3++)
								{
									ATablePart* TablePart3 = Cast<ATablePart>(*It3);
									if (TablePart3)
									{
										if (TablePart3->Table_Pos_Current == NewLocation)
										{
											if (TablePart3->Chess_Name == Note || (TablePart3->Chess_Name == King && TablePart3->Chess_Color != TablePart1->Chess_Color))
											{
												//TablePart3->StaticMesh->SetMaterial(0, Material_Blue);

												NewLocation.X = NewLocation.X + 1.0f;
												NewLocation.Y = NewLocation.Y - 1.0f;

												if (!Enumy_Chess_All.Contains(TablePart3))
												{
													Enumy_Chess_All.Add(TablePart3);
												}

											}
											else {/* break; */ }
										}
									}
								}
								//break;
							}
							//break;
						}
					}

					for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
					{
						ATablePart* TablePart1 = Cast<ATablePart>(*It1);
						if (TablePart1)
						{
							if (TablePart1->Chess_Name == King)
							{
								LHasWay = true;
							}
						}
					}

					if (LHasWay)
					{
						F_Chess_Chackmate2(LEnemy);
					}

					else
					{
						Enumy_Chess_All.Empty();
						F_ClearAllTable();

						//4
						for (auto It1 = Enumy_Chess_Bishop.CreateIterator(); It1; It1++)
						{
							ATablePart* TablePart1 = Cast<ATablePart>(*It1);
							if (TablePart1)
							{
								FVector2D NewLocation;
								NewLocation.X = TablePart1->Table_Pos_Current.X - 1.0f;
								NewLocation.Y = TablePart1->Table_Pos_Current.Y - 1.0f;

								for (int32 It2 = 0; It2 <= 7; It2++)
								{
									TArray<AActor*> TablePartAll3;
									TablePartAll3.Empty();
									UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll3);
									for (auto It3 = TablePartAll3.CreateIterator(); It3; It3++)
									{
										ATablePart* TablePart3 = Cast<ATablePart>(*It3);
										if (TablePart3)
										{
											if (TablePart3->Table_Pos_Current == NewLocation)
											{
												if (TablePart3->Chess_Name == Note || (TablePart3->Chess_Name == King && TablePart3->Chess_Color != TablePart1->Chess_Color))
												{
													//TablePart3->StaticMesh->SetMaterial(0, Material_Blue);

													NewLocation.X = NewLocation.X - 1.0f;
													NewLocation.Y = NewLocation.Y - 1.0f;

													if (!Enumy_Chess_All.Contains(TablePart3))
													{
														Enumy_Chess_All.Add(TablePart3);
													}

												}
												else {/* break; */ }
											}
										}
									}
									//break;
								}
								//break;
							}
						}

						for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
						{
							ATablePart* TablePart1 = Cast<ATablePart>(*It1);
							if (TablePart1)
							{
								if (TablePart1->Chess_Name == King)
								{
									LHasWay = true;
								}
							}
						}

						if (LHasWay)
						{
							F_Chess_Chackmate2(LEnemy);
						}

						else
						{
							Enumy_Chess_All.Empty();
							F_ClearAllTable();
						}
					}
				}
			}

		
		    break;
	    }

		//------------
	    case Rock:
	    {
			//1
			for (auto It1 = Enumy_Chess_Rock.CreateIterator(); It1; It1++)
			{
				ATablePart* TablePart1 = Cast<ATablePart>(*It1);
				if (TablePart1)
				{
					FVector2D NewLocation;
					NewLocation.X = TablePart1->Table_Pos_Current.X + 1.0f;
					NewLocation.Y = TablePart1->Table_Pos_Current.Y;

					for (int32 It2 = 0; It2 <= 7; It2++)
					{
						TArray<AActor*> TablePartAll3;
						TablePartAll3.Empty();
						UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll3);
						for (auto It3 = TablePartAll3.CreateIterator(); It3; It3++)
						{
							ATablePart* TablePart3 = Cast<ATablePart>(*It3);
							if (TablePart3)
							{
								if (TablePart3->Table_Pos_Current == NewLocation)
								{
									if (TablePart3->Chess_Name == Note || (TablePart3->Chess_Name == King && TablePart3->Chess_Color != TablePart1->Chess_Color))
									{
										//TablePart3->StaticMesh->SetMaterial(0, Material_Blue);

										NewLocation.X = NewLocation.X + 1.0f;
										NewLocation.Y = NewLocation.Y;

										if (!Enumy_Chess_All.Contains(TablePart3))
										{
											Enumy_Chess_All.Add(TablePart3);
										}

									}
									else {/* break; */ }
								}
							}
						}
						//break;
					}
					//break;
				}
			}

			for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
			{
				ATablePart* TablePart1 = Cast<ATablePart>(*It1);
				if (TablePart1)
				{
					if (TablePart1->Chess_Name == King)
					{
						LHasWay = true;
					}
				}
			}

			if (LHasWay)
			{
				F_Chess_Chackmate2(LEnemy);
			}

			else
			{
				Enumy_Chess_All.Empty();
				F_ClearAllTable();

				//2
				for (auto It1 = Enumy_Chess_Rock.CreateIterator(); It1; It1++)
				{
					ATablePart* TablePart1 = Cast<ATablePart>(*It1);
					if (TablePart1)
					{
						FVector2D NewLocation;
						NewLocation.X = TablePart1->Table_Pos_Current.X - 1.0f;
						NewLocation.Y = TablePart1->Table_Pos_Current.Y;

						for (int32 It2 = 0; It2 <= 7; It2++)
						{
							TArray<AActor*> TablePartAll3;
							TablePartAll3.Empty();
							UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll3);
							for (auto It3 = TablePartAll3.CreateIterator(); It3; It3++)
							{
								ATablePart* TablePart3 = Cast<ATablePart>(*It3);
								if (TablePart3)
								{
									if (TablePart3->Table_Pos_Current == NewLocation)
									{
										if (TablePart3->Chess_Name == Note || (TablePart3->Chess_Name == King && TablePart3->Chess_Color != TablePart1->Chess_Color))
										{
											//TablePart3->StaticMesh->SetMaterial(0, Material_Blue);

											NewLocation.X = NewLocation.X - 1.0f;
											NewLocation.Y = NewLocation.Y;

											if (!Enumy_Chess_All.Contains(TablePart3))
											{
												Enumy_Chess_All.Add(TablePart3);
											}

										}
										else {/* break; */ }
									}
								}
							}
							//break;
						}
						//break;
					}
				}

				for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
				{
					ATablePart* TablePart1 = Cast<ATablePart>(*It1);
					if (TablePart1)
					{
						if (TablePart1->Chess_Name == King)
						{
							LHasWay = true;
						}
					}
				}

				if (LHasWay)
				{
					F_Chess_Chackmate2(LEnemy);
				}

				else
				{
					Enumy_Chess_All.Empty();
					F_ClearAllTable();

					//3
					for (auto It1 = Enumy_Chess_Rock.CreateIterator(); It1; It1++)
					{
						ATablePart* TablePart1 = Cast<ATablePart>(*It1);
						if (TablePart1)
						{
							FVector2D NewLocation;
							NewLocation.X = TablePart1->Table_Pos_Current.X;
							NewLocation.Y = TablePart1->Table_Pos_Current.Y + 1.0f;

							for (int32 It2 = 0; It2 <= 7; It2++)
							{
								TArray<AActor*> TablePartAll3;
								TablePartAll3.Empty();
								UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll3);
								for (auto It3 = TablePartAll3.CreateIterator(); It3; It3++)
								{
									ATablePart* TablePart3 = Cast<ATablePart>(*It3);
									if (TablePart3)
									{
										if (TablePart3->Table_Pos_Current == NewLocation)
										{
											if (TablePart3->Chess_Name == Note || (TablePart3->Chess_Name == King && TablePart3->Chess_Color != TablePart1->Chess_Color))
											{
												//TablePart3->StaticMesh->SetMaterial(0, Material_Blue);

												NewLocation.X = NewLocation.X;
												NewLocation.Y = NewLocation.Y + 1.0f;

												if (!Enumy_Chess_All.Contains(TablePart3))
												{
													Enumy_Chess_All.Add(TablePart3);
												}

											}
											else {/* break; */ }
										}
									}
								}
								//break;
							}
							//break;
						}
					}

					for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
					{
						ATablePart* TablePart1 = Cast<ATablePart>(*It1);
						if (TablePart1)
						{
							if (TablePart1->Chess_Name == King)
							{
								LHasWay = true;
							}
						}
					}

					if (LHasWay)
					{
						F_Chess_Chackmate2(LEnemy);
					}

					else
					{
						Enumy_Chess_All.Empty();
						F_ClearAllTable();

						//4
						for (auto It1 = Enumy_Chess_Rock.CreateIterator(); It1; It1++)
						{
							ATablePart* TablePart1 = Cast<ATablePart>(*It1);
							if (TablePart1)
							{
								FVector2D NewLocation;
								NewLocation.X = TablePart1->Table_Pos_Current.X;
								NewLocation.Y = TablePart1->Table_Pos_Current.Y - 1.0f;

								for (int32 It2 = 0; It2 <= 7; It2++)
								{
									TArray<AActor*> TablePartAll3;
									TablePartAll3.Empty();
									UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll3);
									for (auto It3 = TablePartAll3.CreateIterator(); It3; It3++)
									{
										ATablePart* TablePart3 = Cast<ATablePart>(*It3);
										if (TablePart3)
										{
											if (TablePart3->Table_Pos_Current == NewLocation)
											{
												if (TablePart3->Chess_Name == Note || (TablePart3->Chess_Name == King && TablePart3->Chess_Color != TablePart1->Chess_Color))
												{
													//TablePart3->StaticMesh->SetMaterial(0, Material_Blue);

													NewLocation.X = NewLocation.X;
													NewLocation.Y = NewLocation.Y - 1.0f;

													if (!Enumy_Chess_All.Contains(TablePart3))
													{
														Enumy_Chess_All.Add(TablePart3);
													}

												}
												else {/* break; */ }
											}
										}
									}
									//break;
								}
								//break;
							}
						}

						for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
						{
							ATablePart* TablePart1 = Cast<ATablePart>(*It1);
							if (TablePart1)
							{
								if (TablePart1->Chess_Name == King)
								{
									LHasWay = true;
								}
							}
						}

						if (LHasWay)
						{
							F_Chess_Chackmate2(LEnemy);
						}

						else
						{
							Enumy_Chess_All.Empty();
							F_ClearAllTable();
						}
					}
				}
			}
		
		    break;
	    }

		//------------
	    case Queen:
	    {
			//1
			for (auto It1 = Enumy_Chess_Queen.CreateIterator(); It1; It1++)
			{
				ATablePart* TablePart1 = Cast<ATablePart>(*It1);
				if (TablePart1)
				{
					FVector2D NewLocation;
					NewLocation.X = TablePart1->Table_Pos_Current.X + 1.0f;
					NewLocation.Y = TablePart1->Table_Pos_Current.Y + 1.0f;

					for (int32 It2 = 0; It2 <= 7; It2++)
					{
						TArray<AActor*> TablePartAll3;
						TablePartAll3.Empty();
						UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll3);
						for (auto It3 = TablePartAll3.CreateIterator(); It3; It3++)
						{
							ATablePart* TablePart3 = Cast<ATablePart>(*It3);
							if (TablePart3)
							{
								if (TablePart3->Table_Pos_Current == NewLocation)
								{
									if (TablePart3->Chess_Name == Note || (TablePart3->Chess_Name == King && TablePart3->Chess_Color != TablePart1->Chess_Color))
									{
										//TablePart3->StaticMesh->SetMaterial(0, Material_Blue);
									
										NewLocation.X = NewLocation.X + 1.0f;
										NewLocation.Y = NewLocation.Y + 1.0f;

										if (!Enumy_Chess_All.Contains(TablePart3))
										{
											Enumy_Chess_All.Add(TablePart3);
										}
									
									}
									else {/* break; */}
								}
							}
						}
						//break;
					}
					//break;
				}
			}

			for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
			{
				ATablePart* TablePart1 = Cast<ATablePart>(*It1);
				if (TablePart1)
				{
					if (TablePart1->Chess_Name == King)
					{
						LHasWay = true;
					}
				}
			}

			if (LHasWay)
			{
				F_Chess_Chackmate2(LEnemy);
			}

			else
			{
				Enumy_Chess_All.Empty();
				F_ClearAllTable();

				//2
				for (auto It1 = Enumy_Chess_Queen.CreateIterator(); It1; It1++)
				{
					ATablePart* TablePart1 = Cast<ATablePart>(*It1);
					if (TablePart1)
					{
						FVector2D NewLocation;
						NewLocation.X = TablePart1->Table_Pos_Current.X + 1.0f;
						NewLocation.Y = TablePart1->Table_Pos_Current.Y - 1.0f;

						for (int32 It2 = 0; It2 <= 7; It2++)
						{
							TArray<AActor*> TablePartAll3;
							TablePartAll3.Empty();
							UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll3);
							for (auto It3 = TablePartAll3.CreateIterator(); It3; It3++)
							{
								ATablePart* TablePart3 = Cast<ATablePart>(*It3);
								if (TablePart3)
								{
									if (TablePart3->Table_Pos_Current == NewLocation)
									{
										if (TablePart3->Chess_Name == Note || (TablePart3->Chess_Name == King && TablePart3->Chess_Color != TablePart1->Chess_Color))
										{
											//TablePart3->StaticMesh->SetMaterial(0, Material_Blue);

											NewLocation.X = NewLocation.X + 1.0f;
											NewLocation.Y = NewLocation.Y - 1.0f;

											if (!Enumy_Chess_All.Contains(TablePart3))
											{
												Enumy_Chess_All.Add(TablePart3);
											}

										}
										else {/* break; */ }
									}
								}
							}
							//break;
						}
						//break;
					}
				}

				for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
				{
					ATablePart* TablePart1 = Cast<ATablePart>(*It1);
					if (TablePart1)
					{
						if (TablePart1->Chess_Name == King)
						{
							LHasWay = true;
						}
					}
				}

				if (LHasWay)
				{
					F_Chess_Chackmate2(LEnemy);
				}

				else
				{
					Enumy_Chess_All.Empty();
					F_ClearAllTable();

					//3
					for (auto It1 = Enumy_Chess_Queen.CreateIterator(); It1; It1++)
					{
						ATablePart* TablePart1 = Cast<ATablePart>(*It1);
						if (TablePart1)
						{
							FVector2D NewLocation;
							NewLocation.X = TablePart1->Table_Pos_Current.X - 1.0f;
							NewLocation.Y = TablePart1->Table_Pos_Current.Y + 1.0f;

							for (int32 It2 = 0; It2 <= 7; It2++)
							{
								TArray<AActor*> TablePartAll3;
								TablePartAll3.Empty();
								UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll3);
								for (auto It3 = TablePartAll3.CreateIterator(); It3; It3++)
								{
									ATablePart* TablePart3 = Cast<ATablePart>(*It3);
									if (TablePart3)
									{
										if (TablePart3->Table_Pos_Current == NewLocation)
										{
											if (TablePart3->Chess_Name == Note || (TablePart3->Chess_Name == King && TablePart3->Chess_Color != TablePart1->Chess_Color))
											{
												//TablePart3->StaticMesh->SetMaterial(0, Material_Blue);

												NewLocation.X = NewLocation.X - 1.0f;
												NewLocation.Y = NewLocation.Y + 1.0f;

												if (!Enumy_Chess_All.Contains(TablePart3))
												{
													Enumy_Chess_All.Add(TablePart3);
												}

											}
											else {/* break; */ }
										}
									}
								}
								//break;
							}
							//break;
						}
					}

					for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
					{
						ATablePart* TablePart1 = Cast<ATablePart>(*It1);
						if (TablePart1)
						{
							if (TablePart1->Chess_Name == King)
							{
								LHasWay = true;
							}
						}
					}

					if (LHasWay)
					{
						F_Chess_Chackmate2(LEnemy);
					}

					else
					{
						Enumy_Chess_All.Empty();
						F_ClearAllTable();

						//4
						for (auto It1 = Enumy_Chess_Queen.CreateIterator(); It1; It1++)
						{
							ATablePart* TablePart1 = Cast<ATablePart>(*It1);
							if (TablePart1)
							{
								FVector2D NewLocation;
								NewLocation.X = TablePart1->Table_Pos_Current.X - 1.0f;
								NewLocation.Y = TablePart1->Table_Pos_Current.Y - 1.0f;

								for (int32 It2 = 0; It2 <= 7; It2++)
								{
									TArray<AActor*> TablePartAll3;
									TablePartAll3.Empty();
									UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll3);
									for (auto It3 = TablePartAll3.CreateIterator(); It3; It3++)
									{
										ATablePart* TablePart3 = Cast<ATablePart>(*It3);
										if (TablePart3)
										{
											if (TablePart3->Table_Pos_Current == NewLocation)
											{
												if (TablePart3->Chess_Name == Note || (TablePart3->Chess_Name == King && TablePart3->Chess_Color != TablePart1->Chess_Color))
												{
													//TablePart3->StaticMesh->SetMaterial(0, Material_Blue);

													NewLocation.X = NewLocation.X - 1.0f;
													NewLocation.Y = NewLocation.Y - 1.0f;

													if (!Enumy_Chess_All.Contains(TablePart3))
													{
														Enumy_Chess_All.Add(TablePart3);
													}

												}
												else {/* break; */ }
											}
										}
									}
									//break;
								}
								//break;
							}
						}

						for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
						{
							ATablePart* TablePart1 = Cast<ATablePart>(*It1);
							if (TablePart1)
							{
								if (TablePart1->Chess_Name == King)
								{
									LHasWay = true;
								}
							}
						}

						if (LHasWay)
						{
							F_Chess_Chackmate2(LEnemy);
						}

						else
						{
							Enumy_Chess_All.Empty();
							F_ClearAllTable();

							//5
							for (auto It1 = Enumy_Chess_Queen.CreateIterator(); It1; It1++)
							{
								ATablePart* TablePart1 = Cast<ATablePart>(*It1);
								if (TablePart1)
								{
									FVector2D NewLocation;
									NewLocation.X = TablePart1->Table_Pos_Current.X + 1.0f;
									NewLocation.Y = TablePart1->Table_Pos_Current.Y;

									for (int32 It2 = 0; It2 <= 7; It2++)
									{
										TArray<AActor*> TablePartAll3;
										TablePartAll3.Empty();
										UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll3);
										for (auto It3 = TablePartAll3.CreateIterator(); It3; It3++)
										{
											ATablePart* TablePart3 = Cast<ATablePart>(*It3);
											if (TablePart3)
											{
												if (TablePart3->Table_Pos_Current == NewLocation)
												{
													if (TablePart3->Chess_Name == Note || (TablePart3->Chess_Name == King && TablePart3->Chess_Color != TablePart1->Chess_Color))
													{
														//TablePart3->StaticMesh->SetMaterial(0, Material_Blue);

														NewLocation.X = NewLocation.X + 1.0f;
														NewLocation.Y = NewLocation.Y;

														if (!Enumy_Chess_All.Contains(TablePart3))
														{
															Enumy_Chess_All.Add(TablePart3);
														}

													}
													else {/* break; */ }
												}
											}
										}
										//break;
									}
									//break;
								}
							}

							for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
							{
								ATablePart* TablePart1 = Cast<ATablePart>(*It1);
								if (TablePart1)
								{
									if (TablePart1->Chess_Name == King)
									{
										LHasWay = true;
									}
								}
							}

							if (LHasWay)
							{
								F_Chess_Chackmate2(LEnemy);
							}

							else
							{
								Enumy_Chess_All.Empty();
								F_ClearAllTable();

								//6
								for (auto It1 = Enumy_Chess_Queen.CreateIterator(); It1; It1++)
								{
									ATablePart* TablePart1 = Cast<ATablePart>(*It1);
									if (TablePart1)
									{
										FVector2D NewLocation;
										NewLocation.X = TablePart1->Table_Pos_Current.X - 1.0f;
										NewLocation.Y = TablePart1->Table_Pos_Current.Y;

										for (int32 It2 = 0; It2 <= 7; It2++)
										{
											TArray<AActor*> TablePartAll3;
											TablePartAll3.Empty();
											UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll3);
											for (auto It3 = TablePartAll3.CreateIterator(); It3; It3++)
											{
												ATablePart* TablePart3 = Cast<ATablePart>(*It3);
												if (TablePart3)
												{
													if (TablePart3->Table_Pos_Current == NewLocation)
													{
														if (TablePart3->Chess_Name == Note || (TablePart3->Chess_Name == King && TablePart3->Chess_Color != TablePart1->Chess_Color))
														{
															//TablePart3->StaticMesh->SetMaterial(0, Material_Blue);

															NewLocation.X = NewLocation.X - 1.0f;
															NewLocation.Y = NewLocation.Y;

															if (!Enumy_Chess_All.Contains(TablePart3))
															{
																Enumy_Chess_All.Add(TablePart3);
															}

														}
														else {/* break; */ }
													}
												}
											}
											//break;
										}
										//break;
									}
								}

								for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
								{
									ATablePart* TablePart1 = Cast<ATablePart>(*It1);
									if (TablePart1)
									{
										if (TablePart1->Chess_Name == King)
										{
											LHasWay = true;
										}
									}
								}

								if (LHasWay)
								{
									F_Chess_Chackmate2(LEnemy);
								}

								else
								{
									Enumy_Chess_All.Empty();
									F_ClearAllTable();

									//7
									for (auto It1 = Enumy_Chess_Queen.CreateIterator(); It1; It1++)
									{
										ATablePart* TablePart1 = Cast<ATablePart>(*It1);
										if (TablePart1)
										{
											FVector2D NewLocation;
											NewLocation.X = TablePart1->Table_Pos_Current.X;
											NewLocation.Y = TablePart1->Table_Pos_Current.Y + 1.0f;

											for (int32 It2 = 0; It2 <= 7; It2++)
											{
												TArray<AActor*> TablePartAll3;
												TablePartAll3.Empty();
												UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll3);
												for (auto It3 = TablePartAll3.CreateIterator(); It3; It3++)
												{
													ATablePart* TablePart3 = Cast<ATablePart>(*It3);
													if (TablePart3)
													{
														if (TablePart3->Table_Pos_Current == NewLocation)
														{
															if (TablePart3->Chess_Name == Note || (TablePart3->Chess_Name == King && TablePart3->Chess_Color != TablePart1->Chess_Color))
															{
																//TablePart3->StaticMesh->SetMaterial(0, Material_Blue);

																NewLocation.X = NewLocation.X;
																NewLocation.Y = NewLocation.Y + 1.0f;

																if (!Enumy_Chess_All.Contains(TablePart3))
																{
																	Enumy_Chess_All.Add(TablePart3);
																}

															}
															else {/* break; */ }
														}
													}
												}
												//break;
											}
											//break;
										}
									}

									for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
									{
										ATablePart* TablePart1 = Cast<ATablePart>(*It1);
										if (TablePart1)
										{
											if (TablePart1->Chess_Name == King)
											{
												LHasWay = true;
											}
										}
									}

									if (LHasWay)
									{
										F_Chess_Chackmate2(LEnemy);
									}

									else
									{
										Enumy_Chess_All.Empty();
										F_ClearAllTable();

										//8
										for (auto It1 = Enumy_Chess_Queen.CreateIterator(); It1; It1++)
										{
											ATablePart* TablePart1 = Cast<ATablePart>(*It1);
											if (TablePart1)
											{
												FVector2D NewLocation;
												NewLocation.X = TablePart1->Table_Pos_Current.X;
												NewLocation.Y = TablePart1->Table_Pos_Current.Y - 1.0f;

												for (int32 It2 = 0; It2 <= 7; It2++)
												{
													TArray<AActor*> TablePartAll3;
													TablePartAll3.Empty();
													UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll3);
													for (auto It3 = TablePartAll3.CreateIterator(); It3; It3++)
													{
														ATablePart* TablePart3 = Cast<ATablePart>(*It3);
														if (TablePart3)
														{
															if (TablePart3->Table_Pos_Current == NewLocation)
															{
																if (TablePart3->Chess_Name == Note || (TablePart3->Chess_Name == King && TablePart3->Chess_Color != TablePart1->Chess_Color))
																{
																	//TablePart3->StaticMesh->SetMaterial(0, Material_Blue);

																	NewLocation.X = NewLocation.X;
																	NewLocation.Y = NewLocation.Y - 1.0f;

																	if (!Enumy_Chess_All.Contains(TablePart3))
																	{
																		Enumy_Chess_All.Add(TablePart3);
																	}

																}
																else {/* break; */ }
															}
														}
													}
													//break;
												}
												//break;
											}
										}

										for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
										{
											ATablePart* TablePart1 = Cast<ATablePart>(*It1);
											if (TablePart1)
											{
												if (TablePart1->Chess_Name == King)
												{
													LHasWay = true;
												}
											}
										}

										if (LHasWay)
										{
											F_Chess_Chackmate2(LEnemy);
										}

										else
										{
											Enumy_Chess_All.Empty();
											F_ClearAllTable();
										}
									}
								}
							}
						}
					}
				}


			}



		
		    break;
	    }

		//---------
	    case King:
	    {
			//1
			for (auto It1 = Enumy_Chess_King.CreateIterator(); It1; It1++)
			{
				ATablePart* TablePart1 = Cast<ATablePart>(*It1);
				if (TablePart1)
				{
					TArray<AActor*> TablePartAll11;
					TablePartAll11.Empty();
					UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll11);
					for (auto It11 = TablePartAll11.CreateIterator(); It11; It11++)
					{
						ATablePart* TablePart11 = Cast<ATablePart>(*It11);
						if (TablePart11)
						{
							FVector2D NewLocation;
							NewLocation.X = TablePart1->Table_Pos_Current.X + 1.0f;
							NewLocation.Y = TablePart1->Table_Pos_Current.Y + 1.0f;

							if (TablePart11->Table_Pos_Current == NewLocation)
							{
								if (TablePart11->Chess_Name == Note && TablePart11->Chess_Color != TablePart1->Chess_Color)
								{
									//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

									if (!Enumy_Chess_All.Contains(TablePart11))
									{
										Enumy_Chess_All.Add(TablePart11);
									}
								}
							}
						}
					}
				}
			}

			for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
			{
				ATablePart* TablePart1 = Cast<ATablePart>(*It1);
				if (TablePart1)
				{
					if (TablePart1->Chess_Name == King)
					{
						LHasWay = true;
					}
				}
			}

			if (LHasWay)
			{
				F_Chess_Chackmate2(LEnemy);
			}

			else 
			{
				Enumy_Chess_All.Empty();
				F_ClearAllTable();
				
				//2
				for (auto It1 = Enumy_Chess_King.CreateIterator(); It1; It1++)
				{
					ATablePart* TablePart1 = Cast<ATablePart>(*It1);
					if (TablePart1)
					{
						TArray<AActor*> TablePartAll11;
						TablePartAll11.Empty();
						UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll11);
						for (auto It11 = TablePartAll11.CreateIterator(); It11; It11++)
						{
							ATablePart* TablePart11 = Cast<ATablePart>(*It11);
							if (TablePart11)
							{
								FVector2D NewLocation;
								NewLocation.X = TablePart1->Table_Pos_Current.X + 1.0f;
								NewLocation.Y = TablePart1->Table_Pos_Current.Y - 1.0f;

								if (TablePart11->Table_Pos_Current == NewLocation)
								{
									if (TablePart11->Chess_Name == Note && TablePart11->Chess_Color != TablePart1->Chess_Color)
									{
										//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

										if (!Enumy_Chess_All.Contains(TablePart11))
										{
											Enumy_Chess_All.Add(TablePart11);
										}
									}
								}
							}
						}
					}
				}

				for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
				{
					ATablePart* TablePart1 = Cast<ATablePart>(*It1);
					if (TablePart1)
					{
						if (TablePart1->Chess_Name == King)
						{
							LHasWay = true;
						}
					}
				}

				if (LHasWay)
				{
					F_Chess_Chackmate2(LEnemy);
				}

				else
				{
					Enumy_Chess_All.Empty();
					F_ClearAllTable();
					
					//3
					for (auto It1 = Enumy_Chess_King.CreateIterator(); It1; It1++)
					{
						ATablePart* TablePart1 = Cast<ATablePart>(*It1);
						if (TablePart1)
						{
							TArray<AActor*> TablePartAll11;
							TablePartAll11.Empty();
							UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll11);
							for (auto It11 = TablePartAll11.CreateIterator(); It11; It11++)
							{
								ATablePart* TablePart11 = Cast<ATablePart>(*It11);
								if (TablePart11)
								{
									FVector2D NewLocation;
									NewLocation.X = TablePart1->Table_Pos_Current.X - 1.0f;
									NewLocation.Y = TablePart1->Table_Pos_Current.Y + 1.0f;

									if (TablePart11->Table_Pos_Current == NewLocation)
									{
										if (TablePart11->Chess_Name == Note && TablePart11->Chess_Color != TablePart1->Chess_Color)
										{
											//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

											if (!Enumy_Chess_All.Contains(TablePart11))
											{
												Enumy_Chess_All.Add(TablePart11);
											}
										}
									}
								}
							}
						}
					}

					for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
					{
						ATablePart* TablePart1 = Cast<ATablePart>(*It1);
						if (TablePart1)
						{
							if (TablePart1->Chess_Name == King)
							{
								LHasWay = true;
							}
						}
					}

					if (LHasWay)
					{
						F_Chess_Chackmate2(LEnemy);
					}

					else
					{
						Enumy_Chess_All.Empty();
						F_ClearAllTable();
						
						//4
						for (auto It1 = Enumy_Chess_King.CreateIterator(); It1; It1++)
						{
							ATablePart* TablePart1 = Cast<ATablePart>(*It1);
							if (TablePart1)
							{
								TArray<AActor*> TablePartAll11;
								TablePartAll11.Empty();
								UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll11);
								for (auto It11 = TablePartAll11.CreateIterator(); It11; It11++)
								{
									ATablePart* TablePart11 = Cast<ATablePart>(*It11);
									if (TablePart11)
									{
										FVector2D NewLocation;
										NewLocation.X = TablePart1->Table_Pos_Current.X - 1.0f;
										NewLocation.Y = TablePart1->Table_Pos_Current.Y - 1.0f;

										if (TablePart11->Table_Pos_Current == NewLocation)
										{
											if (TablePart11->Chess_Name == Note && TablePart11->Chess_Color != TablePart1->Chess_Color)
											{
												//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

												if (!Enumy_Chess_All.Contains(TablePart11))
												{
													Enumy_Chess_All.Add(TablePart11);
												}
											}
										}
									}
								}
							}
						}

						for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
						{
							ATablePart* TablePart1 = Cast<ATablePart>(*It1);
							if (TablePart1)
							{
								if (TablePart1->Chess_Name == King)
								{
									LHasWay = true;
								}
							}
						}

						if (LHasWay)
						{
							F_Chess_Chackmate2(LEnemy);
						}

						else
						{
							Enumy_Chess_All.Empty();
							F_ClearAllTable();
							
							//5
							for (auto It1 = Enumy_Chess_King.CreateIterator(); It1; It1++)
							{
								ATablePart* TablePart1 = Cast<ATablePart>(*It1);
								if (TablePart1)
								{
									TArray<AActor*> TablePartAll11;
									TablePartAll11.Empty();
									UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll11);
									for (auto It11 = TablePartAll11.CreateIterator(); It11; It11++)
									{
										ATablePart* TablePart11 = Cast<ATablePart>(*It11);
										if (TablePart11)
										{
											FVector2D NewLocation;
											NewLocation.X = TablePart1->Table_Pos_Current.X + 1.0f;
											NewLocation.Y = TablePart1->Table_Pos_Current.Y;

											if (TablePart11->Table_Pos_Current == NewLocation)
											{
												if (TablePart11->Chess_Name == Note && TablePart11->Chess_Color != TablePart1->Chess_Color)
												{
													//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

													if (!Enumy_Chess_All.Contains(TablePart11))
													{
														Enumy_Chess_All.Add(TablePart11);
													}
												}
											}
										}
									}
								}
							}

							for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
							{
								ATablePart* TablePart1 = Cast<ATablePart>(*It1);
								if (TablePart1)
								{
									if (TablePart1->Chess_Name == King)
									{
										LHasWay = true;
									}
								}
							}

							if (LHasWay)
							{
								F_Chess_Chackmate2(LEnemy);
							}

							else
							{
								Enumy_Chess_All.Empty();
								F_ClearAllTable();
								
								//6
								for (auto It1 = Enumy_Chess_King.CreateIterator(); It1; It1++)
								{
									ATablePart* TablePart1 = Cast<ATablePart>(*It1);
									if (TablePart1)
									{
										TArray<AActor*> TablePartAll11;
										TablePartAll11.Empty();
										UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll11);
										for (auto It11 = TablePartAll11.CreateIterator(); It11; It11++)
										{
											ATablePart* TablePart11 = Cast<ATablePart>(*It11);
											if (TablePart11)
											{
												FVector2D NewLocation;
												NewLocation.X = TablePart1->Table_Pos_Current.X - 1.0f;
												NewLocation.Y = TablePart1->Table_Pos_Current.Y;

												if (TablePart11->Table_Pos_Current == NewLocation)
												{
													if (TablePart11->Chess_Name == Note && TablePart11->Chess_Color != TablePart1->Chess_Color)
													{
														//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

														if (!Enumy_Chess_All.Contains(TablePart11))
														{
															Enumy_Chess_All.Add(TablePart11);
														}
													}
												}
											}
										}
									}
								}

								for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
								{
									ATablePart* TablePart1 = Cast<ATablePart>(*It1);
									if (TablePart1)
									{
										if (TablePart1->Chess_Name == King)
										{
											LHasWay = true;
										}
									}
								}

								if (LHasWay)
								{
									F_Chess_Chackmate2(LEnemy);
								}

								else
								{
									Enumy_Chess_All.Empty();
									F_ClearAllTable();
									
									//7
									for (auto It1 = Enumy_Chess_King.CreateIterator(); It1; It1++)
									{
										ATablePart* TablePart1 = Cast<ATablePart>(*It1);
										if (TablePart1)
										{
											TArray<AActor*> TablePartAll11;
											TablePartAll11.Empty();
											UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll11);
											for (auto It11 = TablePartAll11.CreateIterator(); It11; It11++)
											{
												ATablePart* TablePart11 = Cast<ATablePart>(*It11);
												if (TablePart11)
												{
													FVector2D NewLocation;
													NewLocation.X = TablePart1->Table_Pos_Current.X;
													NewLocation.Y = TablePart1->Table_Pos_Current.Y + 1.0f;

													if (TablePart11->Table_Pos_Current == NewLocation)
													{
														if (TablePart11->Chess_Name == Note && TablePart11->Chess_Color != TablePart1->Chess_Color)
														{
															//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

															if (!Enumy_Chess_All.Contains(TablePart11))
															{
																Enumy_Chess_All.Add(TablePart11);
															}
														}
													}
												}
											}
										}
									}

									for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
									{
										ATablePart* TablePart1 = Cast<ATablePart>(*It1);
										if (TablePart1)
										{
											if (TablePart1->Chess_Name == King)
											{
												LHasWay = true;
											}
										}
									}

									if (LHasWay)
									{
										F_Chess_Chackmate2(LEnemy);
									}

									else
									{
										Enumy_Chess_All.Empty();
										F_ClearAllTable();

										//8
										for (auto It1 = Enumy_Chess_King.CreateIterator(); It1; It1++)
										{
											ATablePart* TablePart1 = Cast<ATablePart>(*It1);
											if (TablePart1)
											{
												TArray<AActor*> TablePartAll11;
												TablePartAll11.Empty();
												UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll11);
												for (auto It11 = TablePartAll11.CreateIterator(); It11; It11++)
												{
													ATablePart* TablePart11 = Cast<ATablePart>(*It11);
													if (TablePart11)
													{
														FVector2D NewLocation;
														NewLocation.X = TablePart1->Table_Pos_Current.X;
														NewLocation.Y = TablePart1->Table_Pos_Current.Y - 1.0f;

														if (TablePart11->Table_Pos_Current == NewLocation)
														{
															if (TablePart11->Chess_Name == Note && TablePart11->Chess_Color != TablePart1->Chess_Color)
															{
																//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

																if (!Enumy_Chess_All.Contains(TablePart11))
																{
																	Enumy_Chess_All.Add(TablePart11);
																}
															}
														}
													}
												}
											}
										}

										for (auto It1 = Enumy_Chess_All.CreateIterator(); It1; It1++)
										{
											ATablePart* TablePart1 = Cast<ATablePart>(*It1);
											if (TablePart1)
											{
												if (TablePart1->Chess_Name == King)
												{
													LHasWay = true;
												}
											}
										}

										if (LHasWay)
										{
											F_Chess_Chackmate2(LEnemy);
										}

										else
										{
											Enumy_Chess_All.Empty();
											F_ClearAllTable();
										}
									}
								}
							}
						}
					}
				}
			}
		    break;
	    }
	}

}


//--Chech All Owners Chess Pos

void ATablePart::F_Chess_Chackmate2(ATablePart* LEnemy)
{


/*
//ForTEst
	GLog->Log(FString::FromInt(Enumy_Chess_All.Num()));
	for (auto a = Enumy_Chess_All.CreateIterator(); a; a++)
	{
		ATablePart* b = Cast<ATablePart>(*a);
		if (b)
		{		
			FName c = *b->GetName();
			FString e = c.ToString();		
			GLog->Log(FString(c.ToString()));
		}
	}
*/

	//Get Game Mode
	AChessCPPGameModeBase* GM_Base;
	GM_Base = Cast<AChessCPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	//Local var
	TArray<ATablePart*> LPawn;
	TArray<ATablePart*> LKnight;
	TArray<ATablePart*> LBishop;
	TArray<ATablePart*> LRock;
	TArray<ATablePart*> LQueen;
	TArray<ATablePart*> LKing;
	TArray<ATablePart*> LAll;

	bool LChessMate1 = true;


	LPawn.Empty(); 
	LKnight.Empty(); 
	LBishop.Empty(); 
	LRock.Empty(); 
	LQueen.Empty(); 
	LKing.Empty(); 
	LAll.Empty();

	TArray<AActor*> TablePartAll;
	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			if (TablePart->Chess_Color == GM_Base->CheyHod)
			{
				switch (TablePart->Chess_Name)
				{
				    case Note: {break; }
				    case Pawn:
				    {
					    LPawn.Add(TablePart);
					    break;
				    }
				    case Knight:
				    {
					    LKnight.Add(TablePart);
					    break;
				    }
				    case Bishop:
				    {
					    LBishop.Add(TablePart);
					    break;
				    }
				    case Rock:
				    {
					    LRock.Add(TablePart);
					    break;
				    }
				    case Queen:
				    {
					    LQueen.Add(TablePart);
					    break;
				    }
				    case King:
				    {
					    LKing.Add(TablePart);
					    break;
				    }
				}
			}
		}
	}

	F_ClearAllTable();

	//----------------
	//pawn
	switch (GM_Base->CheyHod)
	{
	    case None: {break; }
		case White:
		{
			//1
			for (auto It1 = LPawn.CreateIterator(); It1; It1++)
			{
				ATablePart* TablePart1 = Cast<ATablePart>(*It1);
				if (TablePart1)
				{
					TArray<AActor*> TablePartAll2;
					TablePartAll2.Empty();
					UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
					for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
					{
						ATablePart* TablePart2 = Cast<ATablePart>(*It2);
						if (TablePart2)
						{
							FVector2D NewLocation;
							NewLocation.X = TablePart1->Table_Pos_Current.X - 1.0f;
							NewLocation.Y = TablePart1->Table_Pos_Current.Y + 1.0f;

							if (TablePart2->Table_Pos_Current == NewLocation && TablePart2->Table_Pos_Current == LEnemy->Table_Pos_Current)
							{
								//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);
								if (!LAll.Contains(TablePart2))
								{
									LAll.Add(TablePart2);
								}
							}
						}
					}
				}
			}

			//2
			for (auto It1 = LPawn.CreateIterator(); It1; It1++)
			{
				ATablePart* TablePart1 = Cast<ATablePart>(*It1);
				if (TablePart1)
				{
					TArray<AActor*> TablePartAll2;
					TablePartAll2.Empty();
					UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
					for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
					{
						ATablePart* TablePart2 = Cast<ATablePart>(*It2);
						if (TablePart2)
						{
							FVector2D NewLocation;
							NewLocation.X = TablePart1->Table_Pos_Current.X + 1.0f;
							NewLocation.Y = TablePart1->Table_Pos_Current.Y + 1.0f;

							if (TablePart2->Table_Pos_Current == NewLocation && TablePart2->Table_Pos_Current == LEnemy->Table_Pos_Current)
							{
								//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);
								if (!LAll.Contains(TablePart2))
								{
									LAll.Add(TablePart2);
								}
							}
						}
					}
				}
			}

			//3
			for (auto It1 = LPawn.CreateIterator(); It1; It1++)
			{
				ATablePart* TablePart1 = Cast<ATablePart>(*It1);
				if (TablePart1)
				{
					if (TablePart1->Table_Pos_Current.Y != 2.0f)
					{
						TArray<AActor*> TablePartAll2;
						TablePartAll2.Empty();
						UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
						for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
						{
							ATablePart* TablePart2 = Cast<ATablePart>(*It2);
							if (TablePart2)
							{
								FVector2D NewLocation;
								NewLocation.X = TablePart1->Table_Pos_Current.X;
								NewLocation.Y = TablePart1->Table_Pos_Current.Y + 1.0f;

								if (TablePart2->Table_Pos_Current == NewLocation && TablePart2->Chess_Name == Note)
								{
									//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

									if (!LAll.Contains(TablePart2))
									{
										LAll.Add(TablePart2);
									}
								}
							}
						}
					}
				}
			}

			//4
			for (auto It1 = LPawn.CreateIterator(); It1; It1++)
			{
				ATablePart* TablePart1 = Cast<ATablePart>(*It1);
				if (TablePart1)
				{
					if (TablePart1->Table_Pos_Current.Y == 2.0f)
					{
						TArray<AActor*> TablePartAll2;
						TablePartAll2.Empty();
						UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
						for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
						{
							ATablePart* TablePart2 = Cast<ATablePart>(*It2);
							if (TablePart2)
							{
								FVector2D NewLocation;
								NewLocation.X = TablePart1->Table_Pos_Current.X;
								NewLocation.Y = TablePart1->Table_Pos_Current.Y + 1.0f;

								if (TablePart2->Table_Pos_Current == NewLocation && TablePart2->Chess_Name == Note)
								{
									//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

									if (!LAll.Contains(TablePart2))
									{
										LAll.Add(TablePart2);
									}

									if (TablePart1->Table_Pos_Current.Y == 2.0f)
									{
										TArray<AActor*> TablePartAll3;
										TablePartAll3.Empty();
										UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll3);
										for (auto It3 = TablePartAll3.CreateIterator(); It3; It3++)
										{
											ATablePart* TablePart3 = Cast<ATablePart>(*It3);
											if (TablePart3)
											{
												FVector2D NewLocation3;
												NewLocation3.X = TablePart1->Table_Pos_Current.X;
												NewLocation3.Y = TablePart1->Table_Pos_Current.Y + 2.0f;

												if (TablePart3->Table_Pos_Current == NewLocation3 && TablePart3->Chess_Name == Note)
												{
													//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

													if (!LAll.Contains(TablePart2))
													{
														LAll.Add(TablePart2);
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}

			break;
		}
		case Black:
		{
			//1
			for (auto It1 = LPawn.CreateIterator(); It1; It1++)
			{
				ATablePart* TablePart1 = Cast<ATablePart>(*It1);
				if (TablePart1)
				{
					TArray<AActor*> TablePartAll2;
					TablePartAll2.Empty();
					UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
					for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
					{
						ATablePart* TablePart2 = Cast<ATablePart>(*It2);
						if (TablePart2)
						{
							FVector2D NewLocation;
							NewLocation.X = TablePart1->Table_Pos_Current.X - 1.0f;
							NewLocation.Y = TablePart1->Table_Pos_Current.Y - 1.0f;

							if (TablePart2->Table_Pos_Current == NewLocation && TablePart2->Table_Pos_Current == LEnemy->Table_Pos_Current)
							{
								//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);
								if (!LAll.Contains(TablePart2))
								{
									LAll.Add(TablePart2);
								}
							}
						}
					}
				}
			}

			//2
			for (auto It1 = LPawn.CreateIterator(); It1; It1++)
			{
				ATablePart* TablePart1 = Cast<ATablePart>(*It1);
				if (TablePart1)
				{
					TArray<AActor*> TablePartAll2;
					TablePartAll2.Empty();
					UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
					for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
					{
						ATablePart* TablePart2 = Cast<ATablePart>(*It2);
						if (TablePart2)
						{
							FVector2D NewLocation;
							NewLocation.X = TablePart1->Table_Pos_Current.X + 1.0f;
							NewLocation.Y = TablePart1->Table_Pos_Current.Y - 1.0f;

							if (TablePart2->Table_Pos_Current == NewLocation && TablePart2->Table_Pos_Current == LEnemy->Table_Pos_Current)
							{
								//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);
								if (!LAll.Contains(TablePart2))
								{
									LAll.Add(TablePart2);
								}
							}
						}
					}
				}
			}

			//3
			for (auto It1 = LPawn.CreateIterator(); It1; It1++)
			{
				ATablePart* TablePart1 = Cast<ATablePart>(*It1);
				if (TablePart1)
				{
					if (TablePart1->Table_Pos_Current.Y != 7.0f)
					{
						TArray<AActor*> TablePartAll2;
						TablePartAll2.Empty();
						UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
						for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
						{
							ATablePart* TablePart2 = Cast<ATablePart>(*It2);
							if (TablePart2)
							{
								FVector2D NewLocation;
								NewLocation.X = TablePart1->Table_Pos_Current.X;
								NewLocation.Y = TablePart1->Table_Pos_Current.Y - 1.0f;

								if (TablePart2->Table_Pos_Current == NewLocation && TablePart2->Chess_Name == Note)
								{
									//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

									if (!LAll.Contains(TablePart2))
									{
										LAll.Add(TablePart2);
									}
								}
							}
						}
					}
				}
			}

			//4
			for (auto It1 = LPawn.CreateIterator(); It1; It1++)
			{
				ATablePart* TablePart1 = Cast<ATablePart>(*It1);
				if (TablePart1)
				{
					if (TablePart1->Table_Pos_Current.Y == 7.0f)
					{
						TArray<AActor*> TablePartAll2;
						TablePartAll2.Empty();
						UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
						for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
						{
							ATablePart* TablePart2 = Cast<ATablePart>(*It2);
							if (TablePart2)
							{
								FVector2D NewLocation;
								NewLocation.X = TablePart1->Table_Pos_Current.X;
								NewLocation.Y = TablePart1->Table_Pos_Current.Y - 1.0f;

								if (TablePart2->Table_Pos_Current == NewLocation && TablePart2->Chess_Name == Note)
								{
									//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

									if (!LAll.Contains(TablePart2))
									{
										LAll.Add(TablePart2);
									}

									if (TablePart1->Table_Pos_Current.Y == 7.0f)
									{
										TArray<AActor*> TablePartAll3;
										TablePartAll3.Empty();
										UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll3);
										for (auto It3 = TablePartAll3.CreateIterator(); It3; It3++)
										{
											ATablePart* TablePart3 = Cast<ATablePart>(*It3);
											if (TablePart3)
											{
												FVector2D NewLocation3;
												NewLocation3.X = TablePart1->Table_Pos_Current.X;
												NewLocation3.Y = TablePart1->Table_Pos_Current.Y - 2.0f;

												if (TablePart3->Table_Pos_Current == NewLocation3 && TablePart3->Chess_Name == Note)
												{
													//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

													if (!LAll.Contains(TablePart2))
													{
														LAll.Add(TablePart2);
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}

			break;
		}
	}


	//----------------
	//knight
	//1
	for (auto It1 = LKnight.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It1);
		if (TablePart)
		{
			TArray<AActor*> TablePartAll2;
			TablePartAll2.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
			for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
			{
				ATablePart* TablePart2 = Cast<ATablePart>(*It2);
				if (TablePart2)
				{
					FVector2D NewLocation;
					NewLocation.X = TablePart->Table_Pos_Current.X - 1.0f;
					NewLocation.Y = TablePart->Table_Pos_Current.Y + 2.0f;

					if (TablePart2->Table_Pos_Current == NewLocation && TablePart2->Chess_Color != TablePart->Chess_Color)
					{
						//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);
						if (!LAll.Contains(TablePart2))
						{
							LAll.Add(TablePart2);
						}
					}
				}
			}
		}
	}

	//2
	for (auto It1 = LKnight.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It1);
		if (TablePart)
		{
			TArray<AActor*> TablePartAll2;
			TablePartAll2.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
			for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
			{
				ATablePart* TablePart2 = Cast<ATablePart>(*It2);
				if (TablePart2)
				{
					FVector2D NewLocation;
					NewLocation.X = TablePart->Table_Pos_Current.X + 1.0f;
					NewLocation.Y = TablePart->Table_Pos_Current.Y + 2.0f;

					if (TablePart2->Table_Pos_Current == NewLocation && TablePart2->Chess_Color != TablePart->Chess_Color)
					{
						//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);
						if (!LAll.Contains(TablePart2))
						{
							LAll.Add(TablePart2);
						}
					}
				}
			}
		}
	}

	//3
	for (auto It1 = LKnight.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It1);
		if (TablePart)
		{
			TArray<AActor*> TablePartAll2;
			TablePartAll2.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
			for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
			{
				ATablePart* TablePart2 = Cast<ATablePart>(*It2);
				if (TablePart2)
				{
					FVector2D NewLocation;
					NewLocation.X = TablePart->Table_Pos_Current.X + 2.0f;
					NewLocation.Y = TablePart->Table_Pos_Current.Y + 1.0f;

					if (TablePart2->Table_Pos_Current == NewLocation && TablePart2->Chess_Color != TablePart->Chess_Color)
					{
						//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);
						if (!LAll.Contains(TablePart2))
						{
							LAll.Add(TablePart2);
						}
					}
				}
			}
		}
	}

	//4
	for (auto It1 = LKnight.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It1);
		if (TablePart)
		{
			TArray<AActor*> TablePartAll2;
			TablePartAll2.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
			for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
			{
				ATablePart* TablePart2 = Cast<ATablePart>(*It2);
				if (TablePart2)
				{
					FVector2D NewLocation;
					NewLocation.X = TablePart->Table_Pos_Current.X + 2.0f;
					NewLocation.Y = TablePart->Table_Pos_Current.Y - 1.0f;

					if (TablePart2->Table_Pos_Current == NewLocation && TablePart2->Chess_Color != TablePart->Chess_Color)
					{
						//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);
						if (!LAll.Contains(TablePart2))
						{
							LAll.Add(TablePart2);
						}
					}
				}
			}
		}
	}

	//5
	for (auto It1 = LKnight.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It1);
		if (TablePart)
		{
			TArray<AActor*> TablePartAll2;
			TablePartAll2.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
			for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
			{
				ATablePart* TablePart2 = Cast<ATablePart>(*It2);
				if (TablePart2)
				{
					FVector2D NewLocation;
					NewLocation.X = TablePart->Table_Pos_Current.X + 1.0f;
					NewLocation.Y = TablePart->Table_Pos_Current.Y - 2.0f;

					if (TablePart2->Table_Pos_Current == NewLocation && TablePart2->Chess_Color != TablePart->Chess_Color)
					{
						//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);
						if (!LAll.Contains(TablePart2))
						{
							LAll.Add(TablePart2);
						}
					}
				}
			}
		}
	}

	//6
	for (auto It1 = LKnight.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It1);
		if (TablePart)
		{
			TArray<AActor*> TablePartAll2;
			TablePartAll2.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
			for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
			{
				ATablePart* TablePart2 = Cast<ATablePart>(*It2);
				if (TablePart2)
				{
					FVector2D NewLocation;
					NewLocation.X = TablePart->Table_Pos_Current.X - 1.0f;
					NewLocation.Y = TablePart->Table_Pos_Current.Y - 2.0f;

					if (TablePart2->Table_Pos_Current == NewLocation && TablePart2->Chess_Color != TablePart->Chess_Color)
					{
						//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);
						if (!LAll.Contains(TablePart2))
						{
							LAll.Add(TablePart2);
						}
					}
				}
			}
		}
	}

	//7
	for (auto It1 = LKnight.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It1);
		if (TablePart)
		{
			TArray<AActor*> TablePartAll2;
			TablePartAll2.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
			for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
			{
				ATablePart* TablePart2 = Cast<ATablePart>(*It2);
				if (TablePart2)
				{
					FVector2D NewLocation;
					NewLocation.X = TablePart->Table_Pos_Current.X - 2.0f;
					NewLocation.Y = TablePart->Table_Pos_Current.Y + 1.0f;

					if (TablePart2->Table_Pos_Current == NewLocation && TablePart2->Chess_Color != TablePart->Chess_Color)
					{
						//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);
						if (!LAll.Contains(TablePart2))
						{
							LAll.Add(TablePart2);
						}
					}
				}
			}
		}
	}

	//8
	for (auto It1 = LKnight.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It1);
		if (TablePart)
		{
			TArray<AActor*> TablePartAll2;
			TablePartAll2.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
			for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
			{
				ATablePart* TablePart2 = Cast<ATablePart>(*It2);
				if (TablePart2)
				{
					FVector2D NewLocation;
					NewLocation.X = TablePart->Table_Pos_Current.X - 2.0f;
					NewLocation.Y = TablePart->Table_Pos_Current.Y - 1.0f;

					if (TablePart2->Table_Pos_Current == NewLocation && TablePart2->Chess_Color != TablePart->Chess_Color)
					{
						//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);
						if (!LAll.Contains(TablePart2))
						{
							LAll.Add(TablePart2);
						}
					}
				}
			}
		}
	}

	//----------------
	//bishop
	//1
	for (auto It1 = LBishop.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It1);
		if (TablePart)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart->Table_Pos_Current.X + 1.0f;
			NewLocation.Y = TablePart->Table_Pos_Current.Y + 1.0f;

			for (int32 It2 = 0; It2 <= 7; It2++)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
				{
					ATablePart* TablePart3 = Cast<ATablePart>(*It3);
					if (TablePart3)
					{
						if (TablePart3->Table_Pos_Current == NewLocation)
						{
							if (TablePart3->Chess_Color != TablePart->Chess_Color)
							{
								//TablePart3->StaticMesh->SetMaterial(0, Material_Blue);

								NewLocation.X = NewLocation.X + 1.0f;
								NewLocation.Y = NewLocation.Y + 1.0f;

								if (!LAll.Contains(TablePart3))
								{
									LAll.Add(TablePart3);
								}
							}
							else { /*break;*/ }
						}
					}
				}
				// break;
			}
			//break;
		}
	}

	//2
	for (auto It1 = LBishop.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It1);
		if (TablePart)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart->Table_Pos_Current.X + 1.0f;
			NewLocation.Y = TablePart->Table_Pos_Current.Y - 1.0f;

			for (int32 It2 = 0; It2 <= 7; It2++)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
				{
					ATablePart* TablePart3 = Cast<ATablePart>(*It3);
					if (TablePart3)
					{
						if (TablePart3->Table_Pos_Current == NewLocation)
						{
							if (TablePart3->Chess_Color != TablePart->Chess_Color)
							{
								//TablePart3->StaticMesh->SetMaterial(0, Material_Blue);

								NewLocation.X = NewLocation.X + 1.0f;
								NewLocation.Y = NewLocation.Y - 1.0f;

								if (!LAll.Contains(TablePart3))
								{
									LAll.Add(TablePart3);
								}
							}
							else { /*break;*/ }
						}
					}
				}
				// break;
			}
			//break;
		}
	}

	//3
	for (auto It1 = LBishop.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It1);
		if (TablePart)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart->Table_Pos_Current.X - 1.0f;
			NewLocation.Y = TablePart->Table_Pos_Current.Y + 1.0f;

			for (int32 It2 = 0; It2 <= 7; It2++)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
				{
					ATablePart* TablePart3 = Cast<ATablePart>(*It3);
					if (TablePart3)
					{
						if (TablePart3->Table_Pos_Current == NewLocation)
						{
							if (TablePart3->Chess_Color != TablePart->Chess_Color)
							{
								//TablePart3->StaticMesh->SetMaterial(0, Material_Blue);

								NewLocation.X = NewLocation.X - 1.0f;
								NewLocation.Y = NewLocation.Y + 1.0f;

								if (!LAll.Contains(TablePart3))
								{
									LAll.Add(TablePart3);
								}
							}
							else { /*break;*/ }
						}
					}
				}
				// break;
			}
			//break;
		}
	}

	//4
	for (auto It1 = LBishop.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It1);
		if (TablePart)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart->Table_Pos_Current.X - 1.0f;
			NewLocation.Y = TablePart->Table_Pos_Current.Y - 1.0f;

			for (int32 It2 = 0; It2 <= 7; It2++)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
				{
					ATablePart* TablePart3 = Cast<ATablePart>(*It3);
					if (TablePart3)
					{
						if (TablePart3->Table_Pos_Current == NewLocation)
						{
							if (TablePart3->Chess_Color != TablePart->Chess_Color)
							{
								//TablePart3->StaticMesh->SetMaterial(0, Material_Blue);

								NewLocation.X = NewLocation.X - 1.0f;
								NewLocation.Y = NewLocation.Y - 1.0f;

								if (!LAll.Contains(TablePart3))
								{
									LAll.Add(TablePart3);
								}
							}
							else { /*break;*/ }
						}
					}
				}
				// break;
			}
			//break;
		}
	}

	//----------------
	//rock
	//1
	for (auto It1 = LRock.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It1);
		if (TablePart)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart->Table_Pos_Current.X + 1.0f;
			NewLocation.Y = TablePart->Table_Pos_Current.Y;

			for (int32 It2 = 0; It2 <= 7; It2++)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
				{
					ATablePart* TablePart3 = Cast<ATablePart>(*It3);
					if (TablePart3)
					{
						if (TablePart3->Table_Pos_Current == NewLocation)
						{
							if (TablePart3->Chess_Color != TablePart->Chess_Color)
							{
								//TablePart3->StaticMesh->SetMaterial(0, Material_Blue);

								NewLocation.X = NewLocation.X + 1.0f;
								NewLocation.Y = NewLocation.Y;

								if (!LAll.Contains(TablePart3))
								{
									LAll.Add(TablePart3);
								}
							}
							else { /*break;*/ }
						}
					}
				}
				// break;
			}
			//break;
		}
	}

	//2
	for (auto It1 = LRock.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It1);
		if (TablePart)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart->Table_Pos_Current.X - 1.0f;
			NewLocation.Y = TablePart->Table_Pos_Current.Y;

			for (int32 It2 = 0; It2 <= 7; It2++)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
				{
					ATablePart* TablePart3 = Cast<ATablePart>(*It3);
					if (TablePart3)
					{
						if (TablePart3->Table_Pos_Current == NewLocation)
						{
							if (TablePart3->Chess_Color != TablePart->Chess_Color)
							{
								//TablePart3->StaticMesh->SetMaterial(0, Material_Blue);

								NewLocation.X = NewLocation.X - 1.0f;
								NewLocation.Y = NewLocation.Y;

								if (!LAll.Contains(TablePart3))
								{
									LAll.Add(TablePart3);
								}
							}
							else { /*break;*/ }
						}
					}
				}
				// break;
			}
			//break;
		}
	}

	//3
	for (auto It1 = LRock.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It1);
		if (TablePart)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart->Table_Pos_Current.X;
			NewLocation.Y = TablePart->Table_Pos_Current.Y + 1.0f;

			for (int32 It2 = 0; It2 <= 7; It2++)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
				{
					ATablePart* TablePart3 = Cast<ATablePart>(*It3);
					if (TablePart3)
					{
						if (TablePart3->Table_Pos_Current == NewLocation)
						{
							if (TablePart3->Chess_Color != TablePart->Chess_Color)
							{
								//TablePart3->StaticMesh->SetMaterial(0, Material_Blue);

								NewLocation.X = NewLocation.X;
								NewLocation.Y = NewLocation.Y + 1.0f;

								if (!LAll.Contains(TablePart3))
								{
									LAll.Add(TablePart3);
								}
							}
							else { /*break;*/ }
						}
					}
				}
				// break;
			}
			//break;
		}
	}

	//4
	for (auto It1 = LRock.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It1);
		if (TablePart)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart->Table_Pos_Current.X;
			NewLocation.Y = TablePart->Table_Pos_Current.Y - 1.0f;

			for (int32 It2 = 0; It2 <= 7; It2++)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
				{
					ATablePart* TablePart3 = Cast<ATablePart>(*It3);
					if (TablePart3)
					{
						if (TablePart3->Table_Pos_Current == NewLocation)
						{
							if (TablePart3->Chess_Color != TablePart->Chess_Color)
							{
								//TablePart3->StaticMesh->SetMaterial(0, Material_Blue);

								NewLocation.X = NewLocation.X;
								NewLocation.Y = NewLocation.Y - 1.0f;

								if (!LAll.Contains(TablePart3))
								{
									LAll.Add(TablePart3);
								}
							}
							else { /*break;*/ }
						}
					}
				}
				// break;
			}
			//break;
		}
	}

	//----------------
	//queen
	//1
	for (auto It1 = LQueen.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It1);
		if (TablePart)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart->Table_Pos_Current.X + 1.0f;
			NewLocation.Y = TablePart->Table_Pos_Current.Y + 1.0f;

			for (int32 It2 = 0; It2 <= 7; It2++)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
				{
					ATablePart* TablePart3 = Cast<ATablePart>(*It3);
					if (TablePart3)
					{
						if (TablePart3->Table_Pos_Current == NewLocation)
						{
							if (TablePart3->Chess_Color != TablePart->Chess_Color)
							{
								//TablePart3->StaticMesh->SetMaterial(0, Material_Blue);

								NewLocation.X = NewLocation.X + 1.0f;
								NewLocation.Y = NewLocation.Y + 1.0f;

								if (!LAll.Contains(TablePart3))
								{
									LAll.Add(TablePart3);
								}
							}
							else {  /*break;*/  }
						}
					}
				} 
				 //break;
			}
			//break;
		}
	}
	
	//2
	for (auto It1 = LQueen.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It1);
		if (TablePart)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart->Table_Pos_Current.X + 1.0f;
			NewLocation.Y = TablePart->Table_Pos_Current.Y - 1.0f;

			for (int32 It2 = 0; It2 <= 7; It2++)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
				{
					ATablePart* TablePart3 = Cast<ATablePart>(*It3);
					if (TablePart3)
					{
						if (TablePart3->Table_Pos_Current == NewLocation)
						{
							if (TablePart3->Chess_Color != TablePart->Chess_Color)
							{
								//TablePart3->StaticMesh->SetMaterial(0, Material_Blue);

								NewLocation.X = NewLocation.X + 1.0f;
								NewLocation.Y = NewLocation.Y - 1.0f;

								if (!LAll.Contains(TablePart3))
								{
									LAll.Add(TablePart3);
								}
							}
							else {  /*break;*/  }
						}
					}
				}
				 //break;
			}
			//break;
		}
	}

	//3
	for (auto It1 = LQueen.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It1);
		if (TablePart)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart->Table_Pos_Current.X - 1.0f;
			NewLocation.Y = TablePart->Table_Pos_Current.Y + 1.0f;

			for (int32 It2 = 0; It2 <= 7; It2++)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
				{
					ATablePart* TablePart3 = Cast<ATablePart>(*It3);
					if (TablePart3)
					{
						if (TablePart3->Table_Pos_Current == NewLocation)
						{
							if (TablePart3->Chess_Color != TablePart->Chess_Color)
							{
								//TablePart3->StaticMesh->SetMaterial(0, Material_Blue);

								NewLocation.X = NewLocation.X - 1.0f;
								NewLocation.Y = NewLocation.Y + 1.0f;

								if (!LAll.Contains(TablePart3))
								{
									LAll.Add(TablePart3);
								}
							}
							else {  /*break;*/  }
						}
					}
				}
				// break;
			}
			//break;
		}
	}

	//4
	for (auto It1 = LQueen.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It1);
		if (TablePart)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart->Table_Pos_Current.X - 1.0f;
			NewLocation.Y = TablePart->Table_Pos_Current.Y - 1.0f;

			for (int32 It2 = 0; It2 <= 7; It2++)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
				{
					ATablePart* TablePart3 = Cast<ATablePart>(*It3);
					if (TablePart3)
					{
						if (TablePart3->Table_Pos_Current == NewLocation)
						{
							if (TablePart3->Chess_Color != TablePart->Chess_Color)
							{
								//TablePart3->StaticMesh->SetMaterial(0, Material_Blue);

								NewLocation.X = NewLocation.X - 1.0f;
								NewLocation.Y = NewLocation.Y - 1.0f;

								if (!LAll.Contains(TablePart3))
								{
									LAll.Add(TablePart3);
								}
							}
							else {  /*break;*/ }
						}
					}
				}
				 //break;
			}
			//break;
		}
	}

	//5
	for (auto It1 = LQueen.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It1);
		if (TablePart)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart->Table_Pos_Current.X + 1.0f;
			NewLocation.Y = TablePart->Table_Pos_Current.Y;

			for (int32 It2 = 0; It2 <= 7; It2++)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
				{
					ATablePart* TablePart3 = Cast<ATablePart>(*It3);
					if (TablePart3)
					{
						if (TablePart3->Table_Pos_Current == NewLocation)
						{
							if (TablePart3->Chess_Color != TablePart->Chess_Color)
							{
								//TablePart3->StaticMesh->SetMaterial(0, Material_Blue);

								NewLocation.X = NewLocation.X + 1.0f;
								NewLocation.Y = NewLocation.Y;

								if (!LAll.Contains(TablePart3))
								{
									LAll.Add(TablePart3);
								}
							}
							else {  /*break;*/  }
						}
					}
				}
				 //break;
			}
			//break;
		}
	}

	//6
	for (auto It1 = LQueen.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It1);
		if (TablePart)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart->Table_Pos_Current.X - 1.0f;
			NewLocation.Y = TablePart->Table_Pos_Current.Y;

			for (int32 It2 = 0; It2 <= 7; It2++)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
				{
					ATablePart* TablePart3 = Cast<ATablePart>(*It3);
					if (TablePart3)
					{
						if (TablePart3->Table_Pos_Current == NewLocation)
						{
							if (TablePart3->Chess_Color != TablePart->Chess_Color)
							{
								//TablePart3->StaticMesh->SetMaterial(0, Material_Blue);

								NewLocation.X = NewLocation.X - 1.0f;
								NewLocation.Y = NewLocation.Y;

								if (!LAll.Contains(TablePart3))
								{
									LAll.Add(TablePart3);
								}
							}
							else { /*break;*/ }
						}
					}
				}
				 //break;
			}
			//break;
		}
	}

	//7
	for (auto It1 = LQueen.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It1);
		if (TablePart)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart->Table_Pos_Current.X;
			NewLocation.Y = TablePart->Table_Pos_Current.Y + 1.0f;

			for (int32 It2 = 0; It2 <= 7; It2++)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
				{
					ATablePart* TablePart3 = Cast<ATablePart>(*It3);
					if (TablePart3)
					{
						if (TablePart3->Table_Pos_Current == NewLocation)
						{
							if (TablePart3->Chess_Color != TablePart->Chess_Color)
							{
								//TablePart3->StaticMesh->SetMaterial(0, Material_Blue);

								NewLocation.X = NewLocation.X;
								NewLocation.Y = NewLocation.Y + 1.0f;

								if (!LAll.Contains(TablePart3))
								{
									LAll.Add(TablePart3);
								}
							}
							else {  /*break;*/  }
						}
					}
				}
				 //break;
			}
			//break;
		}
	}

	//8
	for (auto It1 = LQueen.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It1);
		if (TablePart)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart->Table_Pos_Current.X;
			NewLocation.Y = TablePart->Table_Pos_Current.Y - 1.0f;

			for (int32 It2 = 0; It2 <= 7; It2++)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
				{
					ATablePart* TablePart3 = Cast<ATablePart>(*It3);
					if (TablePart3)
					{
						if (TablePart3->Table_Pos_Current == NewLocation)
						{
							if (TablePart3->Chess_Color != TablePart->Chess_Color)
							{
								//TablePart3->StaticMesh->SetMaterial(0, Material_Blue);

								NewLocation.X = NewLocation.X;
								NewLocation.Y = NewLocation.Y - 1.0f;

								if (!LAll.Contains(TablePart3))
								{
									LAll.Add(TablePart3);
								}
							}
							else { /*break;*/ }
						}
					}
				}
				 //break;
			}
			//break;
		}
	}

	//----------------
	/*
	//FOR TEST
	GLog->Log(FString::FromInt(LAll.Num()));
	for (auto a = LAll.CreateIterator(); a; a++)
	{
		ATablePart* b = Cast<ATablePart>(*a);
		if (b)
		{
			FName c = *b->GetName();
			FString e = c.ToString();
			GLog->Log(FString(c.ToString()));
		}
	}
	*/
	//----------------
	//king
	for (auto It1 = LAll.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It1);
		if (TablePart)
		{
			if (Enumy_Chess_All.Contains(TablePart))
			{
				LChessMate1 = false;
			}
		}
	}

	if (LChessMate1)
	{
		LPawn.Empty();
		LKnight.Empty();
		LBishop.Empty();
		LRock.Empty();
		LQueen.Empty();
		LKing.Empty();
		LAll.Empty();

		F_ClearAllTable();

		F_Chess_CheckPos(0);

		TArray<AActor*> TablePartAll4;
		TablePartAll4.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll4);
		for (auto It4 = TablePartAll4.CreateIterator(); It4; It4++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It4);
			if (TablePart)
			{
				if (TablePart->Chess_Color == GM_Base->CheyHod)
				{
					switch (TablePart->Chess_Name)
					{
					    case Note: {break; }
					    case Pawn:
					    {
						    LPawn.Add(TablePart);
						    break;
					    }
					    case Knight:
					    {
						    LKnight.Add(TablePart);
						    break;
					    }
					    case Bishop:
					    {
						    LBishop.Add(TablePart);
						    break;
					    }
					    case Rock:
					    {
						    LRock.Add(TablePart);
						    break;
					    }
					    case Queen:
					    {
						    LQueen.Add(TablePart);
						    break;
					    }
					    case King:
					    {
						    LKing.Add(TablePart);
						    break;
					    }
					}
				}
			}
		}

		//1
		for (auto It1 = LKing.CreateIterator(); It1; It1++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It1);
			if (TablePart)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
				{
					ATablePart* TablePart2 = Cast<ATablePart>(*It2);
					if (TablePart2)
					{
						if (!Enumy_Chess_All.Contains(TablePart2))
						{
							FVector2D NewLocation;
							NewLocation.X = TablePart->Table_Pos_Current.X + 1.0f;
							NewLocation.Y = TablePart->Table_Pos_Current.Y + 1.0f;

							if (TablePart2->Table_Pos_Current == NewLocation)
							{
								if (TablePart->Chess_Color != TablePart2->Chess_Color)
								{
									//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

									if (!LAll.Contains(TablePart2))
									{
										LAll.Add(TablePart2);
									}
								}
							}
						}
					}
				}
			}
		}

		//2
		for (auto It1 = LKing.CreateIterator(); It1; It1++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It1);
			if (TablePart)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
				{
					ATablePart* TablePart2 = Cast<ATablePart>(*It2);
					if (TablePart2)
					{
						if (!Enumy_Chess_All.Contains(TablePart2))
						{
							FVector2D NewLocation;
							NewLocation.X = TablePart->Table_Pos_Current.X + 1.0f;
							NewLocation.Y = TablePart->Table_Pos_Current.Y - 1.0f;

							if (TablePart2->Table_Pos_Current == NewLocation)
							{
								if (TablePart->Chess_Color != TablePart2->Chess_Color)
								{
									//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

									if (!LAll.Contains(TablePart2))
									{
										LAll.Add(TablePart2);
									}
								}
							}
						}
					}
				}
			}
		}

		//3
		for (auto It1 = LKing.CreateIterator(); It1; It1++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It1);
			if (TablePart)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
				{
					ATablePart* TablePart2 = Cast<ATablePart>(*It2);
					if (TablePart2)
					{
						if (!Enumy_Chess_All.Contains(TablePart2))
						{
							FVector2D NewLocation;
							NewLocation.X = TablePart->Table_Pos_Current.X - 1.0f;
							NewLocation.Y = TablePart->Table_Pos_Current.Y + 1.0f;

							if (TablePart2->Table_Pos_Current == NewLocation)
							{
								if (TablePart->Chess_Color != TablePart2->Chess_Color)
								{
									//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

									if (!LAll.Contains(TablePart2))
									{
										LAll.Add(TablePart2);
									}
								}
							}
						}
					}
				}
			}
		}

		//4
		for (auto It1 = LKing.CreateIterator(); It1; It1++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It1);
			if (TablePart)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
				{
					ATablePart* TablePart2 = Cast<ATablePart>(*It2);
					if (TablePart2)
					{
						if (!Enumy_Chess_All.Contains(TablePart2))
						{
							FVector2D NewLocation;
							NewLocation.X = TablePart->Table_Pos_Current.X - 1.0f;
							NewLocation.Y = TablePart->Table_Pos_Current.Y - 1.0f;

							if (TablePart2->Table_Pos_Current == NewLocation)
							{
								if (TablePart->Chess_Color != TablePart2->Chess_Color)
								{
									//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

									if (!LAll.Contains(TablePart2))
									{
										LAll.Add(TablePart2);
									}
								}
							}
						}
					}
				}
			}
		}

		//5
		for (auto It1 = LKing.CreateIterator(); It1; It1++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It1);
			if (TablePart)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
				{
					ATablePart* TablePart2 = Cast<ATablePart>(*It2);
					if (TablePart2)
					{
						if (!Enumy_Chess_All.Contains(TablePart2))
						{
							FVector2D NewLocation;
							NewLocation.X = TablePart->Table_Pos_Current.X + 1.0f;
							NewLocation.Y = TablePart->Table_Pos_Current.Y;

							if (TablePart2->Table_Pos_Current == NewLocation)
							{
								if (TablePart->Chess_Color != TablePart2->Chess_Color)
								{
									//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

									if (!LAll.Contains(TablePart2))
									{
										LAll.Add(TablePart2);
									}
								}
							}
						}
					}
				}
			}
		}

		//6
		for (auto It1 = LKing.CreateIterator(); It1; It1++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It1);
			if (TablePart)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
				{
					ATablePart* TablePart2 = Cast<ATablePart>(*It2);
					if (TablePart2)
					{
						if (!Enumy_Chess_All.Contains(TablePart2))
						{
							FVector2D NewLocation;
							NewLocation.X = TablePart->Table_Pos_Current.X;
							NewLocation.Y = TablePart->Table_Pos_Current.Y - 1.0f;

							if (TablePart2->Table_Pos_Current == NewLocation)
							{
								if (TablePart->Chess_Color != TablePart2->Chess_Color)
								{
									//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

									if (!LAll.Contains(TablePart2))
									{
										LAll.Add(TablePart2);
									}
								}
							}
						}
					}
				}
			}
		}

		//7
		for (auto It1 = LKing.CreateIterator(); It1; It1++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It1);
			if (TablePart)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
				{
					ATablePart* TablePart2 = Cast<ATablePart>(*It2);
					if (TablePart2)
					{
						if (!Enumy_Chess_All.Contains(TablePart2))
						{
							FVector2D NewLocation;
							NewLocation.X = TablePart->Table_Pos_Current.X - 1.0f;
							NewLocation.Y = TablePart->Table_Pos_Current.Y;

							if (TablePart2->Table_Pos_Current == NewLocation)
							{
								if (TablePart->Chess_Color != TablePart2->Chess_Color)
								{
									//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

									if (!LAll.Contains(TablePart2))
									{
										LAll.Add(TablePart2);
									}
								}
							}
						}
					}
				}
			}
		}

		//8
		for (auto It1 = LKing.CreateIterator(); It1; It1++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It1);
			if (TablePart)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
				{
					ATablePart* TablePart2 = Cast<ATablePart>(*It2);
					if (TablePart2)
					{
						if (!Enumy_Chess_All.Contains(TablePart2))
						{
							FVector2D NewLocation;
							NewLocation.X = TablePart->Table_Pos_Current.X;
							NewLocation.Y = TablePart->Table_Pos_Current.Y + 1.0f;

							if (TablePart2->Table_Pos_Current == NewLocation)
							{
								if (TablePart->Chess_Color != TablePart2->Chess_Color)
								{
									//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

									if (!LAll.Contains(TablePart2))
									{
										LAll.Add(TablePart2);
									}
								}
							}
						}
					}
				}
			}
		}

		    /*
			GLog->Log(FString::FromInt(LAll.Num()));
			for (auto a = LAll.CreateIterator(); a; a++)
			{
				ATablePart* b = Cast<ATablePart>(*a);
				if (b)
				{
					FName c = *b->GetName();
					FString e = c.ToString();
					GLog->Log(FString(c.ToString()));
				}
			}
			*/



		if (LAll.Num() == 0)
		{
			GM_Base->F_ChessKing_CheckMate(true);
			
		}

	}	

}


//--------------------------------------------------------------------------------
void ATablePart::F_Chess_Pat()
{
	//Get Game Mode
	AChessCPPGameModeBase* GM_Base;
	GM_Base = Cast<AChessCPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	//Local var
	TArray<ATablePart*> LPawn;
	TArray<ATablePart*> LKnight;
	TArray<ATablePart*> LBishop;
	TArray<ATablePart*> LRock;
	TArray<ATablePart*> LQueen;
	TArray<ATablePart*> LKing;
	TArray<ATablePart*> LAll;

	F_Chess_CheckPos(0);

	Enumy_Chess_Pawn.Empty();
	Enumy_Chess_Knight.Empty();
	Enumy_Chess_Bishop.Empty();
	Enumy_Chess_Rock.Empty();
	Enumy_Chess_Queen.Empty();
	Enumy_Chess_King.Empty();
	Enumy_Chess_All.Empty();

	TArray<AActor*> TablePartAll;
	TablePartAll.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
	for (auto It = TablePartAll.CreateIterator(); It; It++)
	{
		ATablePart* TablePart = Cast<ATablePart>(*It);
		if (TablePart)
		{
			if (TablePart->Chess_Color == GM_Base->CheyHod)
			{
				switch (TablePart->Chess_Name)
				{
				    case Note: {break; }
				    case Pawn:
				    {
					    LPawn.Add(TablePart);
					    break;
				    }
				    case Knight:
				    {
					    LKnight.Add(TablePart);
					    break;
				    }
				    case Bishop:
				    {
					    LBishop.Add(TablePart);
					    break;
				    }
				    case Rock:
				    {
					    LRock.Add(TablePart);
					    break;
				    }
				    case Queen:
				    {
					    LQueen.Add(TablePart);
					    break;
				    }
				    case King:
				    {
					    LKing.Add(TablePart);
					    break;
				    }
				}
			}
		}
	}

	F_ClearAllTable();
	
	//pawn

	switch (GM_Base->CheyHod)
	{
	    case None: {break; }

		case White: 
		{
			for (auto It = LPawn.CreateIterator(); It; It++)
			{
				ATablePart* TablePart = Cast<ATablePart>(*It);
				if (TablePart)
				{
					FVector2D NewLocation;
					NewLocation.X = TablePart->Table_Pos_Current.X - 1.0f;
					NewLocation.Y = TablePart->Table_Pos_Current.Y + 1.0f;

					TArray<AActor*> TablePartAll1;
					TablePartAll1.Empty();
					UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll1);
					for (auto It1 = TablePartAll1.CreateIterator(); It1; It1++)
					{
						ATablePart* TablePart1 = Cast<ATablePart>(*It1);
						if (TablePart1)
						{
							if (TablePart1->Table_Pos_Current == NewLocation && TablePart1->Chess_Name != Note && TablePart1->Chess_Color != GM_Base->CheyHod)
							{
								//TablePart1->StaticMesh->SetMaterial(0, Material_Black);

								if (!LAll.Contains(TablePart1))
								{
									LAll.Add(TablePart1);
								}
							}
						}
					}
				}
			}

			for (auto It = LPawn.CreateIterator(); It; It++)
			{
				ATablePart* TablePart = Cast<ATablePart>(*It);
				if (TablePart)
				{
					TArray<AActor*> TablePartAll1;
					TablePartAll1.Empty();
					UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll1);
					for (auto It1 = TablePartAll1.CreateIterator(); It1; It1++)
					{
						ATablePart* TablePart1 = Cast<ATablePart>(*It1);
						if (TablePart1)
						{
							FVector2D NewLocation;
							NewLocation.X = TablePart->Table_Pos_Current.X + 1.0f;
							NewLocation.Y = TablePart->Table_Pos_Current.Y + 1.0f;

							if (TablePart1->Table_Pos_Current == NewLocation && TablePart1->Chess_Name != Note && TablePart1->Chess_Color != GM_Base->CheyHod)
							{
								//TablePart1->StaticMesh->SetMaterial(0, Material_Black);

								if (!LAll.Contains(TablePart1))
								{
									LAll.Add(TablePart1);
								}
							}
						}
					}
				}
			}

			for (auto It = LPawn.CreateIterator(); It; It++)
			{
				ATablePart* TablePart = Cast<ATablePart>(*It);
				if (TablePart)
				{
					if (TablePart->Table_Pos_Current.Y != 2.0f)
					{
						TArray<AActor*> TablePartAll1;
						TablePartAll1.Empty();
						UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll1);
						for (auto It1 = TablePartAll1.CreateIterator(); It1; It1++)
						{
							ATablePart* TablePart1 = Cast<ATablePart>(*It1);
							if (TablePart1)
							{
								FVector2D NewLocation;
								NewLocation.X = TablePart->Table_Pos_Current.X;
								NewLocation.Y = TablePart->Table_Pos_Current.Y + 1.0f;

								if (TablePart1->Table_Pos_Current == NewLocation && TablePart1->Chess_Name == Note)
								{
									//TablePart1->StaticMesh->SetMaterial(0, Material_Blue);

									if (!LAll.Contains(TablePart1))
									{
										LAll.Add(TablePart1);
									}
								}
							}
						}		
					}
				}
			}

			for (auto It = LPawn.CreateIterator(); It; It++)
			{
				ATablePart* TablePart = Cast<ATablePart>(*It);
				if (TablePart)
				{
					if (TablePart->Table_Pos_Current.Y == 2.0f)
					{
						TArray<AActor*> TablePartAll1;
						TablePartAll1.Empty();
						UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll1);
						for (auto It1 = TablePartAll1.CreateIterator(); It1; It1++)
						{
							ATablePart* TablePart1 = Cast<ATablePart>(*It1);
							if (TablePart1)
							{
								FVector2D NewLocation;
								NewLocation.X = TablePart->Table_Pos_Current.X;
								NewLocation.Y = TablePart->Table_Pos_Current.Y + 1.0f;

								if (TablePart1->Table_Pos_Current == NewLocation && TablePart1->Chess_Name == Note)
								{
									//TablePart1->StaticMesh->SetMaterial(0, Material_Blue);

									if (!LAll.Contains(TablePart1))
									{
										LAll.Add(TablePart1);
									}

									if (TablePart->Table_Pos_Current.Y == 2.0f)
									{
										TArray<AActor*> TablePartAll2;
										TablePartAll2.Empty();
										UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
										for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
										{
											ATablePart* TablePart2 = Cast<ATablePart>(*It2);
											if (TablePart2)
											{
												FVector2D NewLocation2;
												NewLocation2.X = TablePart->Table_Pos_Current.X;
												NewLocation2.Y = TablePart->Table_Pos_Current.Y + 2.0f;

												if (TablePart2->Table_Pos_Current == NewLocation2 && TablePart2->Chess_Name == Note)
												{
													//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

													if (!LAll.Contains(TablePart2))
													{
														LAll.Add(TablePart2);
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}

			break;
		}


		case Black:
		{
			for (auto It = LPawn.CreateIterator(); It; It++)
			{
				ATablePart* TablePart = Cast<ATablePart>(*It);
				if (TablePart)
				{
					FVector2D NewLocation;
					NewLocation.X = TablePart->Table_Pos_Current.X - 1.0f;
					NewLocation.Y = TablePart->Table_Pos_Current.Y - 1.0f;

					TArray<AActor*> TablePartAll1;
					TablePartAll1.Empty();
					UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll1);
					for (auto It1 = TablePartAll1.CreateIterator(); It1; It1++)
					{
						ATablePart* TablePart1 = Cast<ATablePart>(*It1);
						if (TablePart1)
						{
							if (TablePart1->Table_Pos_Current == NewLocation && TablePart1->Chess_Name != Note && TablePart1->Chess_Color != GM_Base->CheyHod)
							{
								//TablePart1->StaticMesh->SetMaterial(0, Material_Black);

								if (!LAll.Contains(TablePart1))
								{
									LAll.Add(TablePart1);
								}
							}
						}
					}
				}
			}

			for (auto It = LPawn.CreateIterator(); It; It++)
			{
				ATablePart* TablePart = Cast<ATablePart>(*It);
				if (TablePart)
				{
					TArray<AActor*> TablePartAll1;
					TablePartAll1.Empty();
					UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll1);
					for (auto It1 = TablePartAll1.CreateIterator(); It1; It1++)
					{
						ATablePart* TablePart1 = Cast<ATablePart>(*It1);
						if (TablePart1)
						{
							FVector2D NewLocation;
							NewLocation.X = TablePart->Table_Pos_Current.X + 1.0f;
							NewLocation.Y = TablePart->Table_Pos_Current.Y - 1.0f;

							if (TablePart1->Table_Pos_Current == NewLocation && TablePart1->Chess_Name != Note && TablePart1->Chess_Color != GM_Base->CheyHod)
							{
								//TablePart1->StaticMesh->SetMaterial(0, Material_Black);

								if (!LAll.Contains(TablePart1))
								{
									LAll.Add(TablePart1);
								}
							}
						}
					}
				}
			}

			for (auto It = LPawn.CreateIterator(); It; It++)
			{
				ATablePart* TablePart = Cast<ATablePart>(*It);
				if (TablePart)
				{
					if (TablePart->Table_Pos_Current.Y != 7.0f)
					{
						TArray<AActor*> TablePartAll1;
						TablePartAll1.Empty();
						UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll1);
						for (auto It1 = TablePartAll1.CreateIterator(); It1; It1++)
						{
							ATablePart* TablePart1 = Cast<ATablePart>(*It1);
							if (TablePart1)
							{
								FVector2D NewLocation;
								NewLocation.X = TablePart->Table_Pos_Current.X;
								NewLocation.Y = TablePart->Table_Pos_Current.Y - 1.0f;

								if (TablePart1->Table_Pos_Current == NewLocation && TablePart1->Chess_Name == Note)
								{
									//TablePart1->StaticMesh->SetMaterial(0, Material_Blue);

									if (!LAll.Contains(TablePart1))
									{
										LAll.Add(TablePart1);
									}
								}
							}
						}
					}
				}
			}

			for (auto It = LPawn.CreateIterator(); It; It++)
			{
				ATablePart* TablePart = Cast<ATablePart>(*It);
				if (TablePart)
				{
					if (TablePart->Table_Pos_Current.Y == 7.0f)
					{
						TArray<AActor*> TablePartAll1;
						TablePartAll1.Empty();
						UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll1);
						for (auto It1 = TablePartAll1.CreateIterator(); It1; It1++)
						{
							ATablePart* TablePart1 = Cast<ATablePart>(*It1);
							if (TablePart1)
							{
								FVector2D NewLocation;
								NewLocation.X = TablePart->Table_Pos_Current.X;
								NewLocation.Y = TablePart->Table_Pos_Current.Y - 1.0f;

								if (TablePart1->Table_Pos_Current == NewLocation && TablePart1->Chess_Name == Note)
								{
									//TablePart1->StaticMesh->SetMaterial(0, Material_Blue);

									if (!LAll.Contains(TablePart1))
									{
										LAll.Add(TablePart1);
									}

									if (TablePart->Table_Pos_Current.Y == 7.0f)
									{
										TArray<AActor*> TablePartAll2;
										TablePartAll2.Empty();
										UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
										for (auto It2 = TablePartAll2.CreateIterator(); It2; It2++)
										{
											ATablePart* TablePart2 = Cast<ATablePart>(*It2);
											if (TablePart2)
											{
												FVector2D NewLocation2;
												NewLocation2.X = TablePart->Table_Pos_Current.X;
												NewLocation2.Y = TablePart->Table_Pos_Current.Y - 2.0f;

												if (TablePart2->Table_Pos_Current == NewLocation2 && TablePart2->Chess_Name == Note)
												{
													//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

													if (!LAll.Contains(TablePart2))
													{
														LAll.Add(TablePart2);
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}

			break;
		}
	}

	//--------------
	//knight
	//1
	for (auto It1 = LKnight.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart1 = Cast<ATablePart>(*It1);
		if (TablePart1)
		{
			TArray<AActor*> TablePartAll11;
			TablePartAll.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll11);
			for (auto It11 = TablePartAll11.CreateIterator(); It11; It11++)
			{
				ATablePart* TablePart11 = Cast<ATablePart>(*It11);
				if (TablePart11)
				{
					FVector2D NewLocation1;
					NewLocation1.X = TablePart1->Table_Pos_Current.X - 1.0f;
					NewLocation1.Y = TablePart1->Table_Pos_Current.Y + 2.0f;

					if (TablePart11->Table_Pos_Current == NewLocation1 && TablePart11->Chess_Color != TablePart1->Chess_Color)
					{
						//TablePart11->StaticMesh->SetMaterial(0, Material_Blue);

						if (!LAll.Contains(TablePart11))
						{
							LAll.Add(TablePart11);
						}

					}
				}
			}
		}
	}

	//2
	for (auto It1 = LKnight.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart1 = Cast<ATablePart>(*It1);
		if (TablePart1)
		{
			TArray<AActor*> TablePartAll11;
			TablePartAll.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll11);
			for (auto It11 = TablePartAll11.CreateIterator(); It11; It11++)
			{
				ATablePart* TablePart11 = Cast<ATablePart>(*It11);
				if (TablePart11)
				{
					FVector2D NewLocation1;
					NewLocation1.X = TablePart1->Table_Pos_Current.X + 1.0f;
					NewLocation1.Y = TablePart1->Table_Pos_Current.Y + 2.0f;

					if (TablePart11->Table_Pos_Current == NewLocation1 && TablePart11->Chess_Color != TablePart1->Chess_Color)
					{
						//TablePart11->StaticMesh->SetMaterial(0, Material_Blue);

						if (!LAll.Contains(TablePart11))
						{
							LAll.Add(TablePart11);
						}

					}
				}
			}
		}
	}

	//3
	for (auto It1 = LKnight.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart1 = Cast<ATablePart>(*It1);
		if (TablePart1)
		{
			TArray<AActor*> TablePartAll11;
			TablePartAll.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll11);
			for (auto It11 = TablePartAll11.CreateIterator(); It11; It11++)
			{
				ATablePart* TablePart11 = Cast<ATablePart>(*It11);
				if (TablePart11)
				{
					FVector2D NewLocation1;
					NewLocation1.X = TablePart1->Table_Pos_Current.X + 2.0f;
					NewLocation1.Y = TablePart1->Table_Pos_Current.Y + 1.0f;

					if (TablePart11->Table_Pos_Current == NewLocation1 && TablePart11->Chess_Color != TablePart1->Chess_Color)
					{
						//TablePart11->StaticMesh->SetMaterial(0, Material_Blue);

						if (!LAll.Contains(TablePart11))
						{
							LAll.Add(TablePart11);
						}

					}
				}
			}
		}
	}

	//4
	for (auto It1 = LKnight.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart1 = Cast<ATablePart>(*It1);
		if (TablePart1)
		{
			TArray<AActor*> TablePartAll11;
			TablePartAll.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll11);
			for (auto It11 = TablePartAll11.CreateIterator(); It11; It11++)
			{
				ATablePart* TablePart11 = Cast<ATablePart>(*It11);
				if (TablePart11)
				{
					FVector2D NewLocation1;
					NewLocation1.X = TablePart1->Table_Pos_Current.X + 2.0f;
					NewLocation1.Y = TablePart1->Table_Pos_Current.Y - 1.0f;

					if (TablePart11->Table_Pos_Current == NewLocation1 && TablePart11->Chess_Color != TablePart1->Chess_Color)
					{
						//TablePart11->StaticMesh->SetMaterial(0, Material_Blue);

						if (!LAll.Contains(TablePart11))
						{
							LAll.Add(TablePart11);
						}

					}
				}
			}
		}
	}

	//5
	for (auto It1 = LKnight.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart1 = Cast<ATablePart>(*It1);
		if (TablePart1)
		{
			TArray<AActor*> TablePartAll11;
			TablePartAll.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll11);
			for (auto It11 = TablePartAll11.CreateIterator(); It11; It11++)
			{
				ATablePart* TablePart11 = Cast<ATablePart>(*It11);
				if (TablePart11)
				{
					FVector2D NewLocation1;
					NewLocation1.X = TablePart1->Table_Pos_Current.X + 1.0f;
					NewLocation1.Y = TablePart1->Table_Pos_Current.Y - 2.0f;

					if (TablePart11->Table_Pos_Current == NewLocation1 && TablePart11->Chess_Color != TablePart1->Chess_Color)
					{
						//TablePart11->StaticMesh->SetMaterial(0, Material_Blue);

						if (!LAll.Contains(TablePart11))
						{
							LAll.Add(TablePart11);
						}

					}
				}
			}
		}
	}

	//6
	for (auto It1 = LKnight.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart1 = Cast<ATablePart>(*It1);
		if (TablePart1)
		{
			TArray<AActor*> TablePartAll11;
			TablePartAll.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll11);
			for (auto It11 = TablePartAll11.CreateIterator(); It11; It11++)
			{
				ATablePart* TablePart11 = Cast<ATablePart>(*It11);
				if (TablePart11)
				{
					FVector2D NewLocation1;
					NewLocation1.X = TablePart1->Table_Pos_Current.X - 1.0f;
					NewLocation1.Y = TablePart1->Table_Pos_Current.Y - 2.0f;

					if (TablePart11->Table_Pos_Current == NewLocation1 && TablePart11->Chess_Color != TablePart1->Chess_Color)
					{
						//TablePart11->StaticMesh->SetMaterial(0, Material_Blue);

						if (!LAll.Contains(TablePart11))
						{
							LAll.Add(TablePart11);
						}
					}
				}
			}
		}
	}

	//7
	for (auto It1 = LKnight.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart1 = Cast<ATablePart>(*It1);
		if (TablePart1)
		{
			TArray<AActor*> TablePartAll11;
			TablePartAll.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll11);
			for (auto It11 = TablePartAll11.CreateIterator(); It11; It11++)
			{
				ATablePart* TablePart11 = Cast<ATablePart>(*It11);
				if (TablePart11)
				{
					FVector2D NewLocation1;
					NewLocation1.X = TablePart1->Table_Pos_Current.X - 2.0f;
					NewLocation1.Y = TablePart1->Table_Pos_Current.Y + 1.0f;

					if (TablePart11->Table_Pos_Current == NewLocation1 && TablePart11->Chess_Color != TablePart1->Chess_Color)
					{
						//TablePart11->StaticMesh->SetMaterial(0, Material_Blue);

						if (!LAll.Contains(TablePart11))
						{
							LAll.Add(TablePart11);
						}
					}
				}
			}
		}
	}

	//8
	for (auto It1 = LKnight.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart1 = Cast<ATablePart>(*It1);
		if (TablePart1)
		{
			TArray<AActor*> TablePartAll11;
			TablePartAll.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll11);
			for (auto It11 = TablePartAll11.CreateIterator(); It11; It11++)
			{
				ATablePart* TablePart11 = Cast<ATablePart>(*It11);
				if (TablePart11)
				{
					FVector2D NewLocation1;
					NewLocation1.X = TablePart1->Table_Pos_Current.X - 2.0f;
					NewLocation1.Y = TablePart1->Table_Pos_Current.Y - 1.0f;

					if (TablePart11->Table_Pos_Current == NewLocation1 && TablePart11->Chess_Color != TablePart1->Chess_Color)
					{
						//TablePart11->StaticMesh->SetMaterial(0, Material_Blue);

						if (!LAll.Contains(TablePart11))
						{
							LAll.Add(TablePart11);
						}
					}
				}
			}
		}
	}

	//--------------
	//bishop
	//1
	for (auto It1 = LBishop.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart1 = Cast<ATablePart>(*It1);
		if (TablePart1)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart1->Table_Pos_Current.X + 1.0f;
			NewLocation.Y = TablePart1->Table_Pos_Current.Y + 1.0f;

			for (int32 It2 = 0; It2 <= 7; It2++)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
				{
					ATablePart* TablePart2 = Cast<ATablePart>(*It3);
					if (TablePart2)
					{
						if (TablePart2->Table_Pos_Current == NewLocation)
						{
							if (TablePart2->Chess_Color != TablePart1->Chess_Color)
							{
								//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

								NewLocation.X = NewLocation.X + 1.0f;
								NewLocation.Y = NewLocation.Y + 1.0f;

								if (!LAll.Contains(TablePart2))
								{
									LAll.Add(TablePart2);
								}
							}
							else { /*break;*/ }
						}
					}
				}
				//break;
			}
			//break;
		}
	}

	//2
	for (auto It1 = LBishop.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart1 = Cast<ATablePart>(*It1);
		if (TablePart1)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart1->Table_Pos_Current.X + 1.0f;
			NewLocation.Y = TablePart1->Table_Pos_Current.Y - 1.0f;

			for (int32 It2 = 0; It2 <= 7; It2++)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
				{
					ATablePart* TablePart2 = Cast<ATablePart>(*It3);
					if (TablePart2)
					{
						if (TablePart2->Table_Pos_Current == NewLocation)
						{
							if (TablePart2->Chess_Color != TablePart1->Chess_Color)
							{
								//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

								NewLocation.X = NewLocation.X + 1.0f;
								NewLocation.Y = NewLocation.Y - 1.0f;

								if (!LAll.Contains(TablePart2))
								{
									LAll.Add(TablePart2);
								}
							}
							else { /*break;*/ }
						}
					}
				}
				//break;
			}
			//break;
		}
	}

	//3
	for (auto It1 = LBishop.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart1 = Cast<ATablePart>(*It1);
		if (TablePart1)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart1->Table_Pos_Current.X - 1.0f;
			NewLocation.Y = TablePart1->Table_Pos_Current.Y + 1.0f;

			for (int32 It2 = 0; It2 <= 7; It2++)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
				{
					ATablePart* TablePart2 = Cast<ATablePart>(*It3);
					if (TablePart2)
					{
						if (TablePart2->Table_Pos_Current == NewLocation)
						{
							if (TablePart2->Chess_Color != TablePart1->Chess_Color)
							{
								//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

								NewLocation.X = NewLocation.X - 1.0f;
								NewLocation.Y = NewLocation.Y + 1.0f;

								if (!LAll.Contains(TablePart2))
								{
									LAll.Add(TablePart2);
								}
							}
							else { /*break;*/ }
						}
					}
				}
				//break;
			}
			//break;
		}
	}

	//4
	for (auto It1 = LBishop.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart1 = Cast<ATablePart>(*It1);
		if (TablePart1)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart1->Table_Pos_Current.X - 1.0f;
			NewLocation.Y = TablePart1->Table_Pos_Current.Y - 1.0f;

			for (int32 It2 = 0; It2 <= 7; It2++)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
				{
					ATablePart* TablePart2 = Cast<ATablePart>(*It3);
					if (TablePart2)
					{
						if (TablePart2->Table_Pos_Current == NewLocation)
						{
							if (TablePart2->Chess_Color != TablePart1->Chess_Color)
							{
								//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

								NewLocation.X = NewLocation.X - 1.0f;
								NewLocation.Y = NewLocation.Y - 1.0f;

								if (!LAll.Contains(TablePart2))
								{
									LAll.Add(TablePart2);
								}
							}
							else { /*break;*/ }
						}
					}
				}
				//break;
			}
			//break;
		}
	}

	//--------------
	//rock
	//1
	for (auto It1 = LRock.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart1 = Cast<ATablePart>(*It1);
		if (TablePart1)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart1->Table_Pos_Current.X + 1.0f;
			NewLocation.Y = TablePart1->Table_Pos_Current.Y;

			for (int32 It2 = 0; It2 <= 7; It2++)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
				{
					ATablePart* TablePart2 = Cast<ATablePart>(*It3);
					if (TablePart2)
					{
						if (TablePart2->Table_Pos_Current == NewLocation)
						{
							if (TablePart2->Chess_Color != TablePart1->Chess_Color)
							{
								//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

								NewLocation.X = NewLocation.X + 1.0f;
								NewLocation.Y = NewLocation.Y;

								if (!LAll.Contains(TablePart2))
								{
									LAll.Add(TablePart2);
								}
							}
							else { /*break;*/ }
						}
					}
				}
				//break;
			}
			//break;
		}
	}

	//2
	for (auto It1 = LRock.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart1 = Cast<ATablePart>(*It1);
		if (TablePart1)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart1->Table_Pos_Current.X;
			NewLocation.Y = TablePart1->Table_Pos_Current.Y - 1.0f;

			for (int32 It2 = 0; It2 <= 7; It2++)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
				{
					ATablePart* TablePart2 = Cast<ATablePart>(*It3);
					if (TablePart2)
					{
						if (TablePart2->Table_Pos_Current == NewLocation)
						{
							if (TablePart2->Chess_Color != TablePart1->Chess_Color)
							{
								//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

								NewLocation.X = NewLocation.X;
								NewLocation.Y = NewLocation.Y - 1.0f;

								if (!LAll.Contains(TablePart2))
								{
									LAll.Add(TablePart2);
								}
							}
							else { /*break;*/ }
						}
					}
				}
				//break;
			}
			//break;
		}
	}

	//3
	for (auto It1 = LRock.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart1 = Cast<ATablePart>(*It1);
		if (TablePart1)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart1->Table_Pos_Current.X - 1.0f;
			NewLocation.Y = TablePart1->Table_Pos_Current.Y;

			for (int32 It2 = 0; It2 <= 7; It2++)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
				{
					ATablePart* TablePart2 = Cast<ATablePart>(*It3);
					if (TablePart2)
					{
						if (TablePart2->Table_Pos_Current == NewLocation)
						{
							if (TablePart2->Chess_Color != TablePart1->Chess_Color)
							{
								//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

								NewLocation.X = NewLocation.X - 1.0f;
								NewLocation.Y = NewLocation.Y;

								if (!LAll.Contains(TablePart2))
								{
									LAll.Add(TablePart2);
								}
							}
							else { /*break;*/ }
						}
					}
				}
				//break;
			}
			//break;
		}
	}

	//4
	for (auto It1 = LRock.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart1 = Cast<ATablePart>(*It1);
		if (TablePart1)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart1->Table_Pos_Current.X;
			NewLocation.Y = TablePart1->Table_Pos_Current.Y + 1.0f;

			for (int32 It2 = 0; It2 <= 7; It2++)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
				{
					ATablePart* TablePart2 = Cast<ATablePart>(*It3);
					if (TablePart2)
					{
						if (TablePart2->Table_Pos_Current == NewLocation)
						{
							if (TablePart2->Chess_Color != TablePart1->Chess_Color)
							{
								//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

								NewLocation.X = NewLocation.X;
								NewLocation.Y = NewLocation.Y + 1.0f;

								if (!LAll.Contains(TablePart2))
								{
									LAll.Add(TablePart2);
								}
							}
							else { /*break;*/ }
						}
					}
				}
				//break;
			}
			//break;
		}
	}

	//-----------------
	//queen
	//1
	for (auto It1 = LQueen.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart1 = Cast<ATablePart>(*It1);
		if (TablePart1)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart1->Table_Pos_Current.X + 1.0f;
			NewLocation.Y = TablePart1->Table_Pos_Current.Y + 1.0f;

			for (int32 It2 = 0; It2 <= 7; It2++)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
				{
					ATablePart* TablePart2 = Cast<ATablePart>(*It3);
					if (TablePart2)
					{
						if (TablePart2->Table_Pos_Current == NewLocation)
						{
							if (TablePart2->Chess_Color != TablePart1->Chess_Color)
							{
								//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

								NewLocation.X = NewLocation.X + 1.0f;
								NewLocation.Y = NewLocation.Y + 1.0f;

								if (!LAll.Contains(TablePart2))
								{
									LAll.Add(TablePart2);
								}
							}
							else { /*break;*/ }
						}
					}
				}
				//break;
			}
			//break;
		}
	}

	//2
	for (auto It1 = LQueen.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart1 = Cast<ATablePart>(*It1);
		if (TablePart1)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart1->Table_Pos_Current.X + 1.0f;
			NewLocation.Y = TablePart1->Table_Pos_Current.Y - 1.0f;

			for (int32 It2 = 0; It2 <= 7; It2++)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
				{
					ATablePart* TablePart2 = Cast<ATablePart>(*It3);
					if (TablePart2)
					{
						if (TablePart2->Table_Pos_Current == NewLocation)
						{
							if (TablePart2->Chess_Color != TablePart1->Chess_Color)
							{
								//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

								NewLocation.X = NewLocation.X + 1.0f;
								NewLocation.Y = NewLocation.Y - 1.0f;

								if (!LAll.Contains(TablePart2))
								{
									LAll.Add(TablePart2);
								}
							}
							else { /*break;*/ }
						}
					}
				}
				//break;
			}
			//break;
		}
	}

	//3
	for (auto It1 = LQueen.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart1 = Cast<ATablePart>(*It1);
		if (TablePart1)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart1->Table_Pos_Current.X - 1.0f;
			NewLocation.Y = TablePart1->Table_Pos_Current.Y + 1.0f;

			for (int32 It2 = 0; It2 <= 7; It2++)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
				{
					ATablePart* TablePart2 = Cast<ATablePart>(*It3);
					if (TablePart2)
					{
						if (TablePart2->Table_Pos_Current == NewLocation)
						{
							if (TablePart2->Chess_Color != TablePart1->Chess_Color)
							{
								//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

								NewLocation.X = NewLocation.X - 1.0f;
								NewLocation.Y = NewLocation.Y + 1.0f;

								if (!LAll.Contains(TablePart2))
								{
									LAll.Add(TablePart2);
								}
							}
							else { /*break;*/ }
						}
					}
				}
				//break;
			}
			//break;
		}
	}

	//4
	for (auto It1 = LQueen.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart1 = Cast<ATablePart>(*It1);
		if (TablePart1)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart1->Table_Pos_Current.X - 1.0f;
			NewLocation.Y = TablePart1->Table_Pos_Current.Y - 1.0f;

			for (int32 It2 = 0; It2 <= 7; It2++)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
				{
					ATablePart* TablePart2 = Cast<ATablePart>(*It3);
					if (TablePart2)
					{
						if (TablePart2->Table_Pos_Current == NewLocation)
						{
							if (TablePart2->Chess_Color != TablePart1->Chess_Color)
							{
								//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

								NewLocation.X = NewLocation.X - 1.0f;
								NewLocation.Y = NewLocation.Y - 1.0f;

								if (!LAll.Contains(TablePart2))
								{
									LAll.Add(TablePart2);
								}
							}
							else { /*break;*/ }
						}
					}
				}
				//break;
			}
			//break;
		}
	}

	//5
	for (auto It1 = LQueen.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart1 = Cast<ATablePart>(*It1);
		if (TablePart1)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart1->Table_Pos_Current.X + 1.0f;
			NewLocation.Y = TablePart1->Table_Pos_Current.Y;

			for (int32 It2 = 0; It2 <= 7; It2++)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
				{
					ATablePart* TablePart2 = Cast<ATablePart>(*It3);
					if (TablePart2)
					{
						if (TablePart2->Table_Pos_Current == NewLocation)
						{
							if (TablePart2->Chess_Color != TablePart1->Chess_Color)
							{
								//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

								NewLocation.X = NewLocation.X + 1.0f;
								NewLocation.Y = NewLocation.Y;

								if (!LAll.Contains(TablePart2))
								{
									LAll.Add(TablePart2);
								}
							}
							else { /*break;*/ }
						}
					}
				}
				//break;
			}
			//break;
		}
	}

	//6
	for (auto It1 = LQueen.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart1 = Cast<ATablePart>(*It1);
		if (TablePart1)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart1->Table_Pos_Current.X;
			NewLocation.Y = TablePart1->Table_Pos_Current.Y - 1.0f;

			for (int32 It2 = 0; It2 <= 7; It2++)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
				{
					ATablePart* TablePart2 = Cast<ATablePart>(*It3);
					if (TablePart2)
					{
						if (TablePart2->Table_Pos_Current == NewLocation)
						{
							if (TablePart2->Chess_Color != TablePart1->Chess_Color)
							{
								//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

								NewLocation.X = NewLocation.X;
								NewLocation.Y = NewLocation.Y - 1.0f;

								if (!LAll.Contains(TablePart2))
								{
									LAll.Add(TablePart2);
								}
							}
							else { /*break;*/ }
						}
					}
				}
				//break;
			}
			//break;
		}
	}

	//7
	for (auto It1 = LQueen.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart1 = Cast<ATablePart>(*It1);
		if (TablePart1)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart1->Table_Pos_Current.X - 1.0f;
			NewLocation.Y = TablePart1->Table_Pos_Current.Y;

			for (int32 It2 = 0; It2 <= 7; It2++)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
				{
					ATablePart* TablePart2 = Cast<ATablePart>(*It3);
					if (TablePart2)
					{
						if (TablePart2->Table_Pos_Current == NewLocation)
						{
							if (TablePart2->Chess_Color != TablePart1->Chess_Color)
							{
								//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

								NewLocation.X = NewLocation.X - 1.0f;
								NewLocation.Y = NewLocation.Y;

								if (!LAll.Contains(TablePart2))
								{
									LAll.Add(TablePart2);
								}
							}
							else { /*break;*/ }
						}
					}
				}
				//break;
			}
			//break;
		}
	}

	//8
	for (auto It1 = LQueen.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart1 = Cast<ATablePart>(*It1);
		if (TablePart1)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart1->Table_Pos_Current.X;
			NewLocation.Y = TablePart1->Table_Pos_Current.Y + 1.0f;

			for (int32 It2 = 0; It2 <= 7; It2++)
			{
				TArray<AActor*> TablePartAll2;
				TablePartAll2.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
				for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
				{
					ATablePart* TablePart2 = Cast<ATablePart>(*It3);
					if (TablePart2)
					{
						if (TablePart2->Table_Pos_Current == NewLocation)
						{
							if (TablePart2->Chess_Color != TablePart1->Chess_Color)
							{
								//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

								NewLocation.X = NewLocation.X;
								NewLocation.Y = NewLocation.Y + 1.0f;

								if (!LAll.Contains(TablePart2))
								{
									LAll.Add(TablePart2);
								}
							}
							else { /*break;*/ }
						}
					}
				}
				//break;
			}
			//break;
		}
	}

	//---------------
	//king
    //1
	for (auto It1 = LKing.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart1 = Cast<ATablePart>(*It1);
		if (TablePart1)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart1->Table_Pos_Current.X + 1.0f;
			NewLocation.Y = TablePart1->Table_Pos_Current.Y + 1.0f;

			TArray<AActor*> TablePartAll2;
			TablePartAll2.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
			for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
			{
				ATablePart* TablePart2 = Cast<ATablePart>(*It3);
				if (TablePart2)
				{
					if (TablePart2->Table_Pos_Current == NewLocation)
					{
						if (TablePart2->Chess_Color != TablePart1->Chess_Color)
						{
							//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

							if (!LAll.Contains(TablePart2))
							{
								LAll.Add(TablePart2);
							}
						}
						else { /*break;*/ }
					}
				}
			}
			//break;
		}
	}

	//2
	for (auto It1 = LKing.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart1 = Cast<ATablePart>(*It1);
		if (TablePart1)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart1->Table_Pos_Current.X + 1.0f;
			NewLocation.Y = TablePart1->Table_Pos_Current.Y - 1.0f;

			TArray<AActor*> TablePartAll2;
			TablePartAll2.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
			for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
			{
				ATablePart* TablePart2 = Cast<ATablePart>(*It3);
				if (TablePart2)
				{
					if (TablePart2->Table_Pos_Current == NewLocation)
					{
						if (TablePart2->Chess_Color != TablePart1->Chess_Color)
						{
							//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

							if (!LAll.Contains(TablePart2))
							{
								LAll.Add(TablePart2);
							}
						}
						else { /*break;*/ }
					}
				}
			}
			//break;
		}
	}

	//3
	for (auto It1 = LKing.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart1 = Cast<ATablePart>(*It1);
		if (TablePart1)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart1->Table_Pos_Current.X - 1.0f;
			NewLocation.Y = TablePart1->Table_Pos_Current.Y + 1.0f;

			TArray<AActor*> TablePartAll2;
			TablePartAll2.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
			for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
			{
				ATablePart* TablePart2 = Cast<ATablePart>(*It3);
				if (TablePart2)
				{
					if (TablePart2->Table_Pos_Current == NewLocation)
					{
						if (TablePart2->Chess_Color != TablePart1->Chess_Color)
						{
							//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

							if (!LAll.Contains(TablePart2))
							{
								LAll.Add(TablePart2);
							}
						}
						else { /*break;*/ }
					}
				}
			}
			//break;
		}
	}

	//4
	for (auto It1 = LKing.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart1 = Cast<ATablePart>(*It1);
		if (TablePart1)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart1->Table_Pos_Current.X - 1.0f;
			NewLocation.Y = TablePart1->Table_Pos_Current.Y - 1.0f;

			TArray<AActor*> TablePartAll2;
			TablePartAll2.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
			for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
			{
				ATablePart* TablePart2 = Cast<ATablePart>(*It3);
				if (TablePart2)
				{
					if (TablePart2->Table_Pos_Current == NewLocation)
					{
						if (TablePart2->Chess_Color != TablePart1->Chess_Color)
						{
							//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

							if (!LAll.Contains(TablePart2))
							{
								LAll.Add(TablePart2);
							}
						}
						else { /*break;*/ }
					}
				}
			}
			//break;
		}
	}

	//5
	for (auto It1 = LKing.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart1 = Cast<ATablePart>(*It1);
		if (TablePart1)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart1->Table_Pos_Current.X + 1.0f;
			NewLocation.Y = TablePart1->Table_Pos_Current.Y;

			TArray<AActor*> TablePartAll2;
			TablePartAll2.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
			for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
			{
				ATablePart* TablePart2 = Cast<ATablePart>(*It3);
				if (TablePart2)
				{
					if (TablePart2->Table_Pos_Current == NewLocation)
					{
						if (TablePart2->Chess_Color != TablePart1->Chess_Color)
						{
							//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

							if (!LAll.Contains(TablePart2))
							{
								LAll.Add(TablePart2);
							}
						}
						else { /*break;*/ }
					}
				}
			}
			//break;
		}
	}

	//6
	for (auto It1 = LKing.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart1 = Cast<ATablePart>(*It1);
		if (TablePart1)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart1->Table_Pos_Current.X;
			NewLocation.Y = TablePart1->Table_Pos_Current.Y - 1.0f;

			TArray<AActor*> TablePartAll2;
			TablePartAll2.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
			for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
			{
				ATablePart* TablePart2 = Cast<ATablePart>(*It3);
				if (TablePart2)
				{
					if (TablePart2->Table_Pos_Current == NewLocation)
					{
						if (TablePart2->Chess_Color != TablePart1->Chess_Color)
						{
							//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

							if (!LAll.Contains(TablePart2))
							{
								LAll.Add(TablePart2);
							}
						}
						else { /*break;*/ }
					}
				}
			}
			//break;
		}
	}

	//7
	for (auto It1 = LKing.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart1 = Cast<ATablePart>(*It1);
		if (TablePart1)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart1->Table_Pos_Current.X - 1.0f;
			NewLocation.Y = TablePart1->Table_Pos_Current.Y;

			TArray<AActor*> TablePartAll2;
			TablePartAll2.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
			for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
			{
				ATablePart* TablePart2 = Cast<ATablePart>(*It3);
				if (TablePart2)
				{
					if (TablePart2->Table_Pos_Current == NewLocation)
					{
						if (TablePart2->Chess_Color != TablePart1->Chess_Color)
						{
							//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

							if (!LAll.Contains(TablePart2))
							{
								LAll.Add(TablePart2);
							}
						}
						else { /*break;*/ }
					}
				}
			}
			//break;
		}
	}

	//8
	for (auto It1 = LKing.CreateIterator(); It1; It1++)
	{
		ATablePart* TablePart1 = Cast<ATablePart>(*It1);
		if (TablePart1)
		{
			FVector2D NewLocation;
			NewLocation.X = TablePart1->Table_Pos_Current.X;
			NewLocation.Y = TablePart1->Table_Pos_Current.Y + 1.0f;

			TArray<AActor*> TablePartAll2;
			TablePartAll2.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll2);
			for (auto It3 = TablePartAll2.CreateIterator(); It3; It3++)
			{
				ATablePart* TablePart2 = Cast<ATablePart>(*It3);
				if (TablePart2)
				{
					if (TablePart2->Table_Pos_Current == NewLocation)
					{
						if (TablePart2->Chess_Color != TablePart1->Chess_Color)
						{
							//TablePart2->StaticMesh->SetMaterial(0, Material_Blue);

							if (!LAll.Contains(TablePart2))
							{
								LAll.Add(TablePart2);
							}
						}
						else { /*break;*/ }
					}
				}
			}
			//break;
		}
	}


	//--------
	if (LAll.Num() == 0)
	{
		//GM_Base->ChessKing_Pat = true;
		GM_Base->F_ChessKing_Pat(true);
	}
}

//--------------------------------------------------------------------------------
void ATablePart::F_Chess_Casting_Painting()
{
	//Get Game Mode
	AChessCPPGameModeBase* GM_Base;
	GM_Base = Cast<AChessCPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (!GM_Base->ChessKing_Check)
	{
		switch (GM_Base->CheyHod)
		{
		    //case Note: {break; }
			case White:
			{
				if (!GM_Base->IsCanCasting_White)
				{
					F_Chess_Casting_Painting1();
				}
				break;
			}
			case Black:
			{
				if (!GM_Base->IsCanCasting_Black)
				{
					F_Chess_Casting_Painting1();
				}
				break;
			}
		}
	}
}

void ATablePart::F_Chess_Casting_Painting1()
{

	//Get Game Mode
	AChessCPPGameModeBase* GM_Base;
	GM_Base = Cast<AChessCPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	//local var
	FVector2D LPoss = FVector2D(0.f, 0.f);;
	bool LCanCasting = false;
	int32 LCountCasting = 0;

	F_Chess_CheckPos(0);


	LPoss.X = Table_Pos_Current.X + 1.0f;
	LPoss.Y = Table_Pos_Current.Y;

	LCountCasting = 0;

	for (int32 i = 0; i <= 1; i++)
	{
		TArray<AActor*> TablePartAll;
		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == LPoss && !Enumy_Chess_All.Contains(TablePart) && TablePart->Chess_Name == Note)
				{
					//TablePart->StaticMesh->SetMaterial(0, Material_Blue);

					LPoss.X = LPoss.X + 1.0f;
					LPoss.Y = LPoss.Y;

					LCountCasting = LCountCasting + 1;
				}
			}
		}
	}

	if (LCountCasting >= 2)
	{
		LPoss.X = Table_Pos_Current.X + 3.0f;
		LPoss.Y = Table_Pos_Current.Y;
		
		TArray<AActor*> TablePartAll;
		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{ 
				if (TablePart->Table_Pos_Current == LPoss && TablePart->Chess_Name == Rock && TablePart->Chess_Color == GM_Base->CheyHod)
				{
					TablePart->StaticMesh->SetMaterial(0, Material_Green);

					LCanCasting = true;
				}
			}
		}
	}

	LPoss.X = Table_Pos_Current.X - 1.0f;
	LPoss.Y = Table_Pos_Current.Y;

	LCountCasting = 0;

	for (int32 i = 0; i <= 2; i++)
	{
		TArray<AActor*> TablePartAll;
		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == LPoss && !Enumy_Chess_All.Contains(TablePart) && TablePart->Chess_Name == Note)
				{
					//TablePart->StaticMesh->SetMaterial(0, Material_Blue);

					LPoss.X = LPoss.X - 1.0f;
					LPoss.Y = LPoss.Y;

					LCountCasting = LCountCasting + 1;
				}
			}
		}
	}

	if (LCountCasting >= 2)
	{
		LPoss.X = Table_Pos_Current.X - 4.0f;
		LPoss.Y = Table_Pos_Current.Y;

		TArray<AActor*> TablePartAll;
		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == LPoss && TablePart->Chess_Name == Rock && TablePart->Chess_Color == GM_Base->CheyHod)
				{
					TablePart->StaticMesh->SetMaterial(0, Material_Green);

					LCanCasting = true;
				}
			}
		}
	}

}

//--------------------------------------------------------------------------------
bool ATablePart::F_Chess_Casting_Move()
{
	//Get Game Mode
	AChessCPPGameModeBase* GM_Base;
	GM_Base = Cast<AChessCPPGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	//Local var
	FVector2D LPoss = FVector2D(0.f, 0.f);
	ATablePart* LPossKing = nullptr;
	ATablePart* LPossRock = nullptr;
	TEnumAsByte <enum_ChessName> LCurrentName = Note;
	FString LCurrentNames;
	FString LNextNames;



	LCurrentName = GM_Base->Chess_Current->Chess_Name;

	if (GM_Base->Chess_Current->Table_Pos_Current.X < Table_Pos_Current.X)
	{
		LPoss.X = GM_Base->Chess_Current->Table_Pos_Current.X + 2.0f;
		LPoss.Y = GM_Base->Chess_Current->Table_Pos_Current.Y;

		TArray<AActor*> TablePartAll;
		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == LPoss)
				{
					TablePart->Chess_Name = GM_Base->Chess_Current->Chess_Name;
					TablePart->Chess_Color = GM_Base->Chess_Current->Chess_Color;
					LPossKing = TablePart;
				}
			}
		}

		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == GM_Base->Chess_Current->Table_Pos_Current)
				{
					TablePart->Chess_Name = Note;
					TablePart->Chess_Color = None;

					break;
				}
			}
		}

		TArray<AActor*> BaseChessAll;
		BaseChessAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AbaseChess::StaticClass(), BaseChessAll);
		for (auto It = BaseChessAll.CreateIterator(); It; It++)
		{
			AbaseChess* BaseChess = Cast<AbaseChess>(*It);
			if (BaseChess)
			{
				if (BaseChess->GetActorLocation().X == GM_Base->Chess_Current->GetActorLocation().X && BaseChess->GetActorLocation().Y == GM_Base->Chess_Current->GetActorLocation().Y)
				{
					FVector NewLocation;
					NewLocation.X = LPossKing->GetActorLocation().X;
					NewLocation.Y = LPossKing->GetActorLocation().Y;
					NewLocation.Z = BaseChess->GetActorLocation().Z;

					BaseChess->SetActorLocation(NewLocation);

					break;
				}	
			}
		}

		LPoss.X = GM_Base->Chess_Next->Table_Pos_Current.X - 2.0f;
		LPoss.Y = GM_Base->Chess_Next->Table_Pos_Current.Y;

		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == LPoss)
				{
					TablePart->StaticMesh->SetMaterial(0, Material_Blue);

					TablePart->Chess_Name = GM_Base->Chess_Next->Chess_Name;
					TablePart->Chess_Color = GM_Base->Chess_Next->Chess_Color;
					LPossRock = TablePart;
				}
			}
		}

		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == GM_Base->Chess_Next->Table_Pos_Current)
				{
					TablePart->Chess_Name = Note;
					TablePart->Chess_Color = None;

					break;
				}
			}
		}

		BaseChessAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AbaseChess::StaticClass(), BaseChessAll);
		for (auto It = BaseChessAll.CreateIterator(); It; It++)
		{
			AbaseChess* BaseChess = Cast<AbaseChess>(*It);
			if (BaseChess)
			{
				if (BaseChess->GetActorLocation().X == GM_Base->Chess_Next->GetActorLocation().X && BaseChess->GetActorLocation().Y == GM_Base->Chess_Next->GetActorLocation().Y)
				{
					FVector NewLocation;
					NewLocation.X = LPossRock->GetActorLocation().X;
					NewLocation.Y = LPossRock->GetActorLocation().Y;
					NewLocation.Z = BaseChess->GetActorLocation().Z;

					BaseChess->SetActorLocation(NewLocation);

					break;
				}
			}
		}

		F_ClearAllTable();

		switch (GM_Base->CheyHod)
		{
		    case None: {break; }
			case White:
			{
				GM_Base->IsCanCasting_White = true;
				break;
			}
			case Black:
			{
				GM_Base->IsCanCasting_Black = true;
				break;
			}
		}

		GM_Base->WidgetHistory->E_NewZapis(LCurrentName, "Casting", "Small", GM_Base->CheyHod);

		return true;

	}

	else if (GM_Base->Chess_Current->Table_Pos_Current.X > Table_Pos_Current.X)
	{
		LPoss.X = GM_Base->Chess_Current->Table_Pos_Current.X - 2.0f;
		LPoss.Y = GM_Base->Chess_Current->Table_Pos_Current.Y;

		TArray<AActor*> TablePartAll;
		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == LPoss)
				{
					TablePart->Chess_Name = GM_Base->Chess_Current->Chess_Name;
					TablePart->Chess_Color = GM_Base->Chess_Current->Chess_Color;
					LPossKing = TablePart;
				}
			}
		}

		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == GM_Base->Chess_Current->Table_Pos_Current)
				{
					TablePart->Chess_Name = Note;
					TablePart->Chess_Color = None;

					break;
				}
			}
		}

		TArray<AActor*> BaseChessAll;
		BaseChessAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AbaseChess::StaticClass(), BaseChessAll);
		for (auto It = BaseChessAll.CreateIterator(); It; It++)
		{
			AbaseChess* BaseChess = Cast<AbaseChess>(*It);
			if (BaseChess)
			{
				if (BaseChess->GetActorLocation().X == GM_Base->Chess_Current->GetActorLocation().X && BaseChess->GetActorLocation().Y == GM_Base->Chess_Current->GetActorLocation().Y)
				{
					FVector NewLocation;
					NewLocation.X = LPossKing->GetActorLocation().X;
					NewLocation.Y = LPossKing->GetActorLocation().Y;
					NewLocation.Z = BaseChess->GetActorLocation().Z;

					BaseChess->SetActorLocation(NewLocation);

					break;
				}
			}
		}

		LPoss.X = GM_Base->Chess_Next->Table_Pos_Current.X + 3.0f;
		LPoss.Y = GM_Base->Chess_Next->Table_Pos_Current.Y;

		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == LPoss)
				{
					TablePart->StaticMesh->SetMaterial(0, Material_Blue);

					TablePart->Chess_Name = GM_Base->Chess_Next->Chess_Name;
					TablePart->Chess_Color = GM_Base->Chess_Next->Chess_Color;
					LPossRock = TablePart;
				}
			}
		}

		TablePartAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATablePart::StaticClass(), TablePartAll);
		for (auto It = TablePartAll.CreateIterator(); It; It++)
		{
			ATablePart* TablePart = Cast<ATablePart>(*It);
			if (TablePart)
			{
				if (TablePart->Table_Pos_Current == GM_Base->Chess_Next->Table_Pos_Current)
				{
					TablePart->Chess_Name = Note;
					TablePart->Chess_Color = None;

					break;
				}
			}
		}

		BaseChessAll.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AbaseChess::StaticClass(), BaseChessAll);
		for (auto It = BaseChessAll.CreateIterator(); It; It++)
		{
			AbaseChess* BaseChess = Cast<AbaseChess>(*It);
			if (BaseChess)
			{
				if (BaseChess->GetActorLocation().X == GM_Base->Chess_Next->GetActorLocation().X && BaseChess->GetActorLocation().Y == GM_Base->Chess_Next->GetActorLocation().Y)
				{
					FVector NewLocation;
					NewLocation.X = LPossRock->GetActorLocation().X;
					NewLocation.Y = LPossRock->GetActorLocation().Y;
					NewLocation.Z = BaseChess->GetActorLocation().Z;

					BaseChess->SetActorLocation(NewLocation);

					break;
				}
			}
		}

		F_ClearAllTable();

		switch (GM_Base->CheyHod)
		{
		case None: {break; }
		case White:
		{
			GM_Base->IsCanCasting_White = true;
			break;
		}
		case Black:
		{
			GM_Base->IsCanCasting_Black = true;
			break;
		}
		}

		GM_Base->WidgetHistory->E_NewZapis(LCurrentName, "Casting", "Big", GM_Base->CheyHod);

		return true;

	}
	
	return false;
}






