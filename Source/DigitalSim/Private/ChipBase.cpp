// Fill out your copyright notice in the Description page of Project Settings.



#include "ChipBase.h"

// Sets default values
AChipBase::AChipBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	MeshRootComp = CreateDefaultSubobject<USceneComponent>(TEXT("MeshSceneRoot"));
	MeshRootComp->AttachToComponent(RootComponent,FAttachmentTransformRules::SnapToTargetIncludingScale);
	//MeshRootComp->SetWorldLocation(GetActorLocation());
	//MeshRootComp->SetRelativeLocation(FVector(0));

	

	PinsRootComp = CreateDefaultSubobject<USceneComponent>(TEXT("PinSceneRoot"));
	PinsRootComp->AttachToComponent(MeshRootComp,FAttachmentTransformRules::SnapToTargetIncludingScale);
	PinsRootComp->SetWorldLocation(GetActorLocation());
	PinsRootComp->SetRelativeLocation(FVector(0));

}

// Called when the game starts or when spawned
void AChipBase::BeginPlay()
{
	Super::BeginPlay();

	
}

void AChipBase::ProcessOutput()
{

	FString InputSet = "";
	
	
	int forIndex = pow(2,ChipData.NumInputs); //calculating binary permutations of the given number of inputs
	

	
	for (int i = 0; i < ChipData.NumInputs; i++) // Building a string with current inputs to compare it with the truth table values
	{
		
		
		switch(InputPinArray[i]->State()) //Assigning ints according to the inout pin states in Order
		{
			case 0: InputSet.AppendInt(0);
				break;

			case 1: InputSet.AppendInt(1);
				break;

		default:
			break;
		}

		
		if (i < ChipData.NumInputs - 1) // adding delimiter between everything expect after the last index
		{
			InputSet.Append(",");
		}
	}
	

	
	
	for (int j = 0; j < forIndex; j++) //comparing the built string with the truth table
	{
		
		if (ChipData.TTInput.Num() != forIndex)
		{
			//ErrorMEssgae that the TruthTbale isnt filled properly
			return;
		}

		if (InputSet.Equals(ChipData.TTInput[j]) ) //cheching id the input data set matches any entry
		{

			//Set output here
			SendOutput(ChipData.TTOutput[j]);

			break;
		}
		
		
			

		
		

	}


	
}

void AChipBase::OnClicked(UPrimitiveComponent* inPinComp, FKey ButtonPressed)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, FString("EEEEEEEEEEEEEEEEE"));
	}

}

// Called every frame
void AChipBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChipBase::RecieveInputSignal(UDigiPinComponent* pin)
{
	numInputsRecieved++;

	if(numInputsRecieved == InputPinArray.Num())
	{ 
		ProcessOutput();
	}
}


/*
Function to Spawn and initialize DigiPins
*/
void AChipBase::InitializeChipData()
{
	
	//Find a way to Clear the Child elements and clear the array.
	
	ChipName = ChipData.Chipname;

	CreateChipMesh();

	
}


void AChipBase::SendOutput(FString OutputSet)
{
	
	
	TArray<FString> Out;
	OutputSet.ParseIntoArray(Out, TEXT(","), true); //Spliting the comma seperated values into single character strings


	

	
	for (int i = 0; i < Out.Num(); i++)
	{
		
		int32 CheckInt = FCString::Atoi(*Out[i]); //Converting the string array chars into integer for calculations

		

		
		if (OutputPinArray[i] != nullptr) //Checking for null refs
		{
			switch (CheckInt)
			{
				
			case 0: OutputPinArray[i]->ReceiveSignal(0); //send negative signal if output matches 0
				break;

				
			case 1: OutputPinArray[i]->ReceiveSignal(1); //Send positive signal if output is 1
				break;

			default:
				break;
			}
		}
	}
}

void AChipBase::CreateChipMesh()
{
	//Creating mainBase mesh for center

	FString Meshname = "<nan>";

	float LocationX = 0.0f;
	MeshSelectindex = 0;

	if (InputsMeshMask.Num() > 0)
	{
		for (int i = 0; i < InputsMeshMask.Num(); i++)
		{
			if (ChipData.NumInputs <= InputsMeshMask[i])
			{
				MeshSelectindex = i;
				break;
			}

			else
			{
				MeshSelectindex = InputsMeshMask.Num() - 1;

			}
			

		}
	}

	/*Spawning the topmost end of the mesh
	  This will include calulating the location to spawn from the actor root will always be to the
	*/

	/// <summary>
	/// Calculating the Topmost location for the current num of inputs 
	/// (Assuming number of inputs is always greater or equal to the number of outputs)
	/// </summary>

	LocationX = float((ChipData.NumInputs-2) * 50.0f);


		//Spawning the topmost end of the mesh

	
		if ((ChipData.NumInputs & 1) == 0)
		{
			LocationX += 50.0f;	// Offestting values for even no of Meshes
		}
		
	

		//Spawning the rest of the mesh

	float YOffset = (MeshSelectindex + 1.0f) * 100.0f; //Offset for Inputs and output pins from the center


	if (ChipData.NumInputs > 0)
	{
		for (int i = 0; i < ChipData.NumInputs; i++)
		{

			if (i == 0)
			{
				if (TopMeshRef[MeshSelectindex]) // validity Check
				{
					Meshname = "TopMesh";
					CreateMesh(Meshname, FVector(LocationX, 0.0f, 0.0f), FRotator(0), TopMeshRef[MeshSelectindex]);
				}
				
				
			}

			else if (i == ChipData.NumInputs - 1)
			{
				//Spawning the Bottommost End of the mesh

				if (TopMeshRef[MeshSelectindex]) // validity Check
				{
					LocationX = LocationX - 100.0f;
					Meshname = "BotMesh";

					CreateMesh(Meshname, FVector(LocationX, 0.0f, 0.0f), FRotator(0.0f, 180.0f, 0.0f), TopMeshRef[MeshSelectindex]);
				}
			}

			/// Spawning the mid Meshes for the generated model

			else
			{
				if (MidMeshRef[MeshSelectindex]) //Validity Check
				{
					Meshname = "MidMesh_";
					Meshname.AppendInt(i);
					LocationX = LocationX - 100.0f;
					CreateMesh(Meshname, FVector(LocationX, 0.0f, 0.0f), FRotator(0), MidMeshRef[MeshSelectindex]);
				}

			}

			/// Spawning the Pin components for Connections

			SpawnedComponent = nullptr;
			FString Name = "InputPin_";
			Name.AppendInt(i);
			

			CreatePin(*Name, FVector(LocationX, -YOffset, 0.0f), FRotator(0.0f, 180.0f, 0.0f)); // Spawn Pins with Custom name and Offset


			if (SpawnedComponent)
			{
				SpawnedComponent->CurrentPinType = EPinType::PinInput; //initializing pintype
				InputPinArray.Add(SpawnedComponent); //storing the reference for future calculations
			}


		}



		
	}
	
	

	

}

void AChipBase::CreatePin(FString inPinName, FVector inLocation, FRotator inRotation)
{

	SpawnedComponent = NewObject<UDigiPinComponent>(this, *inPinName); //Spawning a Pin Component


	inPinName.Append("Mesh");


	if (SpawnedComponent) //Cheching if the Pin is Spawned correctly
	{

		SpawnedComponent->RegisterComponent();  //Registering the component according to unreal rules
		SpawnedComponent->AttachToComponent(PinsRootComp, FAttachmentTransformRules::SnapToTargetIncludingScale); //Attching the DigiPin component to each mesh
		SpawnedComponent->OnClicked.AddDynamic(this, &AChipBase::OnClicked);
		SpawnedComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
		SpawnedComponent->SetWorldLocation(GetActorLocation());

		AddInstanceComponent(SpawnedComponent); //This is to make the component show up in the Editor

		SpawnedComponent->ChipRef = this; //setting the Chip reference for the spawned component
		

		SpawnedComponent->SetStaticMesh(DigiPinMesh);
		SpawnedComponent->SetWorldLocation(PinMeshComp->GetComponentLocation());
		SpawnedComponent->SetRelativeLocation(inLocation);
		SpawnedComponent->SetRelativeRotation(inRotation);
	}

	

	

	

}

void AChipBase::CreateMesh(FString inMeshName, FVector inLocation, FRotator inRotation, UStaticMesh* inMeshRef)
{
	
	PinMeshComp = NewObject<UStaticMeshComponent>(this, *inMeshName); //Spawning a Mesh Component
	PinMeshComp->RegisterComponent();  //Registering the component according to unreal rules
	PinMeshComp->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	PinMeshComp->SetWorldLocation(GetActorLocation());
	PinMeshComp->bCastDynamicShadow = false;
	AddInstanceComponent(PinMeshComp); //This is to make the component show up in the Editor
	



	if (inMeshRef)// if mesh is valid
	{

		PinMeshComp->SetStaticMesh(inMeshRef);
		PinMeshComp->AttachToComponent(MeshRootComp, FAttachmentTransformRules::SnapToTargetIncludingScale); //Attching the DigiPin component to each mesh
		PinMeshComp->SetWorldLocation(MeshRootComp->GetComponentLocation()); //hacky method to make the component come to actor loc else they end up at world 0,0,0
		PinMeshComp->SetRelativeLocation(inLocation); //setting relative location of mesh
		PinMeshComp->SetRelativeRotation(inRotation);//Setting relative rotation


	}


}


