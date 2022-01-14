// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DigiPinComponent.h"
#include "OutputDisplay.generated.h"

class UDigiPinComponent;

UCLASS()
class DIGITALSIM_API AOutputDisplay : public AActor
{
	GENERATED_BODY()
	
private:
		
	

public:	
	// Sets default values for this actor's properties
	AOutputDisplay();

	// A unique DigiPin Reference for connecting (Named Output pin but the actual type is InputPin)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UDigiPinComponent* OutputPinComp;

	// A Static Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BaseMeshComp;


	// Bool check to see if the Display is powered -- easier access than to access the pin everytime 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Variables")
	bool bIsPowered;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Unreal Event to Show the Output
	UFUNCTION(BlueprintImplementableEvent)
	void ShowOutput();

	

};
