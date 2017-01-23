// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NJPUtilityFunctionLibrary.h"
#include "SaveGameManager.h"
#include "GeneralDataManager.h"
#include "GameFramework/Actor.h"
#include "GamePlayManager.generated.h"

UCLASS()
class NAKJADIPM_API AGamePlayManager : public AActor
{
	GENERATED_BODY()
		DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FShowResumeDialogue, float, idleGain);
public:	

	//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResumeProcessedFinished, AGamePlayManager*);
	// Sets default values for this actor's properties
	AGamePlayManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called when the game starts or when spawned
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		AGeneralDataManager* DataManager = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		UCampaignSaveGame* CurrentGameData = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int ClickSkillIndex = 0;

	
	UFUNCTION()
		void UpdateGamePerSecond();

	FTimespan UpdateTimeSpan;
	FTimespan AutoSaveTimeSpan;

	UFUNCTION(BlueprintCallable, Category = "Data")
		void Initialize();
	//UFUNCTION(BlueprintNativeEvent, Category = "DmgSystem")
	//	void TakeDmg(int32 Damage);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
		void ProcessPlayerClick();
	UFUNCTION(BlueprintCallable, Category = "Interaction")
		void ProcessPlayerUpgrade(int SkillIndex, float Cost);
	
	UFUNCTION(BlueprintCallable, Category = "Processing")
		void ProcessParlimentSeatsResult();
	UFUNCTION(BlueprintCallable, Category = "Processing")
		void ProcessVotesPerSecond();
	UFUNCTION(BlueprintCallable, Category = "Processing")
		void AddVotesToSeats(float VoteCount);
	UFUNCTION(BlueprintCallable, Category = "Processing")
		int GetVotersCountByIndex(int Index);
	UFUNCTION(BlueprintCallable, Category = "Processing")
		void ProcessTimeRemaining();
	UFUNCTION(BlueprintCallable, Category = "Processing")
		void ProcessAchievement();
	UFUNCTION(BlueprintCallable, Category = "Processing")
		void ProcessGameResume();
	UFUNCTION(BlueprintCallable, Category = "Processing")
		float ReturnRemainingVotesFromCurrentSeat();
	UFUNCTION(BlueprintCallable, Category = "Processing")
		float  GetGainsBetweenNowAndLastProcessTime();
	UFUNCTION(BlueprintCallable, Category = "Processing")
		FTimespan GetTimeSpanBetweenNowAndLastProcessTime();
	
	UFUNCTION(BlueprintCallable, Category = "Processing")
		void SaveCurrentGame();

	UFUNCTION(BlueprintCallable, Category = "Processing")
		void ProcessFinishedReport();
	
	/*UFUNCTION(BlueprintCallable, Category = "Interaction")
	bool playerUpgrade();
	
	UFUNCTION(BlueprintCallable, Category = "loop")
	bool UpdateBalance();
	
	UFUNCTION(BlueprintCallable, Category = "loop")
	bool UpdateElectionData();*/

	UFUNCTION(BlueprintCallable, Category = "Event")
		void FireShowResumeDialogueEvent(float IdleGains);

	UPROPERTY(BlueprintAssignable, Category = "Event")
		FShowResumeDialogue OnShowResumeDialogue;
};
