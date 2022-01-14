// Fill out your copyright notice in the Description page of Project Settings.


#include "InputSource.h"

// Sets default values
AInputSource::AInputSource()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BaseMeshComp")); //Creating a mesh component to render the Actor

	InputPinComp = CreateDefaultSubobject<UDigiPinComponent>(TEXT("InputPinComp"));  //creating Digi Pin Comp
	
	InputPinComp->SetupAttachment(BaseMeshComp);
	InputPinComp->CurrentPinType = EPinType::PinOutput;
	InputPinComp->InputRef = this;
	InputPinComp->ReceiveSignal(0);
	

	
	
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

int AInputSource::ChangeInput()
{
	InputPinComp->ReceiveSignal(!InputPinComp->State()); //Flip the current input state - positive signal if it was negative and viceversa

	return InputPinComp->State();
}

