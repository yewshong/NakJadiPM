// Fill out your copyright notice in the Description page of Project Settings.

#include "NakJadiPM.h"
#include "ProductsSaveGame.h"

UProductsSaveGame::UProductsSaveGame()
{
	SaveSlotName = TEXT("ProductData");
	UserIndex = 0;
	Medal = StartMedal;
	ConsumedRecords = TArray<FConsumedRecord>();
	AllProductsData = FAllProductsData();
	staffUpgradeRecords = TArray<FStaffUpgradeRecord>();
	NoAds = false;
	NoAdsActivated = true;
}

void UProductsSaveGame::UpdateProductInfo(FString &ID, FString &DisplayPrice)
{
	for(FProductData Product:AllProductsData.Products)
	{
		if (Product.ProductID == ID)
		{
			Product.DisplayPrice= FText::FromString(DisplayPrice);
			break;
		}
	}
}