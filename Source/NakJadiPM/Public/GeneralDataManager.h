// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	UPROPERTY(VisibleAnywhere, Category = "DataTable")
		FString DataVersion = "0,00";

	UPROPERTY(EditAnywhere, Category = "DataTable")
		UDataTable* ParlimentSeatsDataTable;

	UPROPERTY(EditAnywhere, Category = "DataTable")
		UDataTable* CandidatesDataTable;

	UPROPERTY(EditAnywhere, Category = "DataTable")
		UDataTable* SkillsCostData;

	UFUNCTION(BlueprintCallable, Category = "DataTable")
		void ContrustElectionDataFromDataTable();

	UFUNCTION(BlueprintCallable, Category = "DataTable")
		void ContsructCandidateDataFromDataTable();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FAllCandidatesData CandidatesData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FAllParlimentSeatsData ParlimentSeatsData;
	
	UFUNCTION(BlueprintCallable, Category = "SaveData")
	bool GameSaveDataExists();
	UFUNCTION(BlueprintCallable, Category = "SaveData")
	bool GameSaveDataExpired();
	//UFUNCTION(BlueprintCallable, Category = "SaveData")
	//void CreateNewGameSaveData();
};
