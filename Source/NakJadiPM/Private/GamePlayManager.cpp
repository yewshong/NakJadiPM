// Fill out your copyright notice in the Description page of Project Settings.

#include "NakJadiPM.h"
#include "GamePlayManager.h"


// Sets default values
AGamePlayManager::AGamePlayManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UpdateTimeSpan = FTimespan(0, 0, 1);
	AutoSaveTimeSpan = FTimespan(0, 0, 10);
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
		
		FTimerHandle AutoSaveTimerHandle = FTimerHandle();
		GetWorldTimerManager().SetTimer(AutoSaveTimerHandle, this, &AGamePlayManager::SaveCurrentGame, UpdateTimeSpan.GetSeconds(), true);
		
		ProcessParlimentSeatsResult();
		ProcessGameResume();
	}
}

// Called every frame
void AGamePlayManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AGamePlayManager::UpdateGamePerSecond()
{
	if (CurrentGameData && !CurrentGameData->CampaignData.Finished)
	{
		//CurrentGameData
		CurrentGameData->CampaignData.Balance += CurrentGameData->CampaignData.VotesPerSecond;
		CurrentGameData->CampaignData.TimeRemaining = CurrentGameData->CampaignData.TimeRemaining - UpdateTimeSpan;
		ProcessVotesPerSecond();
		ProcessParlimentSeatsResult();
		ProcessTimeRemaining();
		ProcessAchievement();
	}
}

void AGamePlayManager::ProcessTimeRemaining()
{
	if (CurrentGameData->CampaignData.TimeRemaining.GetTotalSeconds() <= 0)
	{
		CurrentGameData->CampaignData.Finished = true;
	}
}

void AGamePlayManager::ProcessPlayerClick()
{
	if (CurrentGameData)
	{
		CurrentGameData->CampaignData.Balance += CurrentGameData->CampaignData.ClickDamage;
		AddVotesToSeats(CurrentGameData->CampaignData.ClickDamage);
	}
}

void AGamePlayManager::ProcessPlayerUpgrade(int SkillIndex, float Cost)
{ 
	if (CurrentGameData)
	{
		if (SkillIndex == ClickSkillIndex)
		{
			CurrentGameData->CampaignData.ClickDamage += 
			CurrentGameData->CampaignData.SkillsCostData.SkillCosts[SkillIndex].Damage;
			CurrentGameData->CampaignData.ClickDamage = UNJPUtilityFunctionLibrary::ConvertTo2Decimals(CurrentGameData->CampaignData.ClickDamage);
		}
		else
		{
			CurrentGameData->CampaignData.VotesPerSecond +=
				CurrentGameData->CampaignData.SkillsCostData.SkillCosts[SkillIndex].Damage;
			CurrentGameData->CampaignData.VotesPerSecond = UNJPUtilityFunctionLibrary::ConvertTo2Decimals(CurrentGameData->CampaignData.VotesPerSecond);

		}
		CurrentGameData->CampaignData.SkillUpgradeRecord[SkillIndex].Level += 1;
		CurrentGameData->CampaignData.Balance -= Cost;
		SaveCurrentGame();
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
					UE_LOG(LogTemp, Warning, TEXT("New Seat need to add after index : %d, Last Seat Possesion : %f @ Voter Count : %f,"), 
						CurrentGameData->CampaignData.SeatPossessionRecord.Num() - 1,
						CurrentSeatResult.possesion, 
						GetVotersCountByIndex(CurrentGameData->CampaignData.SeatPossessionRecord.Num() - 1));
					FParlimentSeatResult SeatResult = FParlimentSeatResult();
					SeatResult.Index = CurrentGameData->CampaignData.SeatPossessionRecord.Num();
					SeatResult.possesion = 0;
					CurrentGameData->CampaignData.SeatPossessionRecord.Add(SeatResult);
				}
				else
				{
					//to do:: Fire game finished Event
					CurrentGameData->CampaignData.Finished = true;
				}
			}
		}
	}
}

void AGamePlayManager::ProcessVotesPerSecond()
{
	if (CurrentGameData)
	{
		AddVotesToSeats(CurrentGameData->CampaignData.VotesPerSecond);
	}
}


void AGamePlayManager::ProcessAchievement()
{
	if (CurrentGameData)
	{
		//if full win, return //

		//if candidate 
			//check if win alreayd at least 1 seat 
		//else if MPS
			//check if win alraedy 51% of seat
		//else if Majority 2/3 
			//check if win alrady 100%, set game finished = true;
	}
}

void AGamePlayManager::AddVotesToSeats(float VoteCount)
{
	if (CurrentGameData->CampaignData.SeatPossessionRecord.Num()>0)
	{
		float VotesCurrent = VoteCount;
		float VotesRemaining = ReturnRemainingVotesFromCurrentSeat();
		if (VotesRemaining > VotesCurrent)
		{
			CurrentGameData->CampaignData.SeatPossessionRecord.Last().possesion += VotesCurrent;
			return;
		}
		else
		{
			CurrentGameData->CampaignData.SeatPossessionRecord.Last().possesion += VotesRemaining;
			VotesCurrent -= VotesRemaining;
			ProcessParlimentSeatsResult();

			if (CurrentGameData->CampaignData.Finished)
				return;

			if (VotesCurrent > 0)
				AddVotesToSeats(VotesCurrent);
		}
		
		/*while(VotesCurrent > 0)
		{
			VotesRemaining = ReturnRemainingVotesFromCurrentSeat();
			VotesCurrent -= VotesRemaining;
			CurrentGameData->CampaignData.SeatPossessionRecord.Last().possesion += VotesRemaining;
			ProcessParlimentSeatsResult();
			if (CurrentGameData->CampaignData.Finished)
				break;
		}*/
	}
}


float AGamePlayManager::ReturnRemainingVotesFromCurrentSeat()
{
	return GetVotersCountByIndex(CurrentGameData->CampaignData.SeatPossessionRecord.Num() - 1) -
		CurrentGameData->CampaignData.SeatPossessionRecord.Last().possesion;
}

int AGamePlayManager::GetVotersCountByIndex(int Index)
{
	if (CurrentGameData && Index < CurrentGameData->CampaignData.ParlimentSeatsData.ParlimentSeats.Num())
		return CurrentGameData->CampaignData.ParlimentSeatsData.ParlimentSeats[Index].Count;
	else 
		return 0;
}

void AGamePlayManager::SaveCurrentGame()
{
	if (CurrentGameData && DataManager)
	{
		CurrentGameData->CampaignData.LastSavedTime = FDateTime::UtcNow();
		DataManager->UpdateSaveGame(CurrentGameData);
	}
}

void AGamePlayManager::ProcessGameResume()
{
	if (CurrentGameData)
	{
		FTimespan IdleTimeSpan;
		if(FDateTime::UtcNow() < CurrentGameData->CampaignData.EndTime)
			IdleTimeSpan = FDateTime::UtcNow() - CurrentGameData->CampaignData.LastSavedTime;
		else 
		{
			IdleTimeSpan = CurrentGameData->CampaignData.EndTime - CurrentGameData->CampaignData.LastSavedTime;
			CurrentGameData->CampaignData.Finished = true;
		}
		CurrentGameData->CampaignData.TimeRemaining = CurrentGameData->CampaignData.TimeRemaining - IdleTimeSpan;
		float IdleGains = FMath::FloorDouble(IdleTimeSpan.GetTotalSeconds()) * CurrentGameData->CampaignData.VotesPerSecond;
		UE_LOG(LogTemp, Warning, TEXT("Before Round: %f"), IdleGains);
		IdleGains = UNJPUtilityFunctionLibrary::ConvertTo2Decimals(IdleGains);
		UE_LOG(LogTemp, Warning, TEXT("After Round: %f"), IdleGains);
		CurrentGameData->CampaignData.Balance += IdleGains;
		AddVotesToSeats(IdleGains);
		
		if (IdleGains > 0)
			FireShowResumeDialogueEvent(IdleGains);
	}
}

void AGamePlayManager::FireShowResumeDialogueEvent(float IdleGains)
{
	OnShowResumeDialogue.Broadcast(IdleGains);
	UE_LOG(LogTemp, Warning, TEXT("Show Resume Dialogue! Idle Gains: %f"),IdleGains);
}

void AGamePlayManager::ProcessFinishedReport()
{
	if (CurrentGameData && DataManager)
	{
		CurrentGameData->CampaignData.FinishedReported = true;
		DataManager->UpdateSaveGame(CurrentGameData);
	}
}




