// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "enum_ChessTeam.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum enum_ChessTeam
{
	None   UMETA(DisplayName = "None"),
	White  UMETA(DisplayName = "White"),
	Black  UMETA(DisplayName = "Black"),
};
