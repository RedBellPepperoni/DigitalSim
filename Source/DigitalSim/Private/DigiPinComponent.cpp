// Fill out your copyright notice in the Description page of Project Settings.


#include "DigiPinComponent.h"

// Sets default values for this component's properties
UDigiPinComponent::UDigiPinComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UDigiPinComponent::BeginPlay()
{
	Super::BeginPlay();
	CheckPower(); //Init checking of Pin power state
	// ...
	
}


// Called every frame
void UDigiPinComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int UDigiPinComponent::State()
{
		return CurrentPinState; //Getting the Current state of the Pin
}


// Sets true only if the Parent pin of this Pin has been set
	//For output pin, the chip itself is considered parent so it always returns true
bool UDigiPinComponent::HasParent()
{
	return ParentPin != nullptr || CurrentPinType == EPinType::PinOutput;
}

void UDigiPinComponent::ConnectPin(UDigiPinComponent* inPin)
{
	switch (CurrentPinType)
	{
		case EPinType::PinInput:	
			
									if (ParentPin)
									{
										ParentPin->DisconnectOutputPin(this);	//Disconnecting Previous connected wire before overwriting
										//add code for visual reprentaion later on: since disconnecting wires that are already connected will be necessary
									}

									ParentPin = inPin;	//Will replace/override previous parentPinref
									CurrentPinState = ParentPin->State(); //Setting State according to previous PArent if connection occurs

									
			break;

		case EPinType::PinOutput:	ChildPinArray.Add(inPin);
									
									for (int i = 0; i < ChildPinArray.Num(); i++)
									{	
										//Sending Outputs to all childpins if connections occurs
										if (ChildPinArray[i]->ChipRef)
											ChildPinArray[i]->ChipRef->ProcessOutput();

										
									}
			break;

		default:
			break;
	}

	//Checking the current power state
	CheckPower();

	if(ChipRef)
	{	
		ChipRef->ProcessOutput();//Calling the Chip To process the output of all its input pins
	}
	else if (OutputRef)
	{
		
		OutputRef->ShowOutput();//calling the OutputDisplay Event Hook
	}

	

}

//Pin Which Receives and input from others can only be connected by one otherpin
void UDigiPinComponent::DisconnectInputPin()
{
	if (ParentPin)
	{
		ParentPin->ChildPinArray.Remove(this);	//Removing current pin reference from the ParentPin's Child array
		ParentPin = nullptr;	//Clearing the Parent Pin Reference

		CurrentPinState = 0;	//Since there is no connection from any Pin, Set the state to 0 / OFF

		if (CableRef)
		{
			CableRef->Destroy(); //IF there was a cable attached to thos component -> Destroy it
		}
	}

	CheckPower(); //Update the Power State of this Pin / Object

	if(ChipRef)
	{
		ChipRef->ProcessOutput();	// If current pin is part of a Chip Process its output to propogate the changed data
	}

	else if (OutputRef)
	{
		OutputRef->ShowOutput();	//IF the pin is a part of OutputDisplay call the Event hook
	}

	

}

//Fucntion to Disconnect an Input Pin from the current Pin (OutputPin)
void UDigiPinComponent::DisconnectOutputPin(UDigiPinComponent* inPin)
{
	
	//Search and check if the pin to be disconnected is valid and in the child array
	if (ChildPinArray.Contains(inPin))
	{
		
		inPin->DisconnectInputPin();	//Call the Input Pin Disconnect function on that pin

		//FFOp
		//ChildPinArray.Remove(inPin);	//

	}

	CheckPower(); //Update the Power state of the Pin and Object


	

}

//Fucntion to Recieve and propogate the Pin State Signal
void UDigiPinComponent::ReceiveSignal(int inSignal)
{
	//Updating currentstate to match the incoming state
	CurrentPinState = inSignal;


	


	if (CurrentPinType == EPinType::PinInput) // if this Pin is an Input Pin, calculate the output
	{
		CheckPower();

		if (ChipRef)
		{
			
			ChipRef->ProcessOutput();
		}

		else if(OutputRef)
		{
			OutputRef->ShowOutput();
		}
		
	}

	

	else if ((CurrentPinType == EPinType::PinOutput)) // if this Pin is an Output pin, propogate the signal to its children
	{
		if (ChildPinArray.Num() > 0)
		{
			for (int i = 0; i < ChildPinArray.Num(); i++)
			{
				ChildPinArray[i]->ReceiveSignal(inSignal); //Sending all the child pins this pin is connected to - the same signal
			}
		}

		else
		{ 
			//Tmp Printing for debug

			//if(GEngine)
					//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%d"),inSignal));


			//Display the UI feedback
		}

		
	}
}

bool UDigiPinComponent::GetIsPowered()
{
	return bIsPowered;
}


//Function to check and update the Power state of the pin and Object

void UDigiPinComponent::CheckPower()
{
	switch (CurrentPinType)
	{
	case EPinType::PinInput:
								// Checking if Parent Pin is not null and Parent pin is a part of a Chip
								if (ParentPin && ParentPin->ChipRef)
								{
									bIsPowered = ParentPin->ChipRef->GetIsPowered();	//Setting current power state according to ParentPin's Chip's Power State
								}
								// Checking if Parent Pin is not null and Parent pin is a part of a InputSource
								else if(ParentPin && ParentPin->InputRef)
								{
									bIsPowered = true;	// setting power state as true since Input source are always powered
									
								}
								
								else
								{
									bIsPowered = false;	//Anything else setting power state to false
								}


								if (ChipRef)
								{
									ChipRef->PowerCheck();	//if pin is a part of chip call its Power check function
								}


								else if (OutputRef)
								{
									OutputRef->bIsPowered = bIsPowered;	//if the pin is part of outputDisplay change the power state of output display according to its pin		
								}
								
								
		break;

	case EPinType::PinOutput:

							if (ChipRef)
							{
								bIsPowered = ChipRef->GetIsPowered();	//If Pin is part of a Chip, call its power check FUnction
							}
							else if (InputRef)
							{
								bIsPowered = true;	// if pin is part of InputSouce make it powered since input sources are always powered
							}
							else 
							{
								bIsPowered = false;// Rest of the time make the state unpowered
							}
		break;

	default:
		break;
	}

}

