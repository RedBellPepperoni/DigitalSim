// Copyright Epic Games, Inc. All Rights Reserved.

#include "DigitalSimGameMode.h"
#include "CustomSimPlayerController.h"
#include "DigitalSimCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADigitalSimGameMode::ADigitalSimGameMode()
{
	// use our custom PlayerController class
//	PlayerControllerClass = ADigitalSimPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	//if (PlayerPawnBPClass.Class != nullptr)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}



	PlayerControllerClass = ACustomSimPlayerController::StaticClass();
	//DefaultPawnClass = ARTSPlayerCameraSpectatorPawn::StaticClass();
}