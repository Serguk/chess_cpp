// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "w_SelectChess.generated.h"

/**
 * 
 */
UCLASS()
class CHESSCPP_API Uw_SelectChess : public UUserWidget
{
	GENERATED_BODY()

    DECLARE_DELEGATE(Delegate_SelectedKnight)
	DECLARE_DELEGATE(Delegate_SelectedBishop)
	DECLARE_DELEGATE(Delegate_SelectedRock)
	DECLARE_DELEGATE(Delegate_SelectedQueen)


public:	

	Delegate_SelectedKnight Del_SelectedKnight;
	Delegate_SelectedBishop Del_SelectedBishop;
	Delegate_SelectedRock Del_SelectedRock;
	Delegate_SelectedQueen Del_SelectedQueen;


protected:
	virtual void NativeConstruct() override;




public:
	UFUNCTION(BlueprintCallable, Category = "WidgetCPP")
		void SelectedKnight();

	UFUNCTION(BlueprintCallable, Category = "WidgetCPP")
		void SelectedBishop();

	UFUNCTION(BlueprintCallable, Category = "WidgetCPP")
		void SelectedRock();

	UFUNCTION(BlueprintCallable, Category = "WidgetCPP")
		void SelectedQueen();

	
	
};
