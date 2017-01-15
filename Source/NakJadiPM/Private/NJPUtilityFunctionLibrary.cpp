// Fill out your copyright notice in the Description page of Project Settings.

#include "NakJadiPM.h"
#include "NJPUtilityFunctionLibrary.h"





UTexture2D* UNJPUtilityFunctionLibrary::LoadTextureFromPath(const FString& Path)
{
	if (Path.IsEmpty()) return NULL;

	/*FString PathToLoad = "/Game/Textures/YourStructureHere";
	UTexture2D* tmpTexture = LoadTextureFromPath(PathToLoad);*/

	return Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *(Path)));
}


FString UNJPUtilityFunctionLibrary::FormatStringToGoldFormat(int input)
{
	return FString::FromInt(input);
}