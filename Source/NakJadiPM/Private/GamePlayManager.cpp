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

void AGamePlayManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	SaveCurrentGame();
}

void AGamePlayManager::Initialize()
{
	if (DataManager)
	{
		DataManager->Init();
		if (DataManager && DataManager->SaveGameManager)
			CurrentGameData = DataManager->SaveGameManager->GetCampaignSaveGame();

		ProcessParlimentSeatsResult();
		ProcessGameResume();	
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("number of active skill record :" + FString::FromInt(CurrentGameData->CampaignData.ActiveSkillData.ActiveSkills.Num())));

		FTimerHandle GameUpdateTimerHandle = FTimerHandle();
		GetWorldTimerManager().SetTimer(GameUpdateTimerHandle, this, &AGamePlayManager::UpdateGamePerSecond, UpdateTimeSpan.GetSeconds(), true);
		
		FTimerHandle AutoSaveTimerHandle = FTimerHandle();
		GetWorldTimerManager().SetTimer(AutoSaveTimerHandle, this, &AGamePlayManager::SaveCurrentGame, UpdateTimeSpan.GetSeconds(), true);
		InitHexMap();
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
		CurrentGameData->CampaignData.TimeRemaining = CurrentGameData->CampaignData.TimeRemaining - UpdateTimeSpan;
		ProcessActiveSkills();
		ProcessVotesPerSecond();
		ProcessParlimentSeatsResult();
		ProcessTimeRemaining();
		ProcessAchievement();
		CurrentGameData->CampaignData.LastProcessTime = FDateTime::Now();
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
		AddPlayerClick();
		ProcessDoubleClick();
	}
}

void AGamePlayManager::AddPlayerClick()
{
	CurrentGameData->CampaignData.Balance += CurrentGameData->CampaignData.ClickDamage;
	AddVotesToSeats(CurrentGameData->CampaignData.ClickDamage);
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
		float IdleGains = GetGainsBetweenNowAndLastProcessTime();
		AddVotes(IdleGains);
		ProcessDoubleIdle();
	}
}

void AGamePlayManager::AddVotes(float& gains)
{
	CurrentGameData->CampaignData.Balance += gains;
	AddVotesToSeats(gains);
}

void AGamePlayManager::ProcessAchievement()
{
	if (CurrentGameData)
	{
		if (CurrentGameData->CampaignData.SeatPossessionRecord.Num() >= 2)
		{
			if(CurrentGameData->CampaignData.SeatPossessionRecord.Num()/ CurrentGameData->CampaignData.ParlimentSeatsData.ParlimentSeats.Num() * 100 > 50)
				CurrentGameData->CampaignData.achievement = EAchievementEnum::PrimeMinister;
			else
				CurrentGameData->CampaignData.achievement = EAchievementEnum::ParliamentMember;
		}
		else
			CurrentGameData->CampaignData.achievement = EAchievementEnum::Candidate;

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
		CurrentGameData->CampaignData.LastSavedTime = FDateTime::Now();
		DataManager->UpdateSaveGame(CurrentGameData);
	}
}

void AGamePlayManager::ProcessGameResume()
{
	if (CurrentGameData)
	{
		float preProcessBalance = CurrentGameData->CampaignData.Balance;
		float Gains = GetGainsBetweenNowAndLastProcessTime();		
		AddVotes(Gains);
		ProcessDoubleIdle();
		Gains = CurrentGameData->CampaignData.Balance - preProcessBalance;
		if (Gains > 0)
			FireShowResumeDialogueEvent(Gains); 

		CurrentGameData->CampaignData.TimeRemaining = CurrentGameData->CampaignData.TimeRemaining - GetTimeSpanBetweenNowAndLastProcessTime();
		CurrentGameData->CampaignData.LastProcessTime = FDateTime::Now();
	}
}

float AGamePlayManager::GetGainsBetweenNowAndLastProcessTime()
{
	FTimespan IdleTimeSpan = GetTimeSpanBetweenNowAndLastProcessTime();
	float IdleGains = IdleTimeSpan.GetTotalSeconds() * CurrentGameData->CampaignData.VotesPerSecond;
	IdleGains = UNJPUtilityFunctionLibrary::ConvertTo2Decimals(IdleGains);
	return IdleGains;
}

FTimespan AGamePlayManager::GetTimeSpanBetweenNowAndLastProcessTime()
{
	FTimespan IdleTimeSpan;
	if (FDateTime::Now() < CurrentGameData->CampaignData.EndTime)
		IdleTimeSpan = FDateTime::Now() - CurrentGameData->CampaignData.LastProcessTime;
	else
	{
		IdleTimeSpan = CurrentGameData->CampaignData.EndTime - CurrentGameData->CampaignData.LastSavedTime;
		CurrentGameData->CampaignData.Finished = true;
	}
	return IdleTimeSpan;
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

void AGamePlayManager::ProcessVideoRewardAfterPlayed(EAdsRequestType requestType, EActiveSkillType skillType)
{

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Begin ProcessVideoReward"));
	if (requestType == EAdsRequestType::Skill )
	{
		if (CurrentGameData && DataManager)
		{

			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("number of active skill record :"+ FString::FromInt(CurrentGameData->CampaignData.ActiveSkillData.ActiveSkills.Num())));

			for (int i = 0; i < CurrentGameData->CampaignData.ActiveSkillData.ActiveSkills.Num(); i++)
			{
				if (CurrentGameData->CampaignData.ActiveSkillData.ActiveSkills[i].SkillType == skillType)
				{
					if (GEngine)
						GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Skill Type Found"));
					AddActiveSkill(CurrentGameData->CampaignData.ActiveSkillData.ActiveSkills[i]);
					break;
				}
			}
		}
	}
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Finished ProcessVideoReward"));
}

void  AGamePlayManager::AddActiveSkill(FActiveSkill skill)
{
	if (CurrentGameData && DataManager)
	{
		bool activated = false;
		//if no existing
		for(int i = 0; i < CurrentGameData->CampaignData.ActivatedSkillRecord.Num(); i++)
		{
			if (CurrentGameData->CampaignData.ActivatedSkillRecord[i].SkillType == skill.SkillType)
			{
				CurrentGameData->CampaignData.ActivatedSkillRecord[i].EndTime += skill.Duration;
				activated = true;
				break;
			}
		}

		if(!activated)
		{
			FActivatedSkill newActivatedSkill = FActivatedSkill();
			newActivatedSkill.SkillType = skill.SkillType;
			newActivatedSkill.StartTime = FDateTime::Now();
			newActivatedSkill.EndTime = newActivatedSkill.StartTime + skill.Duration;
			CurrentGameData->CampaignData.ActivatedSkillRecord.Add(newActivatedSkill);
		}
	}
}

void AGamePlayManager::ProcessActiveSkills()
{
	for (int i = 0; i < CurrentGameData->CampaignData.ActivatedSkillRecord.Num(); i++)
	{
		if (CurrentGameData->CampaignData.ActivatedSkillRecord[i].EndTime < FDateTime::Now())
		{
			CurrentGameData->CampaignData.ActivatedSkillRecord.RemoveAt(i);
			ProcessActiveSkills();
			break;
		}
	}
}

void AGamePlayManager::ProcessDoubleClick()
{
	for (int i = 0; i < CurrentGameData->CampaignData.ActivatedSkillRecord.Num(); i++)
	{
		if (CurrentGameData->CampaignData.ActivatedSkillRecord[i].SkillType == EActiveSkillType::DoubleClick)
		{
			AddPlayerClick();
			break;
		}
	}
}

bool AGamePlayManager::IsDoubleClickActivated()
{
	for (int i = 0; i < CurrentGameData->CampaignData.ActivatedSkillRecord.Num(); i++)
	{
		if (CurrentGameData->CampaignData.ActivatedSkillRecord[i].SkillType == EActiveSkillType::DoubleClick)
		{
			return true;
		}
	}
	return false;
}

void AGamePlayManager::ProcessDoubleIdle()
{
	for (int i = 0; i < CurrentGameData->CampaignData.ActivatedSkillRecord.Num(); i++)
	{
		if (CurrentGameData->CampaignData.ActivatedSkillRecord[i].SkillType == EActiveSkillType::DoubleIdle)
		{
			float IdleGains = GetGainsBetweenNowAndLastProcessTime();
			FTimespan IdleTimeSpan = GetTimeSpanBetweenNowAndLastProcessTime();
			FTimespan timeSpanToEnd = CurrentGameData->CampaignData.ActivatedSkillRecord[i].EndTime - FDateTime::Now();
			if (timeSpanToEnd < IdleTimeSpan)
			{
				IdleGains = timeSpanToEnd.GetTotalSeconds() * CurrentGameData->CampaignData.VotesPerSecond;
				IdleGains = UNJPUtilityFunctionLibrary::ConvertTo2Decimals(IdleGains);
			}
			AddVotes(IdleGains);
			break;
		}
	}
}


void  AGamePlayManager::InitHexMap()
{
	if (HexagonGrid && HexMapDataManager->MalaysiaHexMapDataTable)
	{
		HexagonGrid->AllTilesInfo = HexMapDataManager->MalaysiaHexMapTilesData;
		HexagonGrid->InitGrid(); 
	}
}
void  AGamePlayManager::UpdateHexMap()
{}

