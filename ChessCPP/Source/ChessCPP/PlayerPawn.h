// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "GameFramework/RotatingMovementComponent.h"

#include "PlayerPawn.generated.h"

UCLASS()
class CHESSCPP_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USceneComponent* Scene;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USpringArmComponent* Arm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		URotatingMovementComponent* RotatingMovementComp;
	
	//ForRotation
	UPROPERTY()
		float Interp_DeltaTime;
	UPROPERTY()
		bool Gate1;
	UPROPERTY()
		bool Gate2;
	UPROPERTY()
	    float Interp_Out;



	UFUNCTION()
		void RotateToWhitePos();
	UFUNCTION()
		void RotateToBlackPos();



	//UPROPERTY()
	//	Uw_SelectChess* Widget;
	//UPROPERTY()
	//	TSubclassOf<UUserWidget>WidgetClassSelectChess;


	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


};
