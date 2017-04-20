// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ProductsSaveGame.h"
#include "InAppPurchaseStructLibrary.h"
#include "CandidateDataManager.h"
#include "GameFramework/Actor.h"
#include "SaveGameManager.h"
#include "GeneralDataManager.generated.h"

UCLASS()
class NAKJADIPM_API AGeneralDataManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneralDataManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Init();
	bool inited = false;
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	UPROPERTY(VisibleAnywhere, Category = "DataTable")
		FString DataVersion = "0,00";

	UPROPERTY(EditAnywhere, Category = "DataTable")
		UDataTable* ParlimentSeatsDataTable;

	UPROPERTY(EditAnywhere, Category = "DataTable")
		UDataTable* CandidatesDataTable;

	UPROPERTY(EditAnywhere, Category = "DataTable")
		UDataTable* PoliticPartiesDataTable;

	UPROPERTY(EditAnywhere, Category = "DataTable")
		UDataTable* StatesDataTable;

	UPROPERTY(EditAnywhere, Category = "DataTable")
		UDataTable* SkillsCostDataTable;

	UPROPERTY(EditAnywhere, Category = "DataTable")
		UDataTable* ActivateSkillsDataTable;

	UPROPERTY(EditAnywhere, Category = "DataTable")
		UDataTable* BalloonSkillsDataTable;

	UPROPERTY(EditAnywhere, Category = "DataTable")
		UDataTable* StaffUpgradeDataTable;

	UPROPERTY(EditAnywhere, Category = "DataTable")
		UDataTable* ProductsDataTable;
	
	UFUNCTION(BlueprintCallable, Category = "DataTable")
		void ConstructAllDataFromDataTable();

	UFUNCTION(BlueprintCallable, Category = "DataTable")
		void ConstructElectionDataFromDataTable();

	UFUNCTION(BlueprintCallable, Category = "DataTable")
		void ConstructCandidateDataFromDataTable();
	UFUNCTION(BlueprintCallable, Category = "DataTable")
		void ConstrucPoliticPartyDataFromDataTable();

	UFUNCTION(BlueprintCallable, Category = "DataTable")
		void ConstructStatesDataFromDataTable();

	UFUNCTION(BlueprintCallable, Category = "DataTable")
		void ConstructSkillsDataFromDataTable();
	
	UFUNCTION(BlueprintCallable, Category = "DataTable")
		void ConstructActivateSkillsDataFromDataTable();

	UFUNCTION(BlueprintCallable, Category = "DataTable")
		void ConstructBalloonSkillsDataFromDataTable();

	UFUNCTION(BlueprintCallable, Category = "DataTable")
		void ConstructStaffUpgradesDataFromDataTable();

	UFUNCTION(BlueprintCallable, Category = "DataTable")
		void ConstructProductsDataFromDataTable();
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FAllCandidatesData CandidatesData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FAllPoliticPartyData PoliticPartiesData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FAllParlimentSeatsData ParlimentSeatsData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FAllStatesData StatesData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FAllSkillCostData SkillsCostData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FAllActiveSkillsData ActivateSkillsData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FAllBalloonSkillsData BalloonSkillsData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FAllStaffUpgradeData StaffUpgradesData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FAllProductsData ProductsData;
	
	UFUNCTION(BlueprintCallable, Category = "SaveData")
	bool GameSaveDataExists();
	UFUNCTION(BlueprintCallable, Category = "SaveData")
	bool GameSaveDataExpired();
	//UFUNCTION(BlueprintCallable, Category = "SaveData")
	//void CreateNewGameSaveData();

	UFUNCTION(BlueprintCallable, Category = "SaveData")
	bool CreateNewAndSaveGame(FCandidate SelectedCandidate,	FPoliticParty SelectedParty);
	
	UFUNCTION(BlueprintCallable, Category = "SaveData")
	bool DeleteSaveGame();

	UFUNCTION(BlueprintCallable, Category = "Save")
		bool UpdateSaveGame(UCampaignSaveGame* ToBeSavedGame);


	UFUNCTION(BlueprintCallable, Category = "SaveData")
		bool ProductsSaveDataExists();
	UFUNCTION(BlueprintCallable, Category = "SaveData")
		bool CreateNewProductsSave();
	UFUNCTION(BlueprintCallable, Category = "Save")
		bool UpdateProductSave(UProductsSaveGame* ToBeSavedGame);
	UFUNCTION(BlueprintCallable, Category = "Save")
		bool ProcessProductsSaveGame();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveData")
	ASaveGameManager* SaveGameManager = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClickSkillIndex")
		int ClickSkillIndex = 0;

	UFUNCTION(BlueprintCallable, Category = "Staff")
		int GetStartingBalance();
	
};
																			