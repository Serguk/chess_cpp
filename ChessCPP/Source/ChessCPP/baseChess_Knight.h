// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "baseChess.h"
#include "baseChess_Knight.generated.h"

/**
 * 
 */
UCLASS()
class CHESSCPP_API AbaseChess_Knight : public AbaseChess
{
	GENERATED_BODY()

public:
	AbaseChess_Knight();

protected:
	virtual void BeginPlay() override;
	
};
