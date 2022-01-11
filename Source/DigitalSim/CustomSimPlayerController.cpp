// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomSimPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/World.h"

ACustomSimPlayerController::ACustomSimPlayerController()
{
	//Defaulting cursor and clicks
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;

}



void ACustomSimPlayerController::SelectObject()
{
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,false,HitObjects);	//Getting Items under the cursor

	if (Cast<UDigiPinComponent>(HitObjects.GetComponent()))	//Checking if Hit Component is of type DigiPin
	{
		/* Checking if Player has already clicked on a Pin and this is the second click to connect pins
		* if not make the click count as the first pin
		*/
		if (bHasInitiatorPin && InitialPinRef )
		{

			//Check to see if the Pin that are getting connected are of opposite type
			if(Cast<UDigiPinComponent>(HitObjects.GetComponent())->CurrentPinType != InitialPinRef->CurrentPinType)
			{ 
				

				TargetPinRef = Cast<UDigiPinComponent>(HitObjects.GetComponent()); // Setting Target Pin reference

				if (TargetPinRef)	//NullRef Check
				{
					TargetPinRef->ConnectPin(InitialPinRef);	//Connect function call on the Second clicked pin
					InitialPinRef->ConnectPin(TargetPinRef);	//Connect call on the initiator pin

				}

				if (CableRef)	//NullRef Check
				{
					CableRef->AttachEndtoComponent(TargetPinRef);		//Attaching the Cable End if its spawned in


				}

				//Setting Cable Pin Variables
				InitialPinRef->CableRef = CableRef;	
				TargetPinRef->CableRef = CableRef;

			}
			
			else
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, FString("Incompatible Pin Connection"));
				}

				
			}
			
			DeselectAll(); // If both the pin are connected or incompatible error - clear the references
			//Check for the Pin type since only Output to input pin is only possible
		}

		else // If the click is on a new pin without an initial ref
		{
			
			InitialPinRef = Cast<UDigiPinComponent>(HitObjects.GetComponent());	//Storing the ref of the initiator pin

			CableRef =  GetWorld()->SpawnActor<AWire>(InitialPinRef->GetComponentLocation(), InitialPinRef->GetComponentRotation());	//Spawning A cable Actor at the initiator Pin 
			CableRef->AttachToComponent(InitialPinRef,FAttachmentTransformRules::SnapToTargetIncludingScale);							//Making the cable a child of th Initiator pin
			CableRef->bIsOneEndAttached = true;	// Extra variable check to see if cable is connected on one end
			bHasInitiatorPin = true;			//Check varivale for Player to see if i has initaitor - can be deleted during optimizing stage

			

		}
	}

	else
	{
		DeselectAll();
	}

	
}


// Clearing the Varibels references for the Pins and Cable on the player
void ACustomSimPlayerController::DeselectAll()
{
	
	InitialPinRef = nullptr;
	TargetPinRef = nullptr;

	bHasInitiatorPin = false;
	CableRef = nullptr;
}


void ACustomSimPlayerController::DetachWires()
{
	
		// Getting the Objects under the Cursor
		GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitObjects);

		//Getting Specific UDigiPin type from the Hit Objects
		UDigiPinComponent* TempPinRef = Cast<UDigiPinComponent>(HitObjects.GetComponent());
		
		
		if (TempPinRef)	//Checking for Nullptrs
		{

			switch (TempPinRef->CurrentPinType)
			{
			case EPinType::PinInput:
									 
										TempPinRef->DisconnectInputPin();	//Disconnecting the Clicked pin if its a Input Type Pin

				break;
			case EPinType:: PinOutput:
										
										// Spawn UI Here and provide the Pin as reference

				if (TempPinRef->ChildPinArray.Num()>0)
				{
					TempPinRef->DisconnectOutputPin(TempPinRef->ChildPinArray[0]);	//Disconnecting the Clicked pin if its an Output Type Pin and passing the selected Pin
	
				}

				break;

			default:
				break;
			}
			
	
			
		}
		
		DeselectAll();

}
