// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "baseChess.h"
#include "baseChess_King.generated.h"

/**
 * 
 */
UCLASS()
class CHESSCPP_API AbaseChess_King : public AbaseChess
{
	GENERATED_BODY()

public:
	AbaseChess_King();

protected:
	virtual void BeginPlay() override;
	
};
