// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "baseChess.h"
#include "baseChess_Bishop.generated.h"

/**
 * 
 */
UCLASS()
class CHESSCPP_API AbaseChess_Bishop : public AbaseChess
{
	GENERATED_BODY()

public:
	AbaseChess_Bishop();

protected:
	virtual void BeginPlay() override;


	
};
