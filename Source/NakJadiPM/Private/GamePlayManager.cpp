// Fill out your copyright notice in the Description page of Project Settings.

#include "NakJadiPM.h"
#include "GamePlayManager.h"


// Sets default values
AGamePlayManager::AGamePlayManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UpdateTimeSpan = FTimespan(0, 0, 1);
}

// Called when the game starts or when spawned
void AGamePlayManager::BeginPlay()
{
	Super::BeginPlay();
	Initialize();
}

void AGamePlayManager::Initialize()
{
	if (DataManager)
	{
		DataManager->BeginPlay();
		if (DataManager && DataManager->SaveGameManager)
			CurrentGameData = DataManager->SaveGameManager->GetCampaignSaveGame();

		FTimerHandle GameUpdateTimerHandle = FTimerHandle();
		GetWorldTimerManager().SetTimer(GameUpdateTimerHandle, this, &AGamePlayManager::UpdateGamePerSecond, UpdateTimeSpan.GetSeconds(), true);
		ProcessParlimentSeatsResult();
	}
}

// Called every frame
void AGamePlayManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AGamePlayManager::UpdateGamePerSecond()
{
	if (CurrentGameData)
	{
		//CurrentGameData
		CurrentGameData->CampaignData.Balance += CurrentGameData->CampaignData.VotesPerSecond;
		CurrentGameData->CampaignData.TimeRemaining = CurrentGameData->CampaignData.TimeRemaining - UpdateTimeSpan;
		ProcessVotesPerSecond();
		ProcessParlimentSeatsResult();
	}
}

/*void AGamePlayManager::Event_PlayerClick(int32 Damage)
{
	if (CurrentGameData)
	{
		UE_LOG(LogTemp, Warning, TEXT("playerClick event fired"), CurrentGameData->CampaignData.balance);
		if (CurrentGameData)
		{
			CurrentGameData->CampaignData.balance += CurrentGameData->CampaignData.ClickDamage;
		}
	}
}*/

void AGamePlayManager::ProcessPlayerClick()
{
	if (CurrentGameData)
	{
		CurrentGameData->CampaignData.Balance += CurrentGameData->CampaignData.ClickDamage;
		AddVotesToCurrentSeat(CurrentGameData->CampaignData.ClickDamage);
	}
}

void AGamePlayManager::ProcessPlayerUpgrade(int SkillIndex, int Cost)
{ 
	if (CurrentGameData)
	{
		if (SkillIndex == ClickSkillIndex)
		{
			CurrentGameData->CampaignData.ClickDamage += 
			CurrentGameData->CampaignData.SkillsCostData.SkillCosts[SkillIndex].Damage;
			UE_LOG(LogTemp, Warning, TEXT("Click Upgraded =.='"));
		}
		else
		{
			CurrentGameData->CampaignData.VotesPerSecond +=
				CurrentGameData->CampaignData.SkillsCostData.SkillCosts[SkillIndex].Damage;
			UE_LOG(LogTemp, Warning, TEXT("Skill Upgraded =.='"));

		}
		CurrentGameData->CampaignData.SkillUpgradeRecord[SkillIndex].Level += 1;
		CurrentGameData->CampaignData.Balance -= Cost;
	}
}

void AGamePlayManager::ProcessParlimentSeatsResult()
{
	if (CurrentGameData)
	{
		if (CurrentGameData->CampaignData.SeatPossessionRecord.Num() == 0)
		{
			//add a new one
			FParlimentSeatResult SeatResult = FParlimentSeatResult();
			SeatResult.Index = 0;
			SeatResult.possesion = 0;
			CurrentGameData->CampaignData.SeatPossessionRecord.Add(SeatResult);
		}
		else
		{
			FParlimentSeatResult CurrentSeatResult = CurrentGameData->CampaignData.SeatPossessionRecord.Last();
			if (CurrentSeatResult.possesion >= GetVotersCountByIndex(CurrentGameData->CampaignData.SeatPossessionRecord.Num() - 1))
			{
				if (CurrentGameData->CampaignData.SeatPossessionRecord.Num() < CurrentGameData->CampaignData.ParlimentSeatsData.ParlimentSeats.Num())
				{
					FParlimentSeatResult SeatResult = FParlimentSeatResult();
					SeatResult.Index = CurrentGameData->CampaignData.SeatPossessionRecord.Num();
					SeatResult.possesion = 0;
					CurrentGameData->CampaignData.SeatPossessionRecord.Add(SeatResult);
				}
				else
				{
					//to do:: Fire game finished Event
				}
			}
		}
	}
}

void AGamePlayManager::ProcessVotesPerSecond()
{
	if (CurrentGameData)
	{
		AddVotesToCurrentSeat(CurrentGameData->CampaignData.VotesPerSecond);
	}
}

void AGamePlayManager::AddVotesToCurrentSeat(float VoteCount)
{
	if (CurrentGameData->CampaignData.SeatPossessionRecord.Num()>0)
	{
		CurrentGameData->CampaignData.SeatPossessionRecord.Last().possesion += VoteCount;
		CurrentGameData->CampaignData.SeatPossessionRecord.Last().possesion = FMath::Clamp<float>(
			CurrentGameData->CampaignData.SeatPossessionRecord.Last().possesion,
			0,
			GetVotersCountByIndex(CurrentGameData->CampaignData.SeatPossessionRecord.Num() - 1)
		);
	}
}

int AGamePlayManager::GetVotersCountByIndex(int Index)
{
	if (CurrentGameData && Index < CurrentGameData->CampaignData.ParlimentSeatsData.ParlimentSeats.Num())
		return CurrentGameData->CampaignData.ParlimentSeatsData.ParlimentSeats[Index].Count;
	else 
		return 0;
}



