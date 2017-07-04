// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "PlayerSettings.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ELanguage : uint8
{
	English,
	Malay,
	Mandarin,
};

UCLASS()
class NAKJADIPM_API UPlayerSettings : public USaveGame
{
	GENERATED_BODY()
public:
	UPlayerSettings();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		bool SoundOn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		bool MusicOn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		ELanguage Language;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString SaveSlotName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int UserIndex;
};
