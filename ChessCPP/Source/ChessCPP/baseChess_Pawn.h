// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "baseChess.h"
#include "baseChess_Pawn.generated.h"

/**
 * 
 */
UCLASS()
class CHESSCPP_API AbaseChess_Pawn : public AbaseChess
{
	GENERATED_BODY()

public:
	AbaseChess_Pawn();

protected:
	virtual void BeginPlay() override;

};
