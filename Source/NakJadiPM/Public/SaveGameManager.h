// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CampaignSaveGame.h"
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
	//UFUNCTION(BlueprintCallable, Category = "Save")
	//bool CampaignFinished();
	//UFUNCTION(BlueprintCallable, Category = "Save")
	//bool UpdateAndSaveCampaignData();
};
