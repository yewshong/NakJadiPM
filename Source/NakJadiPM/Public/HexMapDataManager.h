// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HexagonTile.h"
#include "GameFramework/Actor.h"
#include "HexMapDataManager.generated.h"

UCLASS()
class NAKJADIPM_API AHexMapDataManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHexMapDataManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, Category = "DataTable")
		UDataTable* MalaysiaHexMapDataTable;

	UFUNCTION(BlueprintCallable, Category = "DataTable")
		void ConstructMalaysiaHexMapDataFromDataTable();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TArray<FHexTileInfo> MalaysiaHexMapTilesData;

	
	
};
