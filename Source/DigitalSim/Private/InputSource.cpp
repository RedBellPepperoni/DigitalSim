// Fill out your copyright notice in the Description page of Project Settings.


#include "InputSource.h"

// Sets default values
AInputSource::AInputSource()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComp")); //Creating a mesh component to render the Actor

	OutputPin = CreateDefaultSubobject<UDigiPinComponent>(TEXT("InputPinComp"));  //creating Digi Pin Comp
	OutputPin->SetupAttachment(BaseMeshComp);
	
	OutputPin->ReceiveSignal(0);
}

// Called when the game starts or when spawned
void AInputSource::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInputSource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInputSource::ChangeInput()
{
	OutputPin->ReceiveSignal(!OutputPin->State()); //Flip the current input state - positive signal if it was negative and viceversa

}

