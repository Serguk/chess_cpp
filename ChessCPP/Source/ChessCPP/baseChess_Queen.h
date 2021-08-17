// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "baseChess.h"
#include "baseChess_Queen.generated.h"

/**
 * 
 */
UCLASS()
class CHESSCPP_API AbaseChess_Queen : public AbaseChess
{
	GENERATED_BODY()

public:
	AbaseChess_Queen();

protected:
	virtual void BeginPlay() override;
	
};
