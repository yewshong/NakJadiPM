// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "NJPUtilityFunctionLibrary.h"
#include "ProductsSaveGame.h"
#include "CampaignSaveGame.h"
#include "PlayerSettings.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGameManager.generated.h"
/**
 * 
 */

UCLASS()
class NAKJADIPM_API ASaveGameManager : public AActor
{
	GENERATED_BODY()
public:
	ASaveGameManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	UCampaignSaveGame* CurrentSaveGame;
	UFUNCTION(BlueprintCallable, Category = "Save")
	UCampaignSaveGame* GetCampaignSaveGame();

	UFUNCTION(BlueprintCallable, Category = "Save")
	bool UpdateSaveGame(UCampaignSaveGame* ToBeSavedGame);
	UFUNCTION(BlueprintCallable, Category = "Save")
	bool CreateNewAndSaveGame(FCurrentCampaignData CampaignData);
	UFUNCTION(BlueprintCallable, Category = "Save")
	bool DeleteSaveGame();

	UFUNCTION(BlueprintCallable, Category = "Save")
	bool SaveExists();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
		UProductsSaveGame* CurrentProductSaveGame;
	UFUNCTION(BlueprintCallable, Category = "Save")
		UProductsSaveGame* GetProductSaveGame();
	UFUNCTION(BlueprintCallable, Category = "Save")
		bool ProductsSaveExists();	
	UFUNCTION(BlueprintCallable, Category = "Save")
		bool CreateNewProductSaveGameAndSave(FAllProductsData ProductsData, FAllStaffUpgradeData StaffUpgradesData);
	UFUNCTION(BlueprintCallable, Category = "Save")
		bool UpdateProductSaveGame(UProductsSaveGame* ToBeSavedGame);
	UFUNCTION(BlueprintCallable, Category = "Save")
		void UpdateProductsIfAny(FAllProductsData ProductsData);

	UFUNCTION(BlueprintCallable, Category = "Save")
		void UpdateStaffUpgradesIfAny(FAllStaffUpgradeData StaffUpgrades);



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
		UPlayerSettings* CurrentPlayerSettings;
	UFUNCTION(BlueprintCallable, Category = "Save")
		UPlayerSettings* GetPlayerSettings();
	UFUNCTION(BlueprintCallable, Category = "Save")
		bool SavedPlayerSettingsExists();
	UFUNCTION(BlueprintCallable, Category = "Save")
		bool CreateNewPlayerSettingsAndSave();
	UFUNCTION(BlueprintCallable, Category = "Save")
		bool UpdatePlayerSettingsSave(UPlayerSettings* PlayerSettings);

};
