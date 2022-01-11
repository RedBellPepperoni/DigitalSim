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

	AOutputDisplay* OutputRef;

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


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	

	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	int State();

	bool HasParent();

	// Helper function to Connect this pin to another Pin using Object Reference
	void ConnectPin(UDigiPinComponent* inPin);

	//Fucntion to Disconnect the Pin if its an Input Type Pin
	void DisconnectInputPin();

	//Function to Disconnect the referenced Pin from self pin if current pin is Output type pin 
	void DisconnectOutputPin(UDigiPinComponent* inPin);

	UFUNCTION(BlueprintCallable)
	void ReceiveSignal(int inSignal);
		
};
