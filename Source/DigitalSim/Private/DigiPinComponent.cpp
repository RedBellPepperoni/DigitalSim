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
		case EPinType::PinInput:	ParentPin = inPin;	//Will replace/override previous parentPinref
									//add code for visual reprentaion later on: since disconnecting wires that are already connected will be necessary
									
								
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

	if(ChipRef)
	{
		ChipRef->ProcessOutput();
	}
	else if (OutputRef)
	{
		OutputRef->ShowOutput();
	}

}

void UDigiPinComponent::DisconnectPin(UDigiPinComponent* inPin)
{
	switch (CurrentPinType)
	{
	case EPinType::PinInput:

		//Figure out a way to Discoonect and remove pin refs
		ParentPin->ChildPinArray.RemoveAt(ParentPin->ChildPinArray.Find(this));
		
		ParentPin = nullptr;

		CurrentPinState = 0;

		ChipRef->ProcessOutput();

		break;
	case EPinType::PinOutput:

		

		break;
	default:
		break;
	}

}

void UDigiPinComponent::ReceiveSignal(int inSignal)
{
	CurrentPinState = inSignal;

	if (CurrentPinType == EPinType::PinInput) // if this Pin is an Input Pin, calculate the output
	{
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

			if(GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%d"),inSignal));


			//Display the UI feedback
		}

		
	}
}

