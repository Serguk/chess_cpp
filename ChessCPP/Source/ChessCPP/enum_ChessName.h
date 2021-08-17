// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "enum_ChessName.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum enum_ChessName
{
	Note       UMETA(DisplayName = "None"),
	Pawn       UMETA(DisplayName = "Pawn"),
	Knight     UMETA(DisplayName = "Knight"),
	Bishop     UMETA(DisplayName = "Bishop"),
	Rock       UMETA(DisplayName = "Rock"),
	Queen      UMETA(DisplayName = "Queen"),
	King       UMETA(DisplayName = "King"),
};
