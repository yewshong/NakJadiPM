// Fill out your copyright notice in the Description page of Project Settings.

#include "NakJadiPM.h"
#include "RetrieveTextManager.h"


// Sets default values
ARetrieveTextManager::ARetrieveTextManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARetrieveTextManager::BeginPlay()
{
	Super::BeginPlay();
	ConstructAllDisplayTextDataFromDataTable();
	DataConstructed = true;
}

// Called every frame
void ARetrieveTextManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


void ARetrieveTextManager::ConstructAllDisplayTextDataFromDataTable()
{
	DisplayTextData = TArray<FDisplayText>();
	if (DisplayTextDataTable)
	{
		int RowIndex = 1;
		bool TimetoBreak = false;
		while (!TimetoBreak)
		{
			FName FindRowName = FName(*FString::FromInt(RowIndex));
			FDisplayText* Row = DisplayTextDataTable->FindRow<FDisplayText>(FindRowName, FString(""));
			if (Row)
			{
				DisplayTextData.Add(*Row);
				RowIndex++;
			}
			else
			{
				TimetoBreak = true;
			}
		}
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("String Data return false =.='"));
}

FText ARetrieveTextManager::GetText(FString ID)
{
	if (!DataConstructed)
		ConstructAllDisplayTextDataFromDataTable();

	for (auto TextData : DisplayTextData)
	{
		if (TextData.ID == ID)
		{
			return TextData.Content;
		}
	}
	return FText::FromString(UnknowString);
}

