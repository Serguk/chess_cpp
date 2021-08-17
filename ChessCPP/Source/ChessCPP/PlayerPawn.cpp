// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "ConstructorHelpers.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>("Scene", false);
	RootComponent = Scene;

	Arm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Arm->SetupAttachment(Scene);
	Arm->TargetArmLength = 1000.f;
	Arm->SetRelativeRotation({-40.f,0.f,0.f});
	//Arm->RelativeRotation.Pitch = -40.f;
	Arm->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(Arm);

	RotatingMovementComp = CreateDefaultSubobject<URotatingMovementComponent>("RotateMovementComp");
	RotatingMovementComp->RotationRate.Yaw = 0.f;
	
	//get widget bluprint from content
	//static ConstructorHelpers::FClassFinder<UUserWidget>WidgetFind1(TEXT("/Game/Blueprints/W_SelectChess_bp"));
	//WidgetClassSelectChess = WidgetFind1.Class;
	
}

//==========================================================================================================
// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	//create widget bluprint
	//Widget = CreateWidget<Uw_SelectChess>(UGameplayStatics::GetPlayerController(GetWorld(), 0), WidgetClassSelectChess);
	//Widget->AddToViewport(0);
	


}
//==========================================================================================================
// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Interp_DeltaTime = DeltaTime;

	if (Gate1 == true)
	{

		//GLog->Log(FString::SanitizeFloat(GetActorRotation().Yaw));
		
		if (GetActorRotation().Yaw >= 178.f)
		{
			RotatingMovementComp->RotationRate.Yaw = 0.f;
			Gate1 = false;

			FQuat NewRotation;
			NewRotation.X = 0.f;
			NewRotation.Y = 0.f;
			NewRotation.Z = 180.f;

			SetActorRotation(NewRotation);

			//GLog->Log(FString::SanitizeFloat(GetActorRotation().Yaw));
		}
		 


	}

	if (Gate2 == true)
	{


		//GLog->Log(FString::SanitizeFloat(GetActorRotation().Yaw));

		if (GetActorRotation().Yaw <= 1.f)
		{
			RotatingMovementComp->RotationRate.Yaw = 0.f;
			Gate2 = false;

			FQuat NewRotation;
			NewRotation.X = 0.f;
			NewRotation.Y = 0.f;
			NewRotation.Z = 0.f;

			SetActorRotation(NewRotation);

			//GLog->Log(FString::SanitizeFloat(GetActorRotation().Yaw));
		}
	}

}
//==========================================================================================================
// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

//==========================================================================================================
void APlayerPawn::RotateToWhitePos()
{
	RotatingMovementComp->RotationRate.Yaw = -120.f;
	Gate2 = true;
}

void APlayerPawn::RotateToBlackPos()
{
	RotatingMovementComp->RotationRate.Yaw = 120.f;
	Gate1 = true;
}
//---------------------------------------------------------------------------