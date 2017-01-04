// Fill out your copyright notice in the Description page of Project Settings.

#include "NakJadiPM.h"
#include "GeneralDataManager.h"


// Sets default values
AGeneralDataManager::AGeneralDataManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGeneralDataManager::BeginPlay()
{
	Super::BeginPlay();
	ContrustElectionDataFromDataTable();
	ContsructCandidateDataFromDataTable();
}

// Called every frame
void AGeneralDataManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}
void AGeneralDataManager::ContrustElectionDataFromDataTable()
{	 
	ParlimentSeatsData = FAllParlimentSeatsData();
	ParlimentSeatsData.Version = DataVersion;
	if (ParlimentSeatsDataTable)
	{
		int RowIndex = 1;
		bool TimetoBreak = false;
		while (!TimetoBreak)
		{
			FName FindRowName = FName(*FString::FromInt(RowIndex));
			FParlimentSeat* Row = ParlimentSeatsDataTable->FindRow<FParlimentSeat>(FindRowName, FString(""));
			if (Row)
			{
				UE_LOG(LogTemp, Warning, TEXT("Parliment data found for %s"), *Row->Name);
				ParlimentSeatsData.ParlimentSeats.Add(*Row);
				RowIndex++;
			}
			else
				TimetoBreak = true;
		}
		UE_LOG(LogTemp, Warning, TEXT("ParlimentSeats data stop at %d"), RowIndex);

	}
	else
		UE_LOG(LogTemp, Warning, TEXT("ParlimentSeats Data return false =.='"));
}

void AGeneralDataManager::ContsructCandidateDataFromDataTable()
{
	CandidatesData = FAllCandidatesData();
	CandidatesData.Version = DataVersion;
	if (CandidatesDataTable)
	{
		int RowIndex = 1;
		bool TimetoBreak = false;
		while (!TimetoBreak)
		{
			FName FindRowName = FName(*FString::FromInt(RowIndex));
			FCandidate* Row = CandidatesDataTable->FindRow<FCandidate>(FindRowName, FString(""));
			if (Row)
			{
				UE_LOG(LogTemp, Warning, TEXT("Candidate data found for %s"), *Row->Name);
				CandidatesData.AllCandidates.Add(*Row);
				RowIndex++;
			}
			else
				TimetoBreak = true;
		}
		UE_LOG(LogTemp, Warning, TEXT("Candidate data stop at %d"), RowIndex);

	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Candidate data return false =.='"));
}

bool AGeneralDataManager::GameSaveDataExists()
{
	return SaveGameManager::SaveExists();
}

bool  AGeneralDataManager::GameSaveDataExpired()
{
	return false;
}






