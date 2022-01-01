// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ChipBase.h"
#include "DigiPinComponent.h"
#include "CustomSimPlayerController.generated.h"

/**
 * 
 */
class UDigiPinComponent;
class AChipBase;


UCLASS()
class DIGITALSIM_API ACustomSimPlayerController : public APlayerController
{
	GENERATED_BODY()
		
public:
		ACustomSimPlayerController();


		bool bHasInitiatorPin;
		FHitResult HitObjects;

protected:

	UDigiPinComponent* InitialPinRef;
	UDigiPinComponent* TargetPinRef;

protected:
	
	UFUNCTION(BlueprintCallable)
	void SelectObject();

	UFUNCTION(BlueprintCallable)
	void DeselectWires();

	
	
public:
	
	void PinSelected(AChipBase* ChipRef, UDigiPinComponent* inPinRef);

	
};
