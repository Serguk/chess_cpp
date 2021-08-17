// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Materials/Material.h"
#include "str_TablePart.generated.h"

/**
 * 
 */
USTRUCT()
struct Fstr_TablePart : public FTableRowBase

{
	GENERATED_USTRUCT_BODY()

	//text  name
	UPROPERTY()
		FText Table_Name;
	//vector2d  position
	UPROPERTY()
		FVector2D Table_Position;
	//color  material
	UPROPERTY()
		UMaterial* Table_Color;



};