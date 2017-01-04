// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "NJPUtilityFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class NAKJADIPM_API UNJPUtilityFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "NJPUtility")
		static UTexture2D* LoadTextureFromPath(const FString& Path);
	
	
};
