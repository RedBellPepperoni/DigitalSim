// Fill out your copyright notice in the Description page of Project Settings.


#include "OutputDisplay.h"

// Sets default values
AOutputDisplay::AOutputDisplay()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComp")); //Creating a mesh component to render the Actor

	OutputPinComp = CreateDefaultSubobject<UDigiPinComponent>(TEXT("OutputPinComp"));  //creating Digi Pin Comp
	OutputPinComp->SetupAttachment(BaseMeshComp);			//Attaching the DigiPin to the Main Mesh
							//Setting AActor Ref for Output instead of ChipRef

	OutputPinComp->CurrentPinType = EPinType::PinInput;		//Setting the Pintype to Input
	OutputPinComp->OutputRef = this;
	OutputPinComp->ReceiveSignal(0); //Setting initial signal


}

// Called when the game starts or when spawned
void AOutputDisplay::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AOutputDisplay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}








