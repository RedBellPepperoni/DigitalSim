// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CableComponent.h"
#include "DigiPinComponent.h"
#include "Wire.generated.h"

class UCableComponent;
class UDigiPinComponent;

UCLASS()
class DIGITALSIM_API AWire : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWire();

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Components")
	UCableComponent* CableComp;
	

	bool bIsOneEndAttached;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AttachEndToLocation(FVector inLocation);
	void AttachEndtoComponent(UDigiPinComponent* inPin);

	void ClearCableEnds();
};
