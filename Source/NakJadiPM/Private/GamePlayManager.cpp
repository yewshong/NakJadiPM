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

		if (CurrentGameData)
		{
			ProcessParlimentSeatsResult();
			ProcessGameResume();

			FTimerHandle GameUpdateTimerHandle = FTimerHandle();
			GetWorldTimerManager().SetTimer(GameUpdateTimerHandle, this, &AGamePlayManager::UpdateGamePerSecond, UpdateTimeSpan.GetSeconds(), true);

			FTimerHandle AutoSaveTimerHandle = FTimerHandle();
			GetWorldTimerManager().SetTimer(AutoSaveTimerHandle, this, &AGamePlayManager::SaveCurrentGame, UpdateTimeSpan.GetSeconds(), true);
		}
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
			//todo add candidate
			SeatResult.OpponentIndex = GetRandomOpponentIndex(CurrentGameData->CampaignData.SelectedCandidate.Name);
			SeatResult.OpponentVPS = OpponentBaseVPS + (OpponentVPSAddictive*SeatResult.Index);
			CurrentGameData->CampaignData.SeatPossessionRecord.Add(SeatResult);
		}
		else
		{
			//FParlimentSeatResult CurrentSeatResult = CurrentGameData->CampaignData.SeatPossessionRecord.Last();

			//UE_LOG(LogTemp, Warning, TEXT("CurrentSeatPossesion: %f "), CurrentSeatResult.possesion);
			//if (CurrentSeatResult.possesion >= GetVotersCountByIndex(CurrentGameData->CampaignData.SeatPossessionRecord.Num() - 1))

			if (GetCandidateProgress()*100 > WinPercentageThreshold)
			{
				if (CurrentGameData->CampaignData.SeatPossessionRecord.Num() < CurrentGameData->CampaignData.ParlimentSeatsData.ParlimentSeats.Num())
				{
					FParlimentSeatResult SeatResult = FParlimentSeatResult();
					SeatResult.Index = CurrentGameData->CampaignData.SeatPossessionRecord.Num();
					SeatResult.possesion = 0;
					SeatResult.OpponentIndex = GetRandomOpponentIndex(CurrentGameData->CampaignData.SelectedCandidate.Name);
					SeatResult.OpponentVPS = OpponentBaseVPS + (OpponentVPSAddictive*SeatResult.Index);
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
		//float IdleGains = GetVPSGainsBetweenNowAndLastProcessTime(CurrentGameData->CampaignData.VotesPerSecond);
		//float OpponentGains = GetVPSGainsBetweenNowAndLastProcessTime(CurrentGameData->CampaignData.SeatPossessionRecord.Last().OpponentVPS);
		FTimespan GainTimeSpan = GetTimeSpanBetweenNowAndLastProcessTime();
		FTimespan doubleIdleTimeSpan = GetDoubleIdleTimeSpanBetweenNowAndLastProcessTime();

		ProcessByTimeSpan(GainTimeSpan, doubleIdleTimeSpan);

	}
	return;
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

void AGamePlayManager::ProcessByTimeSpan(FTimespan GainTimeSpan, FTimespan doubleIdleTimeSpan)
{
	FTimespan playerTimeSpan = GainTimeSpan + doubleIdleTimeSpan;
	FTimespan OpponentTimeSpan = GainTimeSpan;
	CurrentGameData->CampaignData.Balance += playerTimeSpan.GetTotalSeconds()*
		CurrentGameData->CampaignData.VotesPerSecond;
	
	for (int i = 0; i < playerTimeSpan.GetTotalSeconds(); i++)
	{
		if (i > TotalSecondsInOneDay) return;
		if (i < OpponentTimeSpan.GetTotalSeconds())
		{
			AddVotesToSeatsBySec(true);
		}
		else
		{
			AddVotesToSeatsBySec(false);
		}
	}
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

void AGamePlayManager::AddVotesToSeatsBySec(bool opponentAlso)
{
	if (CurrentGameData->CampaignData.SeatPossessionRecord.Num() > 0)
	{
		FParlimentSeatResult * CurrentResult = &CurrentGameData->CampaignData.SeatPossessionRecord.Last();
		
		float availableVote = FMath::Max(GetVotersCountByIndex(CurrentResult->Index)- CurrentResult->possesion - CurrentResult->OpponentPossesion,0.0f);
		float OutStandingVotesToBeDeducted = FMath::Max(CurrentGameData->CampaignData.VotesPerSecond - availableVote,0.0f);

		CurrentResult->possesion += CurrentGameData->CampaignData.VotesPerSecond;
		CurrentResult->possesion = FMath::Clamp(CurrentResult->possesion, 0.0f, (float)GetVotersCountByIndex(CurrentResult->Index));
		
		CurrentResult->OpponentPossesion -= OutStandingVotesToBeDeducted;
		CurrentResult->OpponentPossesion = FMath::Clamp(CurrentResult->OpponentPossesion, 0.0f, (float)GetVotersCountByIndex(CurrentResult->Index));

		if (opponentAlso)
		{
			float availableVote2 = FMath::Max(GetVotersCountByIndex(CurrentResult->Index) - CurrentResult->possesion - CurrentResult->OpponentPossesion, 0.0f);
			float OutStandingVotesToBeDeducted2 = FMath::Max(CurrentResult->OpponentVPS - availableVote2, 0.0f);

			CurrentResult->OpponentPossesion += CurrentResult->OpponentVPS;
			CurrentResult->OpponentPossesion = FMath::Clamp(CurrentResult->OpponentPossesion, 0.0f, (float)GetVotersCountByIndex(CurrentResult->Index));
			
			CurrentResult->possesion -= OutStandingVotesToBeDeducted2;
			CurrentResult->possesion = FMath::Clamp(CurrentResult->possesion, 0.0f, (float)GetVotersCountByIndex(CurrentResult->Index));
		}


		//UE_LOG(LogTemp, Warning, TEXT("Player Possesion: %f"), CurrentResult->possesion);
		//UE_LOG(LogTemp, Warning, TEXT("Opponent Possesion: %f"), CurrentResult->OpponentPossesion);
		//UE_LOG(LogTemp, Warning, TEXT("Total Possession: %f"), CurrentResult->possesion+CurrentResult->OpponentPossesion);

		ProcessParlimentSeatsResult();
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
		/*float preProcessBalance = CurrentGameData->CampaignData.Balance;
		float Gains = GetGainsBetweenNowAndLastProcessTime();		
		AddVotes(Gains);
		ProcessDoubleIdle();
		Gains = CurrentGameData->CampaignData.Balance - preProcessBalance;
		if (Gains > 0)
			FireShowResumeDialogueEvent(Gains); */
		float preProcessBalance = CurrentGameData->CampaignData.Balance;
		ProcessVotesPerSecond();
		float Gains = CurrentGameData->CampaignData.Balance - preProcessBalance;
		if (Gains > 0 && !CurrentGameData->CampaignData.Finished)
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

float AGamePlayManager::GetVPSGainsBetweenNowAndLastProcessTime(float &VPS)
{
	FTimespan IdleTimeSpan = GetTimeSpanBetweenNowAndLastProcessTime();
	float IdleGains = IdleTimeSpan.GetTotalSeconds() * VPS;
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
		if (CurrentGameData->CampaignData.EndTime > CurrentGameData->CampaignData.LastSavedTime)
		{
			IdleTimeSpan = CurrentGameData->CampaignData.EndTime - CurrentGameData->CampaignData.LastSavedTime;
		}
		else
			IdleTimeSpan = FTimespan(0, 0, 0);
		CurrentGameData->CampaignData.Finished = true;
	}
	return IdleTimeSpan;
}

FTimespan AGamePlayManager::GetDoubleIdleTimeSpanBetweenNowAndLastProcessTime()
{
	FTimespan result = FTimespan(0,0,0);
	for (int i = 0; i < CurrentGameData->CampaignData.ActivatedSkillRecord.Num(); i++)
	{
		if (CurrentGameData->CampaignData.ActivatedSkillRecord[i].SkillType == EActiveSkillType::DoubleIdle)
		{
			FTimespan IdleTimeSpan = GetTimeSpanBetweenNowAndLastProcessTime();
			FTimespan timeSpanToEnd = CurrentGameData->CampaignData.ActivatedSkillRecord[i].EndTime - FDateTime::Now();
			if (timeSpanToEnd < IdleTimeSpan)
			{
				result = timeSpanToEnd;
			}
			else
				result = IdleTimeSpan;
			break;
		}
	}
	return result;
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
			}
			AddVotes(IdleGains);
			break;
		}
	}
}

float AGamePlayManager::GetCandidateProgress()
{
	if(CurrentGameData)
	{
		return (float)(CurrentGameData->CampaignData.SeatPossessionRecord.Last().possesion) / GetVotersCountByIndex(CurrentGameData->CampaignData.SeatPossessionRecord.Num() - 1);
	}
	return 0;
}

float AGamePlayManager::GetOpponentProgress()
{
	if (CurrentGameData)
	{
		return (float)(CurrentGameData->CampaignData.SeatPossessionRecord.Last().OpponentPossesion) / GetVotersCountByIndex(CurrentGameData->CampaignData.SeatPossessionRecord.Num() - 1);
	}
	return 0;
}
int  AGamePlayManager::GetRandomOpponentIndex(FString SelectedCandidateName)
{
	if (CurrentGameData)
	{
		int Random = FMath::RandRange(0, CurrentGameData->CampaignData.CandidatesData.AllCandidates.Num() - 2);
		UE_LOG(LogTemp, Warning, TEXT("Random Candidate Name: %s"), *CurrentGameData->CampaignData.CandidatesData.AllCandidates[Random].Name);
		if (CurrentGameData->CampaignData.CandidatesData.AllCandidates[Random].Name != SelectedCandidateName)
			return Random;
		else if (Random != CurrentGameData->CampaignData.CandidatesData.AllCandidates.Num() - 2)
			return Random + 1;
		else if (Random > 0)
			return Random - 1;
	}
	return -1;
}


