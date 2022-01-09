// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "ChipBase.h"
#include "OutputDisplay.h"
#include "DigiPinComponent.generated.h"


class AChipBase;
class AOutputDisplay;
class UBoxComponent;
class UStaticMeshComponent;
class UDigiPinComponent;

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

	//Index of the Current Pin
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ChipEssentials")
	int Index;

	//Reference of the Pin that this recieves its input from
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ChipEssentials")
	UDigiPinComponent* ParentPin;


	//Reference of all the Pins that recieve input from this Pin
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ChipEssentials")
	TArray<UDigiPinComponent*> ChildPinArray;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "ChipEssentials")
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

	void ConnectPin(UDigiPinComponent* inPin);

	void DisconnectPin(UDigiPinComponent* inPin);

	UFUNCTION(BlueprintCallable)
	void ReceiveSignal(int inSignal);
		
};
