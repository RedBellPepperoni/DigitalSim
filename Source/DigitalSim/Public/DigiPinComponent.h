// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "ChipBase.h"
#include "OutputDisplay.h"
#include "Wire.h"
#include "DigiPinComponent.generated.h"


class AChipBase;
class AInputSource;
class AOutputDisplay;
class UBoxComponent;
class UStaticMeshComponent;
class UDigiPinComponent;
class AWire;

UENUM(BlueprintType)
enum class EPinType : uint8
{
	PinInput,

	PinOutput

};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DIGITALSIM_API UDigiPinComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDigiPinComponent();



	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ChipEssentials")
	bool Cyclic;

	//Reference to the Chip this Pin is attached to
	
	AChipBase* ChipRef;

	//Reference to the Output Display if the pin is attached to it
	AOutputDisplay* OutputRef;
	
	//Reference to the InputSource if the Pin is attached to it
	AInputSource* InputRef;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ChipEssentials")
	AWire* CableRef;

	//Index of the Current Pin
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ChipEssentials")
	int Index;

	//Reference of the Pin that this recieves its input from
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ChipEssentials")
	UDigiPinComponent* ParentPin;


	//Reference of all the Pins that recieve input from this Pin
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ChipEssentials")
	TArray<UDigiPinComponent*> ChildPinArray;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "ChipEssentials")
	EPinType CurrentPinType;
	


private :
	
	
	//Current State of the Pin 0 == LOW, 1 == HIGH;
	int CurrentPinState;

	//Storing the Power state of the Pin --- This helps to show if the main Object the pin is attached to is connected to the Input source or not
	//IF Objects are not connected to Input source - they wont display results since there needs to be atleast 1 active Input connection
	//Private to prevent mess that can happen in CustomChip Truthtable Generation algorithm
	bool bIsPowered; 


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	

	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Fucntion to Get the Current State of the Pin (0 = OFF, 1 = ON)
	UFUNCTION(BlueprintCallable)
	int State();

	//FFOp
	// Check to see fi the Pin has a parent -- can be removed during urther optimization
	bool HasParent();

	// Helper function to Connect this pin to another Pin using Object Reference
	void ConnectPin(UDigiPinComponent* inPin);

	//Fucntion to Disconnect the Pin if its an Input Type Pin
	void DisconnectInputPin();

	//Function to Disconnect the referenced Pin from self pin if current pin is Output type pin 
	void DisconnectOutputPin(UDigiPinComponent* inPin);

	//Function to Change current Pi nState according to previous call and propogate the changes tok the subsequently connected object
	UFUNCTION(BlueprintCallable)
	void ReceiveSignal(int inSignal);

	//Public function for Reading the current Power State 
	UFUNCTION(BlueprintCallable)
	bool GetIsPowered();

	//Function to Calculate f Current Pin should be powered or unpowered according to its parent component
	void CheckPower();
		
};
