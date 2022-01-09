// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DigiPinComponent.h"
#include "Misc/Char.h"
#include "ChipBase.generated.h"




class UDigiPinComponent;



USTRUCT(Blueprintable)
struct FChipData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChipEssentials")
	int index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChipEssentials")
	FName Chipname;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChipEssentials")
		int NumInputs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChipEssentials")
		int NumOutputs;


	/*
	Currently seperated the input adn output elements into two different arrays for simplicity sake
	can combine the arrays and cut each string in code for more optimization later
	*/

	//Arrays of each of the input
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChipEssentials")
	TArray<FString> TTInput;

	//Arrays of each of the output
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChipEssentials")
	TArray<FString> TTOutput;




};


UCLASS()
class DIGITALSIM_API AChipBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChipBase();

	UPROPERTY(VisibleAnywhere, Category = "ChipEssentials")
	FName ChipName;
	
	//Array of all the inputs to be created and assigned for a chip
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ChipEssentials")
	TArray< UDigiPinComponent*> InputPinArray;

	//Array of all the outputs to be created and assigned for a chip
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ChipEssentials")
	TArray< UDigiPinComponent*> OutputPinArray;

	// Struct of the Data that this chip has
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChipEssentials")
	FChipData ChipData;

	// Bool check if to use custom provided mesh or generate mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	bool bHasCustomMesh;


	
	USceneComponent* MeshRootComp;

	USceneComponent* PinsRootComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMesh* DigiPinMesh;

	// Array of the modular meshes to include for The Top end ------- the bottom mesh is the top mesh flipped 
	// 
	//The number of meshes should match with the InputMeshMask array
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<UStaticMesh*> TopMeshRef;

	// Array of the modular meshes to include for The Mid portion
	//The number of meshes should match with the InputMeshMask array
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<UStaticMesh*> MidMeshRef;

	// The input number check to compare against to switch the meshes.
	
	TArray<int> InputsMeshMask;

	
 
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
		
	

private:

	//total number of input signals recieved 
	int numInputsRecieved;

	// Extravariable for storing the index of teh mesh to be used
	int MeshSelectindex;

	UDigiPinComponent* SpawnedComponent;

	UStaticMeshComponent* PinMeshComp;

	 

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void RecieveInputSignal(UDigiPinComponent* pin);

	UFUNCTION(BlueprintCallable)
	void InitializeChipData();

	UFUNCTION(BlueprintCallable)
	virtual void ProcessOutput();

	

private:

	// Helper function to create a Pin element
	UFUNCTION()
	void CreatePin(FString inPinName, FVector inLocation, FRotator inRotation);

	// Main function to Send the calculated output forward
	UFUNCTION()
	void SendOutput(FString OutputSet);

	// Function to generate a custom mesh according to the numper of inputs
	UFUNCTION()
	void CreateChipMesh();


	// helpe function to spawn a mesh ---- used mainly by CreateChipmesh();
	UFUNCTION()
	void CreateMesh(FString inMeshName,FVector inLocation, FRotator inRotation, UStaticMesh* inMeshRef);

	
};
