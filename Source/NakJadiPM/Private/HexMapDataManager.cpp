// Fill out your copyright notice in the Description page of Project Settings.

#include "NakJadiPM.h"
#include "HexMapDataManager.h"


// Sets default values
AHexMapDataManager::AHexMapDataManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHexMapDataManager::BeginPlay()
{
	Super::BeginPlay();
	ConstructMalaysiaHexMapDataFromDataTable();
	
}

// Called every frame
void AHexMapDataManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AHexMapDataManager::ConstructMalaysiaHexMapDataFromDataTable()
{
	MalaysiaHexMapTilesData = TArray<FHexTileInfo>();
	if (MalaysiaHexMapDataTable)
	{
		int RowIndex = 1;
		bool TimetoBreak = false;
		while (!TimetoBreak)
		{
			FName FindRowName = FName(*FString::FromInt(RowIndex));
			FHexTileInfo* Row = MalaysiaHexMapDataTable->FindRow<FHexTileInfo>(FindRowName, FString(""));
			if (Row)
			{
				MalaysiaHexMapTilesData.Add(*Row);
				RowIndex++;
			}
			else
				TimetoBreak = true;
		}
		UE_LOG(LogTemp, Warning, TEXT("hex map row find break at %d"), RowIndex);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("hex map is null"));
}

