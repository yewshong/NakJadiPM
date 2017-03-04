// Fill out your copyright notice in the Description page of Project Settings.

#include "NakJadiPM.h"
#include "HexagonGrid.h"


// Sets default values
AHexagonGrid::AHexagonGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHexagonGrid::BeginPlay()
{
	Super::BeginPlay();
	OuterRadius = TileSize/2;
	InnerRadius = OuterRadius * 0.866025404f;
	
}

// Called every frame
void AHexagonGrid::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AHexagonGrid::InitGrid()
{
	for (int i = 0; i < AllTilesInfo.Num(); i++)
	{
			CreateTile(AllTilesInfo[i]);
	}
}


void AHexagonGrid::CreateTile(FHexTileInfo &tileInfo)
{
	UWorld* const World = GetWorld();
	if (World)
	{			
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			FRotator SpawnRotation(0.0f, 0.0f, 0.0f);
			FVector SpawnLocation = GetLocationFromGridAddress(tileInfo);
			AHexagonTile* NewTile = World->SpawnActor<AHexagonTile>(HexTileClass, SpawnLocation, SpawnRotation, SpawnParams);
	}
}

FVector AHexagonGrid::GetLocationFromGridAddress(FHexTileInfo &tileInfo)
{
	FVector position = FVector();
	//position.X = tileInfo.ColumnIndex * OuterRadius * 2;
	position.X = (tileInfo.ColumnIndex + tileInfo.RowIndex * 0.5f - tileInfo.RowIndex/2) * (OuterRadius * 2);//(3 + 0 * 0.5 - 0/2) * (InnerRadius*2)
	position.Y = 0;
	position.Z = tileInfo.RowIndex * (OuterRadius * 1.5f);
	return position;
}

