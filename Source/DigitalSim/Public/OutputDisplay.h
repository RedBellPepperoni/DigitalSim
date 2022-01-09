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
	
public:	
	// Sets default values for this actor's properties
	AOutputDisplay();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UDigiPinComponent* OutputPinComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BaseMeshComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void ShowOutput();

};
