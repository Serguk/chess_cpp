// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "enum_ChessName.h"
#include "enum_ChessTeam.h"
#include "w_History.generated.h"

/**
 * 
 */
UCLASS()
class CHESSCPP_API Uw_History : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, Category = "UserFunctions")
		//void E_NewZapis(TEnumAsByte<enum_ChessName> Chess, FString Last, FString Next, TEnumAsByte<enum_ChessTeam> Color);
	
	   void E_NewZapis(const TEnumAsByte<enum_ChessName> &Chess, const FString &Last, const FString &Next, const TEnumAsByte<enum_ChessTeam> &Color);

	
};
