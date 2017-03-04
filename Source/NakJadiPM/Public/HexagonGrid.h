// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HexagonTile.h"
#include "GameFramework/Actor.h"
#include "HexagonGrid.generated.h"

UCLASS()
class NAKJADIPM_API AHexagonGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHexagonGrid();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AHexagonTile> HexTileClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<FHexTileInfo> AllTilesInfo;

	UPROPERTY(EditAnywhere, Category = Tile)
		float TileSize; 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Tile)
		float InnerRadius;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Tile)
		float OuterRadius;

	/** The width of the grid. Needed to calculate tile positions and neighbors. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile)
		int32 GridWidth;

	/** The height of the grid. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile)
		int32 GridHeight;

	UFUNCTION(BlueprintCallable, Category = Initialization)
		void InitGrid();

	UFUNCTION(BlueprintCallable, Category = Initialization)
		void CreateTile(FHexTileInfo &tileInfo);
 
	UFUNCTION(BlueprintCallable, Category = Initialization)
		FVector GetLocationFromGridAddress(FHexTileInfo &tileInfo);
};
