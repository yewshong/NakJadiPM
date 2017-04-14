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
	Init();
}

void AGeneralDataManager::Init()
{
	if (!inited)
	{
		SaveGameManager = (ASaveGameManager*)GetWorld()->SpawnActor(ASaveGameManager::StaticClass());
		inited = true;
	}
}

// Called every frame
void AGeneralDataManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AGeneralDataManager:: ConstructAllDataFromDataTable()
{
	ConstructElectionDataFromDataTable();
	ConstructCandidateDataFromDataTable();
	ConstrucPoliticPartyDataFromDataTable();
	ConstructStatesDataFromDataTable();
	ConstructSkillsDataFromDataTable();
	ConstructActivateSkillsDataFromDataTable(); 
	ConstructBalloonSkillsDataFromDataTable(); 
	ConstructStaffUpgradesDataFromDataTable();
	ConstructProductsDataFromDataTable();
}

void AGeneralDataManager::ConstructElectionDataFromDataTable()
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
				ParlimentSeatsData.ParlimentSeats.Add(*Row);
				RowIndex++;
			}
			else
				TimetoBreak = true;
		}

	}
	else
		UE_LOG(LogTemp, Warning, TEXT("ParlimentSeats variable is not set =.='"));
}

void AGeneralDataManager::ConstructCandidateDataFromDataTable()
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
				CandidatesData.AllCandidates.Add(*Row);
				RowIndex++;
			}
			else
				TimetoBreak = true;
		}

	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Candidate variable is not set =.='"));
}

void AGeneralDataManager::ConstrucPoliticPartyDataFromDataTable()
{
	PoliticPartiesData = FAllPoliticPartyData();
	PoliticPartiesData.Version = DataVersion;
	if (PoliticPartiesDataTable)
	{
		int RowIndex = 1;
		bool TimetoBreak = false;
		while (!TimetoBreak)
		{
			FName FindRowName = FName(*FString::FromInt(RowIndex));
			FPoliticParty* Row = PoliticPartiesDataTable->FindRow<FPoliticParty>(FindRowName, FString(""));
			if (Row)
			{
				PoliticPartiesData.Parties.Add(*Row);
				RowIndex++;
			}
			else
				TimetoBreak = true;
		}

	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Politic Parties variable is not set =.='"));
}

void AGeneralDataManager::ConstructStatesDataFromDataTable()
{
	StatesData = FAllStatesData();
	StatesData.Version = DataVersion;
	if (StatesDataTable)
	{
		int RowIndex = 1;
		bool TimetoBreak = false;
		while (!TimetoBreak)
		{
			FName FindRowName = FName(*FString::FromInt(RowIndex));
			FState* Row = StatesDataTable->FindRow<FState>(FindRowName, FString(""));
			if (Row)
			{
				StatesData.States.Add(*Row);
				RowIndex++;
			}
			else
				TimetoBreak = true;
		}
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("States data variable is not set =.='"));
}

void AGeneralDataManager::ConstructSkillsDataFromDataTable()
{
	SkillsCostData = FAllSkillCostData();
	SkillsCostData.Version = DataVersion;
	if (SkillsCostDataTable)
	{
		int RowIndex = 1;
		bool TimetoBreak = false;
		while (!TimetoBreak)
		{
			FName FindRowName = FName(*FString::FromInt(RowIndex));
			FSkillCostInfo* Row = SkillsCostDataTable->FindRow<FSkillCostInfo>(FindRowName, FString(""));
			if (Row)
			{
				SkillsCostData.SkillCosts.Add(*Row);
				RowIndex++;
			}
			else
				TimetoBreak = true;
		}
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("SkillCost data return false =.='"));
}

void AGeneralDataManager::ConstructActivateSkillsDataFromDataTable()
{
	ActivateSkillsData = FAllActiveSkillsData();
	ActivateSkillsData.Version = DataVersion;
	if (ActivateSkillsDataTable)
	{
		int RowIndex = 1;
		bool TimetoBreak = false;
		while (!TimetoBreak)
		{
			FName FindRowName = FName(*FString::FromInt(RowIndex));
			FActiveSkill* Row = ActivateSkillsDataTable->FindRow<FActiveSkill>(FindRowName, FString(""));
			if (Row)
			{
				ActivateSkillsData.ActiveSkills.Add(*Row);
				RowIndex++;
			}
			else
				TimetoBreak = true;
		}
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Active Skill data return false =.='"));
}

void AGeneralDataManager::ConstructBalloonSkillsDataFromDataTable()
{
	BalloonSkillsData = FAllBalloonSkillsData();
	BalloonSkillsData.Version = DataVersion;
	if (BalloonSkillsDataTable)
	{
		int RowIndex = 1;
		bool TimetoBreak = false;
		while (!TimetoBreak)
		{
			FName FindRowName = FName(*FString::FromInt(RowIndex));
			FBalloonSkill* Row = BalloonSkillsDataTable->FindRow<FBalloonSkill>(FindRowName, FString(""));
			if (Row)
			{
				BalloonSkillsData.BalloonSkills.Add(*Row);
				RowIndex++;
			}
			else
			{
				TimetoBreak = true;
			}
		}
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Balloon Skill data return false =.='"));
}


void AGeneralDataManager::ConstructStaffUpgradesDataFromDataTable()
{
	StaffUpgradesData = FAllStaffUpgradeData();
	StaffUpgradesData.Version = DataVersion;
	if (StaffUpgradeDataTable)
	{
		int RowIndex = 1;
		bool TimetoBreak = false;
		while (!TimetoBreak)
		{
			FName FindRowName = FName(*FString::FromInt(RowIndex));
			FStaffUpgrade* Row = StaffUpgradeDataTable->FindRow<FStaffUpgrade>(FindRowName, FString(""));
			if (Row)
			{
				StaffUpgradesData.StaffUpgrades.Add(*Row);
				RowIndex++;
			}
			else
			{
				TimetoBreak = true;
			}
		}
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Staff Upgrade data return false =.='"));
}

void AGeneralDataManager::ConstructProductsDataFromDataTable()
{
	ProductsData = FAllProductsData();
	ProductsData.Version = DataVersion;
	if (ProductsDataTable)
	{
		int RowIndex = 1;
		bool TimetoBreak = false;
		while (!TimetoBreak)
		{
			FName FindRowName = FName(*FString::FromInt(RowIndex));
			FProductData* Row = ProductsDataTable->FindRow<FProductData>(FindRowName, FString(""));
			if (Row)
			{
				ProductsData.Products.Add(*Row);
				RowIndex++;
			}
			else
			{
				TimetoBreak = true;
			}
		}
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Products data return false =.='"));
}

bool AGeneralDataManager::GameSaveDataExists()
{
	if (SaveGameManager)
		return SaveGameManager->SaveExists();
	else
		return false;
}

bool  AGeneralDataManager::GameSaveDataExpired()
{
	//if(SaveGameManager::CurrentSaveGame)
	return false;
}

bool AGeneralDataManager::CreateNewAndSaveGame(FCandidate SelectedCandidate, FPoliticParty SelectedParty)
{
	FCurrentCampaignData CampaignData = FCurrentCampaignData();
	//add populate data from struct
	
	CampaignData.SelectedCandidate = SelectedCandidate;
	CampaignData.SelectedParty = SelectedParty;
	CampaignData.ParlimentSeatsData = ParlimentSeatsData;
	CampaignData.StatesData = StatesData;
	CampaignData.SkillsCostData = SkillsCostData;
	CampaignData.ActiveSkillData = ActivateSkillsData;
	CampaignData.BalloonSkillData = BalloonSkillsData;
	CampaignData.CandidatesData = CandidatesData;
	CampaignData.PoliticPartiesData = PoliticPartiesData;
	CampaignData.StaffUpgradesData = StaffUpgradesData;

	for (int i = 0; i < SkillsCostData.SkillCosts.Num(); i++)
	{
		if (i == 0)
			CampaignData.ClickDamage = SkillsCostData.SkillCosts[i].Damage;

		FSkillUpgradeInfo upgradeInfo = FSkillUpgradeInfo();
		upgradeInfo.Index = i;
		CampaignData.SkillUpgradeRecord.Add(upgradeInfo);
	}

	if (SaveGameManager)
		return SaveGameManager->CreateNewAndSaveGame(CampaignData);
	else {
		return false;
	}
}

bool AGeneralDataManager::DeleteSaveGame()
{
	if (SaveGameManager)
		return SaveGameManager->DeleteSaveGame();
	else
		return false;
}

bool AGeneralDataManager::UpdateSaveGame(UCampaignSaveGame* ToBeSavedGame)
{
	if (SaveGameManager)
		return SaveGameManager->UpdateSaveGame(ToBeSavedGame);
	else
		return false;
}


bool AGeneralDataManager::UpdateProductSave(UProductsSaveGame* ToBeSavedGame)
{
	if (SaveGameManager)
		return SaveGameManager->UpdateProductSaveGame(ToBeSavedGame);
	else
		return false;
}

bool AGeneralDataManager::CreateNewProductsSave()
{
	if (SaveGameManager)
		return SaveGameManager->CreateNewProductSaveGameAndSave(ProductsData);
	else {
		return false;
	}
}

bool AGeneralDataManager::ProductsSaveDataExists()
{
	if (SaveGameManager)
		return SaveGameManager->ProductsSaveExists();
	else
		return false;
}


bool AGeneralDataManager::ProcessProductsSaveGame()
{
	if (ProductsSaveDataExists())
	{
		SaveGameManager->UpdateProductsIfAny(ProductsData);
	}
	else
	{
		return CreateNewProductsSave();
	}

	return true;
}