// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomSimPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/World.h"

ACustomSimPlayerController::ACustomSimPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;

}



void ACustomSimPlayerController::SelectObject()
{
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,false,HitObjects);

	if (Cast<UDigiPinComponent>(HitObjects.GetComponent()))
	{
		

		if (bHasInitiatorPin && InitialPinRef )
		{


			if(Cast<UDigiPinComponent>(HitObjects.GetComponent())->CurrentPinType != InitialPinRef->CurrentPinType)
			{ 
				

				TargetPinRef = Cast<UDigiPinComponent>(HitObjects.GetComponent()); // Setting Target Pin reference

				if (TargetPinRef)
				{
					TargetPinRef->ConnectPin(InitialPinRef);
					InitialPinRef->ConnectPin(TargetPinRef);

				}

				if (CableRef)
				{
					CableRef->AttachEndtoComponent(TargetPinRef);
				}

				
			}
			
			else
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, FString("Incompatible Pin Connection"));
				}

				
			}
			
			DeselectWires();
			//Check for the Pin type since only Output to input pin is only possible
		}

		else
		{
			
			InitialPinRef = Cast<UDigiPinComponent>(HitObjects.GetComponent());

			CableRef =  GetWorld()->SpawnActor<AWire>(InitialPinRef->GetComponentLocation(), InitialPinRef->GetComponentRotation());
			CableRef->AttachToComponent(InitialPinRef,FAttachmentTransformRules::SnapToTargetIncludingScale);
			CableRef->bIsOneEndAttached = true;
			bHasInitiatorPin = true;

		}
	}

	
}



void ACustomSimPlayerController::DeselectWires()
{

	if(bHasInitiatorPin && CableRef)
	{ 
		CableRef->Destroy();
	}

	InitialPinRef = nullptr;
	TargetPinRef = nullptr;

	bHasInitiatorPin = false;
	CableRef = nullptr;
}
