// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ProductsSaveGame.h"
#include "NJPUtilityFunctionLibrary.h"
#include "SaveGameManager.h"
#include "GeneralDataManager.h"
#include "HexMapDataManager.h"
#include "HexagonGrid.h"
#include "HexagonTile.h"
#include "GameFramework/Actor.h"
#include "GamePlayManager.generated.h"

UCLASS()
class NAKJADIPM_API AGamePlayManager : public AActor
{
	GENERATED_BODY()
		DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FShowResumeDialogue, float, idleGain);
public:	
	
	UFUNCTION(BlueprintCallable, Category = "Event")
		void FireShowResumeDialogueEvent(float IdleGains);

	UPROPERTY(BlueprintAssignable, Category = "Event")
		FShowResumeDialogue OnShowResumeDialogue;

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
		UProductsSaveGame* CurrentProductsData = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		AHexMapDataManager* HexMapDataManager = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		AHexagonGrid* HexagonGrid = nullptr;
	
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
	UFUNCTION(BlueprintCallable, Category = "Interaction")
		void AddActiveSkill(FActiveSkill skill);

		void AddPlayerClick();//refractor from processplayer click to use in double click skill too
		void AddVotes(float& gains);//refractor from processVotesPerSecond to use in double skill

	UFUNCTION(BlueprintCallable, Category = "Processing")
		void ProcessParlimentSeatsResult();
	UFUNCTION(BlueprintCallable, Category = "Processing")
		void ProcessVotesPerSecond();
	UFUNCTION(BlueprintCallable, Category = "Processing")
		void AddVotesToSeats(float VoteCount);
	UFUNCTION(BlueprintCallable, Category = "Processing")
		void AddVotesToSeatsBySec(bool opponentAlso);
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
		float GetVPSGainsBetweenNowAndLastProcessTime(float &VPS);
	UFUNCTION(BlueprintCallable, Category = "Processing")
		void ProcessByTimeSpan(FTimespan GainTimeSpan, FTimespan doubleIdleTimeSpan);
	UFUNCTION(BlueprintCallable, Category = "Processing")
		FTimespan GetTimeSpanBetweenNowAndLastProcessTime();
	UFUNCTION(BlueprintCallable, Category = "Processing")
		FTimespan GetDoubleIdleTimeSpanBetweenNowAndLastProcessTime();
	
	UFUNCTION(BlueprintCallable, Category = "Processing")
		void SaveCurrentGame();
	UFUNCTION(BlueprintCallable, Category = "Processing")
		void SaveCurrentProducts();

	UFUNCTION(BlueprintCallable, Category = "Processing")
		void ProcessFinishedReport(int MedalsEarned);

	UFUNCTION(BlueprintCallable, Category = "Processing")
		void ProcessVideoRewardAfterPlayed(EAdsRequestType requestType,EActiveSkillType skillType);

	UFUNCTION(BlueprintCallable, Category = "Processing")
		void ProcessActiveSkills();
	UFUNCTION(BlueprintCallable, Category = "Processing")
		void ProcessDoubleClick();
	UFUNCTION(BlueprintCallable, Category = "Processing")
		bool IsDoubleClickActivated();
	UFUNCTION(BlueprintCallable, Category = "Processing")
		void ProcessDoubleIdle();
	

	UFUNCTION(BlueprintCallable, Category = "RetrieveData")
		float GetCandidateProgress() ;
	UFUNCTION(BlueprintCallable, Category = "RetrieveData")
		float GetOpponentProgress();
	UFUNCTION(BlueprintCallable, Category = "RetrieveData")
		int GetRandomOpponentIndex(FString SelectedCandidateName);
	UFUNCTION(BlueprintCallable, Category = "RetrieveData")
		int GetRandomPartiIndex(FString SelectedCandidateParti);

	UFUNCTION(BlueprintCallable, Category = "Balloon")
	FBalloonSkill GetRandomBalloonSkill();
	UFUNCTION(BlueprintCallable, Category = "Balloon")
	void ActivateBalloonSkill(FBalloonSkill BalloonSkill);


	UFUNCTION(BlueprintCallable, Category = "Medal")
		bool AnyMedalLeft();
	UFUNCTION(BlueprintCallable, Category = "Medal")
		void AddMedal(int number);
	UFUNCTION(BlueprintCallable, Category = "Medal")
		void MinusMedal(int number);
	UFUNCTION(BlueprintCallable, Category = "Medal")
		bool IsEnoughMedal(int MedalRequest);

	UFUNCTION(BlueprintPure, Category = "Medal")
		bool IsNoAds();

	UFUNCTION(BlueprintCallable, Category = "Product")
		void ProductsInfoReceived(FString productID, FString DisplayPrice);
	UFUNCTION(BlueprintCallable, Category = "Product")
		void ClaimedProduct(FString ProductID, FString TransactionID);
	UFUNCTION(BlueprintCallable, Category = "Product")
		void ActivateNoAds();
	UFUNCTION(BlueprintCallable, Category = "Product")
		void RecordConsumed(FString ProductID, FString TransactionID);
	UFUNCTION(BlueprintCallable, Category = "Staff")
	void ProcessStaffUpgrade(FString StaffName, int MedalCost);
	UFUNCTION(BlueprintCallable, Category = "Staff")
		float GetBonusVPSMultiplier();
	UFUNCTION(BlueprintCallable, Category = "Staff")
		float GetBonusClickMultiplier();

	UPROPERTY(EditAnywhere, Category = "GameProperties")
		float OpponentBaseVPS = 0.1f;
	UPROPERTY(EditAnywhere, Category = "GameProperties")
		float OpponentVPSAddictive = 7.5f;
	UPROPERTY(EditAnywhere, Category = "GameProperties")
		float WinPercentageThreshold = 50.0f;
	UPROPERTY(EditAnywhere, Category = "GameProperties")
		double TotalSecondsInOneDay = 86400.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameProperties")
		int WatchAdsReward = 5;

};
