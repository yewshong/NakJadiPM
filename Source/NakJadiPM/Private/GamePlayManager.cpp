// Fill out your copyright notice in the Description page of Project Settings.

#include "NakJadiPM.h"
#include "NJPUtilityFunctionLibrary.h"
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


		if (DataManager && DataManager->SaveGameManager)
			CurrentProductsData = DataManager->SaveGameManager->GetProductSaveGame();

		if (CurrentGameData)
		{
			CurrentGameData->CampaignData.ClickDamage = UNJPUtilityFunctionLibrary::RecalculateClickGain(CurrentGameData->CampaignData, GetBonusClickMultiplier(), ClickSkillIndex);
			CurrentGameData->CampaignData.ClickDamage = UNJPUtilityFunctionLibrary::ConvertTo2Decimals(CurrentGameData->CampaignData.ClickDamage);
			CurrentGameData->CampaignData.VotesPerSecond = UNJPUtilityFunctionLibrary::RecalculateVPS(CurrentGameData->CampaignData, GetBonusVPSMultiplier(), ClickSkillIndex);
			CurrentGameData->CampaignData.VotesPerSecond = UNJPUtilityFunctionLibrary::ConvertTo2Decimals(CurrentGameData->CampaignData.VotesPerSecond);

			ProcessParlimentSeatsResult();
			//ProcessGameResume();

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
	if (CurrentGameData->CampaignData.Finished)
	{

		UE_LOG(LogAndroid, Warning, TEXT("campaign finished"));
	}

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
		CurrentGameData->CampaignData.SkillUpgradeRecord[SkillIndex].Level += 1;
		if (SkillIndex == ClickSkillIndex)
		{
			CurrentGameData->CampaignData.ClickDamage += 
			CurrentGameData->CampaignData.SkillsCostData.SkillCosts[SkillIndex].Damage;
			CurrentGameData->CampaignData.ClickDamage = UNJPUtilityFunctionLibrary::RecalculateClickGain(CurrentGameData->CampaignData, GetBonusClickMultiplier(), ClickSkillIndex);
			CurrentGameData->CampaignData.ClickDamage = UNJPUtilityFunctionLibrary::ConvertTo2Decimals(CurrentGameData->CampaignData.ClickDamage);
		}
		else
		{
			CurrentGameData->CampaignData.VotesPerSecond = UNJPUtilityFunctionLibrary::RecalculateVPS(CurrentGameData->CampaignData, GetBonusVPSMultiplier(),ClickSkillIndex);
			CurrentGameData->CampaignData.VotesPerSecond = UNJPUtilityFunctionLibrary::ConvertTo2Decimals(CurrentGameData->CampaignData.VotesPerSecond);
		}
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
			AddNewSeatsResult();
		}
		else
		{

			FParlimentSeatResult * CurrentResult = &CurrentGameData->CampaignData.SeatPossessionRecord.Last();
			if(CurrentResult->Status == ESeatStatus::Done)
				AddNewSeatsResult();
			else
			{
				
				if (CurrentResult->StateSeatsDone())
				{
					if (CurrentResult->GetPossesionPercent() > WinPercentageThreshold)
					{
						CurrentResult->Status = ESeatStatus::Done;
						AddNewSeatsResult();
					}
				}
				else
				{
					for (int i = 0; i < CurrentResult->StateSeatsResult.Num(); i++)
					{
						if (CurrentResult->StateSeatsResult[i].Status != ESeatStatus::Done)
						{

							UE_LOG(LogTemp, Warning, TEXT("Current Possesion is: %f"), CurrentResult->StateSeatsResult[i].possesion);
							UE_LOG(LogTemp, Warning, TEXT("CurrentStateSeatCount is: %d"), CurrentResult->StateSeatsResult[i].Count);
							UE_LOG(LogTemp, Warning, TEXT("Current Possesion Percent is: %f"), CurrentResult->StateSeatsResult[i].GetPossesionPercent());
							UE_LOG(LogTemp, Warning, TEXT("============================================="));
							if (CurrentResult->StateSeatsResult[i].GetPossesionPercent() > WinPercentageThreshold)
							{
								CurrentResult->StateSeatsResult[i].Status = ESeatStatus::Done;
							}
							break;
						}
					}
				}
			}
		}

		/*if (CurrentGameData->CampaignData.SeatPossessionRecord.Num() == 0)
		{
			//add a new one
			FParlimentSeatResult SeatResult = FParlimentSeatResult();
			SeatResult.OpponentIndex = GetRandomOpponentIndex(CurrentGameData->CampaignData.SelectedCandidate.Name);
			
			SeatResult.PartiIndex = GetRandomPartiIndex(CurrentGameData->CampaignData.SelectedParty.Name);
			for (auto StateSeatData : CurrentGameData->CampaignData.ParlimentSeatsData.ParlimentSeats[SeatResult.Index].StateSeats)
			{
				FStateSeatResult StateResult = FStateSeatResult();
				StateResult.OpponentVPS = 
				SeatResult.StateSeatsResult.Add(StateResult);
			}
			UNJPUtilityFunctionLibrary::RecalculateSeatOpponentVPS(CurrentGameData->CampaignData.SeatPossessionRecord.Num(), 1, GetHalveOpponentVPSMultiplier(), SeatResult);
			CurrentGameData->CampaignData.SeatPossessionRecord.Add(SeatResult);
		}
		else
		{
			//get from parliment seat data base on number
			//if done then add
			// add check at add vote 
			Todo::
            




			if (GetCandidateProgress()*100 > WinPercentageThreshold)
			{
				if (CurrentGameData->CampaignData.SeatPossessionRecord.Num() < CurrentGameData->CampaignData.ParlimentSeatsData.ParlimentSeats.Num())
				{
					FParlimentSeatResult SeatResult = FParlimentSeatResult();
					SeatResult.Index = CurrentGameData->CampaignData.SeatPossessionRecord.Num();
					SeatResult.possesion = 0;
					SeatResult.OpponentIndex = GetRandomOpponentIndex(CurrentGameData->CampaignData.SelectedCandidate.Name);
					//SeatResult.OpponentVPS = UNJPUtilityFunctionLibrary::RecalculateOpponentVPS(CurrentGameData->CampaignData.SeatPossessionRecord.Num(), 1, GetHalveOpponentVPSMultiplier()); //OpponentBaseVPS + (OpponentVPSAddictive*SeatResult.Index);
					SeatResult.OpponentPossesion = 0;
					SeatResult.PartiIndex = GetRandomPartiIndex(CurrentGameData->CampaignData.SelectedParty.Name);
					UNJPUtilityFunctionLibrary::RecalculateSeatOpponentVPS(CurrentGameData->CampaignData.SeatPossessionRecord.Num(), 1, GetHalveOpponentVPSMultiplier(), SeatResult);
					CurrentGameData->CampaignData.SeatPossessionRecord.Add(SeatResult);
				}
				else
				{
					//to do:: Fire game finished Event
					CurrentGameData->CampaignData.Finished = true;
				}
			}
		}*/
	}
}


void AGamePlayManager::AddNewSeatsResult()
{
	FParlimentSeatResult SeatResult = FParlimentSeatResult();
	SeatResult.Index = CurrentGameData->CampaignData.SeatPossessionRecord.Num() % CurrentGameData->CampaignData.ParlimentSeatsData.ParlimentSeats.Num();
	SeatResult.OpponentIndex = GetRandomOpponentIndex(CurrentGameData->CampaignData.SelectedCandidate.Name);
	SeatResult.PartiIndex = GetRandomPartiIndex(CurrentGameData->CampaignData.SelectedParty.Name);
	int MalaysiaLevel = (CurrentGameData->CampaignData.SeatPossessionRecord.Num() / CurrentGameData->CampaignData.ParlimentSeatsData.ParlimentSeats.Num()) + 1;
	UNJPUtilityFunctionLibrary::AddStateSeatAndRecalculateSeatVoteCount(CurrentGameData->CampaignData.SeatPossessionRecord.Num(), SeatResult, CurrentGameData->CampaignData.ParlimentSeatsData.ParlimentSeats[SeatResult.Index]);
	UNJPUtilityFunctionLibrary::RecalculateSeatOpponentVPS(CurrentGameData->CampaignData.SeatPossessionRecord.Num(), MalaysiaLevel, GetHalveOpponentVPSMultiplier(), SeatResult);
	
	CurrentGameData->CampaignData.SeatPossessionRecord.Add(SeatResult);
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
	CurrentGameData->CampaignData.Balance += playerTimeSpan.GetTotalSeconds()*CurrentGameData->CampaignData.VotesPerSecond;
	
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
		/*float VotesCurrent = VoteCount;
		float VotesRemaining = ReturnRemainingVotesFromCurrentSeat();
		if (VotesRemaining > VotesCurrent)
		{
			CurrentGameData->CampaignData.SeatPossessionRecord.Last().AddVotes(VotesCurrent);
			return;
		}
		else
		{
			CurrentGameData->CampaignData.SeatPossessionRecord.Last().AddVotes(VotesRemaining);
			VotesCurrent -= VotesRemaining;
			ProcessParlimentSeatsResult();

			if (CurrentGameData->CampaignData.Finished)
				return;

			//if (VotesCurrent > 0)// remove this to make sure no votes carry over by click
			//	AddVotesToSeats(VotesCurrent);
		}*/
		CurrentGameData->CampaignData.SeatPossessionRecord.Last().AddVotes(VoteCount, false);
		ProcessParlimentSeatsResult();

	}
}

void AGamePlayManager::AddVotesToSeatsBySec(bool opponentAlso)
{
	if (CurrentGameData->CampaignData.SeatPossessionRecord.Num() > 0)
	{
		FParlimentSeatResult * CurrentResult = &CurrentGameData->CampaignData.SeatPossessionRecord.Last();
		
		/*float availableVote = FMath::Max(GetVotersCountByIndex(CurrentResult->Index)- CurrentResult->possesion - CurrentResult->OpponentPossesion,0.0f);
		float OutStandingVotesToBeDeducted = FMath::Max(CurrentGameData->CampaignData.VotesPerSecond - availableVote,0.0f);

		CurrentResult->possesion += CurrentGameData->CampaignData.VotesPerSecond;
		CurrentResult->possesion = FMath::Clamp(CurrentResult->possesion, 0.0f, (float)GetVotersCountByIndex(CurrentResult->Index));
		
		CurrentResult->OpponentPossesion -= OutStandingVotesToBeDeducted;
		CurrentResult->OpponentPossesion = FMath::Clamp(CurrentResult->OpponentPossesion, 0.0f, (float)GetVotersCountByIndex(CurrentResult->Index));

		if (opponentAlso)
		{
			if (FDateTime::Now() > CurrentResult->OpponentDisableExpireTime)
			{
				float availableVote2 = FMath::Max(GetVotersCountByIndex(CurrentResult->Index) - CurrentResult->possesion - CurrentResult->OpponentPossesion, 0.0f);
				float OutStandingVotesToBeDeducted2 = FMath::Max(CurrentResult->OpponentVPS - availableVote2, 0.0f);

				CurrentResult->OpponentPossesion += CurrentResult->OpponentVPS;
				CurrentResult->OpponentPossesion = FMath::Clamp(CurrentResult->OpponentPossesion, 0.0f, (float)GetVotersCountByIndex(CurrentResult->Index));

				CurrentResult->possesion -= OutStandingVotesToBeDeducted2;
				CurrentResult->possesion = FMath::Clamp(CurrentResult->possesion, 0.0f, (float)GetVotersCountByIndex(CurrentResult->Index));
			}
		}*/
		CurrentResult->AddVotes(CurrentGameData->CampaignData.VotesPerSecond, opponentAlso);

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

float AGamePlayManager::ProcessGameResume()
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
		//if (Gains > 0 && !CurrentGameData->CampaignData.Finished)
		//	FireShowResumeDialogueEvent(Gains);

		CurrentGameData->CampaignData.TimeRemaining = CurrentGameData->CampaignData.TimeRemaining - GetTimeSpanBetweenNowAndLastProcessTime();
		CurrentGameData->CampaignData.LastProcessTime = FDateTime::Now();
		
		return Gains;
	}
	return 0;
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

/*void AGamePlayManager::FireShowResumeDialogueEvent(float IdleGains)
{
	OnShowResumeDialogue.Broadcast(IdleGains);
	UE_LOG(LogTemp, Warning, TEXT("Show Resume Dialogue! Idle Gains: %f"),IdleGains);
}*/

void AGamePlayManager::ProcessFinishedReport(int MedalsEarned)
{
	if (CurrentGameData && DataManager)
	{ 
		if (CurrentGameData->CampaignData.FinishedReported == false)
		{
			AddMedal(MedalsEarned);
			CurrentGameData->CampaignData.FinishedReported = true;
			DataManager->UpdateSaveGame(CurrentGameData);
		}
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
			for (int i = 0; i < CurrentGameData->CampaignData.ActiveSkillData.ActiveSkills.Num(); i++)
			{
				if (CurrentGameData->CampaignData.ActiveSkillData.ActiveSkills[i].SkillType == skillType)
				{
					AddActiveSkill(CurrentGameData->CampaignData.ActiveSkillData.ActiveSkills[i]);
					break;
				}
			}
		}
	}
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
int  AGamePlayManager::GetRandomOpponentIndex(FText SelectedCandidateName)
{
	if (CurrentGameData)
	{
		int Random = FMath::RandRange(0, CurrentGameData->CampaignData.CandidatesData.AllCandidates.Num() - 2);
		if (CurrentGameData->CampaignData.CandidatesData.AllCandidates[Random].Name.ToString() != SelectedCandidateName.ToString())
			return Random;
		else if (Random != CurrentGameData->CampaignData.CandidatesData.AllCandidates.Num() - 2)
			return Random + 1;
		else if (Random > 0)
			return Random - 1;
	}
	return -1;
}

int  AGamePlayManager::GetRandomPartiIndex(FText SelectedCandidateParti)
{
	if (CurrentGameData)
	{
		int Random = FMath::RandRange(0, CurrentGameData->CampaignData.PoliticPartiesData.Parties.Num() - 2);
		
		if (CurrentGameData->CampaignData.PoliticPartiesData.Parties[Random].Name.ToString() != SelectedCandidateParti.ToString())
			return Random;
		else if (Random != CurrentGameData->CampaignData.PoliticPartiesData.Parties.Num() - 2)
			return Random + 1;
		else if (Random > 0)
			return Random - 1;
	}
	return -1;
}


FBalloonSkill AGamePlayManager::GetRandomBalloonSkill()
{
	if (DataManager)
	{
		if (CurrentGameData->CampaignData.BalloonSkillData.BalloonSkills.Num()>0)
		{
			int randomIndex = FMath::RandRange(0, CurrentGameData->CampaignData.BalloonSkillData.BalloonSkills.Num() - 1);
			return CurrentGameData->CampaignData.BalloonSkillData.BalloonSkills[randomIndex];			
		}
	}
	FBalloonSkill RandomBalloonSkill = FBalloonSkill();
	return RandomBalloonSkill;
}

void AGamePlayManager::ActivateBalloonSkill(FBalloonSkill BalloonSkill)
{
	int effectNumber = UNJPUtilityFunctionLibrary::CalculateBalloonEffect(BalloonSkill, CurrentGameData->CampaignData);
	effectNumber = FMath::Max(BalloonSkill.MinimumNumber, effectNumber);
	switch (BalloonSkill.Type)
	{
	case EBalloonEffectType::AddGold: 
		CurrentGameData->CampaignData.Balance += effectNumber;
		break;
	case EBalloonEffectType::AddVote: 
		AddVotesToSeats(effectNumber);
		break;
	case EBalloonEffectType::DisableOpponent: 
		CurrentGameData->CampaignData.SeatPossessionRecord.Last().OpponentDisableExpireTime = FDateTime::Now() + FTimespan(0, effectNumber, 0);
		break;
	case EBalloonEffectType::DivideOpponentVPS: 
		CurrentGameData->CampaignData.SeatPossessionRecord.Last().OpponentVPS /= effectNumber;
		break;
	case EBalloonEffectType::MinusOpponentVoteCount: 
		CurrentGameData->CampaignData.SeatPossessionRecord.Last().OpponentPossesion -= effectNumber;
		CurrentGameData->CampaignData.SeatPossessionRecord.Last().OpponentPossesion = 
			FMath::Max(0.0f, CurrentGameData->CampaignData.SeatPossessionRecord.Last().OpponentPossesion);
		break;
	}
}


bool AGamePlayManager::AnyMedalLeft()
{
	if (CurrentProductsData && DataManager)
	{
		if (CurrentProductsData->Medal > 0)
			return true;

	}
	return false;
}

void  AGamePlayManager::AddMedal(int number)
{
	if (CurrentProductsData && DataManager)
	{
		CurrentProductsData->Medal += number;
		SaveCurrentProducts();
	}
}

void AGamePlayManager::MinusMedal(int number)
{
	if (CurrentProductsData && DataManager)
	{
		CurrentProductsData->Medal -= number;
		SaveCurrentProducts();
	}
}

void AGamePlayManager::SaveCurrentProducts()
{
	if (CurrentProductsData && DataManager)
	{
		DataManager->UpdateProductSave(CurrentProductsData);
	}
}


void AGamePlayManager::ProductsInfoReceived(FString productID, FString DisplayPrice)
{
	if (CurrentProductsData && DataManager)
	{
		for (int i = 0; i < CurrentProductsData->AllProductsData.Products.Num(); i++)
		{
			if (CurrentProductsData->AllProductsData.Products[i].ProductID == productID)
			{
				CurrentProductsData->AllProductsData.Products[i].DisplayPrice = FText::FromString(DisplayPrice);
				break;
			}
		}
		DataManager->UpdateProductSave(CurrentProductsData);
	}
}

void AGamePlayManager::ClaimedProduct(FString ProductID, FString TransactionID)
{
	if (CurrentProductsData && DataManager)
	{
		for (int i = 0; i < CurrentProductsData->AllProductsData.Products.Num(); i++)
		{
			if (CurrentProductsData->AllProductsData.Products[i].ProductID == ProductID)
			{
				switch (CurrentProductsData->AllProductsData.Products[i].Reward)
				{
					case EProductReward::NoAds:ActivateNoAds(); RecordConsumed(ProductID, TransactionID); break;
					case EProductReward::AddTenStars:AddMedal(10); RecordConsumed(ProductID, TransactionID); break;
				}
			}
		}
	}
	DataManager->UpdateProductSave(CurrentProductsData);
}


void AGamePlayManager::RestoredProduct(FString ProductID, FString TransactionID)
{
	if (CurrentProductsData && DataManager)
	{
		bool found = false;
		for (int i = 0; i < CurrentProductsData->ConsumedRecords.Num(); i++)
		{
			if (CurrentProductsData->ConsumedRecords[i].ProductID == ProductID &&
				CurrentProductsData->ConsumedRecords[i].TransactionID == TransactionID)
			{
				found = true;
				break;
			}
		}
		if (!found)
		{
			ClaimedProduct(ProductID, TransactionID);
		}
	}	
}


void AGamePlayManager::ActivateNoAds()
{
	if (CurrentProductsData && DataManager)
	{
		CurrentProductsData->NoAds = true;
		CurrentProductsData->NoAdsActivated = true;
	}
}

void AGamePlayManager::RecordConsumed(FString ProductID, FString TransactionID)
{
	if (CurrentProductsData && DataManager)
	{
		FConsumedRecord newRecord = FConsumedRecord();
		newRecord.ProductID = ProductID;
		newRecord.TransactionID = TransactionID;
		newRecord.UsedDate = FDateTime::Now();
		CurrentProductsData->ConsumedRecords.Add(newRecord);
		DataManager->UpdateProductSave(CurrentProductsData);
	}
}

void AGamePlayManager::ProcessStaffUpgrade(FString StaffName, int MedalCost)
{
	if (CurrentProductsData && CurrentGameData)
	{
		if (CurrentProductsData->Medal > MedalCost)
		{
			CurrentProductsData->Medal -= MedalCost;
			for (int i = 0; i < CurrentProductsData->staffUpgradeRecords.Num(); i++)
			{
				if (CurrentProductsData->staffUpgradeRecords[i].Name == StaffName)
				{
					for(auto StaffUpgradeData : CurrentGameData->CampaignData.StaffUpgradesData.StaffUpgrades)
					{ 
						if (StaffUpgradeData.Name == StaffName)
						{
							//add balance if the upgrade is add starting gold before upgrade so the upgrade is correct
							if (StaffUpgradeData.Type == EStaffUpgradeType::AddStartingGold)
							{
								CurrentGameData->CampaignData.Balance += CurrentProductsData->staffUpgradeRecords[i].NextValue -
									CurrentProductsData->staffUpgradeRecords[i].CurrentValue;
							} 

							CurrentProductsData->staffUpgradeRecords[i] = UNJPUtilityFunctionLibrary::CreateStaffUpgradeRecord(StaffUpgradeData, 
								CurrentProductsData->staffUpgradeRecords[i].CurrentLevel+1);
							UE_LOG(LogTemp, Warning, TEXT("level upgraded"));
							//CalculateVPS after upgrade
							if (StaffUpgradeData.Type == EStaffUpgradeType::AddVPS)
							{
								CurrentGameData->CampaignData.VotesPerSecond = UNJPUtilityFunctionLibrary::RecalculateVPS(CurrentGameData->CampaignData, GetBonusVPSMultiplier(),ClickSkillIndex);
								CurrentGameData->CampaignData.VotesPerSecond = UNJPUtilityFunctionLibrary::ConvertTo2Decimals(CurrentGameData->CampaignData.VotesPerSecond);
							}
							else if (StaffUpgradeData.Type == EStaffUpgradeType::AddClick)
							{
								CurrentGameData->CampaignData.ClickDamage = UNJPUtilityFunctionLibrary::RecalculateClickGain(CurrentGameData->CampaignData, GetBonusClickMultiplier(), ClickSkillIndex);
								CurrentGameData->CampaignData.ClickDamage = UNJPUtilityFunctionLibrary::ConvertTo2Decimals(CurrentGameData->CampaignData.ClickDamage);
							}
							else if (StaffUpgradeData.Type == EStaffUpgradeType::HalveOpponentVPS)
							{
								CurrentGameData->CampaignData.SeatPossessionRecord[CurrentGameData->CampaignData.SeatPossessionRecord.Num()-1].OpponentVPS =
									UNJPUtilityFunctionLibrary::RecalculateOpponentVPS(CurrentGameData->CampaignData.SeatPossessionRecord.Num()-1, 1, GetHalveOpponentVPSMultiplier());
								//-1 because the other 2 call of function only add record after calculate

								UE_LOG(LogTemp, Warning, TEXT("Halved opponent VPS : %f"), CurrentGameData->CampaignData.SeatPossessionRecord[CurrentGameData->CampaignData.SeatPossessionRecord.Num() - 1].OpponentVPS);
							}

							break;
						}
					}
				}
			}
			DataManager->UpdateProductSave(CurrentProductsData);
		}
		return;
	}
}


bool AGamePlayManager::IsEnoughMedal(int MedalRequest)
{
	if (CurrentProductsData)
	{
		if (CurrentProductsData->Medal >= MedalRequest)
			return true;
		else
			return false;
	}
	return false;
}

float AGamePlayManager::GetBonusVPSMultiplier()
{
	if (CurrentProductsData)
	{
		for(auto A : CurrentProductsData->staffUpgradeRecords)
		{
			if (A.Type == EStaffUpgradeType::AddVPS)
			{
				return A.CurrentValue;
			}
		}
	}

	return 0;
}


float AGamePlayManager::GetBonusClickMultiplier()
{
	float result = 0;
	if (CurrentProductsData)
	{
		for (auto A : CurrentProductsData->staffUpgradeRecords)
		{
			if (A.Type == EStaffUpgradeType::AddClick)
			{
				result = A.CurrentValue;
			}
		}
	}

	return result;
}

float AGamePlayManager::GetHalveOpponentVPSMultiplier()
{
	if (CurrentProductsData)
	{
		for (auto A : CurrentProductsData->staffUpgradeRecords)
		{
			if (A.Type == EStaffUpgradeType::HalveOpponentVPS)
			{
				return A.CurrentValue;
			}
		}
	}

	return 0;
}

bool AGamePlayManager::IsNoAds()
{
	if (CurrentProductsData)
	{
		return CurrentProductsData->NoAds;
	}
	return false;
}


void AGamePlayManager::SetWatchAdsForMedalCoolDown()
{
	if (CurrentProductsData && DataManager)
	{
		CurrentProductsData->MedalAdsRecord.LastClaimTime = FDateTime::Now() +
			CurrentProductsData->MedalAdsRecord.Cooldown;
		DataManager->UpdateProductSave(CurrentProductsData);
	}
}
