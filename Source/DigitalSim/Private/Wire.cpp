// Fill out your copyright notice in the Description page of Project Settings.


#include "Wire.h"

// Sets default values
AWire::AWire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CableComp = CreateDefaultSubobject<UCableComponent>(TEXT("CableComp"));
	CableComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CableComp->NumSides = 8;
	CableComp->CableWidth = 20;
	CableComp->CableGravityScale = 0.8f;
	CableComp->EndLocation = FVector(0);
}

// Called when the game starts or when spawned
void AWire::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AWire::AttachEndToLocation(FVector inLocation)
{
	CableComp->EndLocation = inLocation;
}


void AWire::AttachEndtoComponent(UDigiPinComponent* inPin)
{


	//CableComp->SetAttachEndTo(inPin->GetOwner(),inPin->GetFName(), "WireSocket");
	CableComp->SetAttachEndToComponent(inPin, "WireSocket");

	if (bIsOneEndAttached)
	{
		EndPin = inPin;
	}

	else
	{
		StartPin = inPin;
	}
}

void AWire::ClearCableEnds()
{

}

