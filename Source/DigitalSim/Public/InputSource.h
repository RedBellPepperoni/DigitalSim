// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DigiPinComponent.h"
#include "InputSource.generated.h"

class UDigiPinComponent;


UCLASS()
class DIGITALSIM_API AInputSource : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInputSource();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UDigiPinComponent* OutputPin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BaseMeshComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ChangeInput();
};
