// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "baseChess.h"
#include "baseChess_Rock.generated.h"

/**
 * 
 */
UCLASS()
class CHESSCPP_API AbaseChess_Rock : public AbaseChess
{
	GENERATED_BODY()

public:
	AbaseChess_Rock();

protected:
	virtual void BeginPlay() override;

};
