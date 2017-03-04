// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperSpriteActor.h"
#include "HexagonTile.generated.h"

UENUM(BlueprintType)
enum class EHexTileStatus : uint8
{
	Idle,
	Active,
	done
};

USTRUCT(BlueprintType)
struct FHexTileInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int RowIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int ColumnIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EHexTileStatus Status;
};

/**
 * 
 */
UCLASS()
class NAKJADIPM_API AHexagonTile : public APaperSpriteActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int GridAdress;
	
	
	
};
