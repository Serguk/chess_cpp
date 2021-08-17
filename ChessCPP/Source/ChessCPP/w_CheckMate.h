// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "w_CheckMate.generated.h"

/**
 * 
 */
UCLASS()
class CHESSCPP_API Uw_CheckMate : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "UserFunctions")
		void MassageSetVis(int32 Selection);
	
};
