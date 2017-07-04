// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ElectionDataManager.generated.h"

USTRUCT(BlueprintType)
struct FPoliticParty : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString TexturePath;
};

USTRUCT(BlueprintType)
struct FAllPoliticPartyData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Version;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FPoliticParty> Parties;

	FAllPoliticPartyData()
	{
		Parties = TArray<FPoliticParty>();
	}
};

USTRUCT(BlueprintType)
struct FState : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TexturePath;
};

USTRUCT(BlueprintType)
struct FAllStatesData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Version;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FState> States;

	FAllStatesData()
	{
		States = TArray<FState>();
	}
};

USTRUCT(BlueprintType)
struct FStateSeat : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Count;

	bool operator<(const FStateSeat& rhs) const
	{
		return Count < rhs.Count;
	}
};

USTRUCT(BlueprintType)
struct FParlimentSeat : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString State;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Count;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FStateSeat> StateSeats;
	
	FParlimentSeat()
	{
		StateSeats = TArray<FStateSeat>();
	}

	bool operator<(const FParlimentSeat& rhs) const
	{		
		if ((StateSeats.Num() == 0 && rhs.StateSeats.Num() == 0) ||
			(StateSeats.Num() != 0 && rhs.StateSeats.Num() != 0))
			return Count < rhs.Count;
		else if (StateSeats.Num() == 0 && rhs.StateSeats.Num() != 0)
			return false;
		else
			return true;
	}
};

USTRUCT(BlueprintType)
struct FAllParlimentSeatsData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Version;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FParlimentSeat> ParlimentSeats;

	FAllParlimentSeatsData()
	{
		ParlimentSeats = TArray<FParlimentSeat>();
	}
};

UENUM(BlueprintType)
enum class ESeatStatus : uint8
{
	Waiting,
	Progress,
	Done,
};

USTRUCT(BlueprintType)
struct FStateSeatResult
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float possesion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float OpponentPossesion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float OpponentVPS;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Count;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ESeatStatus Status;

	FStateSeatResult()
	{
		Status = ESeatStatus::Waiting;
		possesion = 0;
		OpponentPossesion = 0;
	}

	float GetPossesionPercent()
	{
		return(float)(possesion * 100 / Count);
	}


	void AddVotes(float votes, bool opponentAlso, FDateTime OpponentDisableExpireTime)
	{
		float availableVote = FMath::Max(Count - possesion - OpponentPossesion, 0.0f);
		float OutStandingVotesToBeDeducted = FMath::Max(votes - availableVote, 0.0f);

		possesion += votes;
		possesion = FMath::Clamp(possesion, 0.0f, (float)Count);

		OpponentPossesion -= OutStandingVotesToBeDeducted;
		OpponentPossesion = FMath::Clamp(OpponentPossesion, 0.0f, (float)Count);

		if (opponentAlso)
		{
			if (FDateTime::Now() > OpponentDisableExpireTime)
			{
				float availableVote2 = FMath::Max(Count - possesion - OpponentPossesion, 0.0f);
				float OutStandingVotesToBeDeducted2 = FMath::Max(OpponentVPS - availableVote2, 0.0f);

				OpponentPossesion += OpponentVPS;
				OpponentPossesion = FMath::Clamp(OpponentPossesion, 0.0f, (float)Count);

				possesion -= OutStandingVotesToBeDeducted2;
				possesion = FMath::Clamp(possesion, 0.0f, (float)Count);
			}
		}
	}
};

USTRUCT(BlueprintType)
struct FParlimentSeatResult 
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Index;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int OpponentIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OpponentPossesion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OpponentVPS;
			
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float possesion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PartiIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDateTime OpponentDisableExpireTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FStateSeatResult> StateSeatsResult;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ESeatStatus Status;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Count;

	FParlimentSeatResult()
	{
		possesion = 0;
		OpponentPossesion = 0;
		OpponentDisableExpireTime = FDateTime::Now();
		StateSeatsResult = TArray<FStateSeatResult>();
		Status = ESeatStatus::Waiting;
	}

	float GetPossesionPercent()
	{
		return(float)(possesion / Count)*100;
	}

	bool StateSeatsDone()
	{
		for (auto StateSeatResult : StateSeatsResult)
			if (StateSeatResult.Status != ESeatStatus::Done)
				return false;
		return true;
	}

	int GetCurrentStateSeatsIndex()
	{
		for (int i = 0; i < StateSeatsResult.Num(); i++)
		{
			if (StateSeatsResult[i].Status != ESeatStatus::Done)
				return i;
		}
		return StateSeatsResult.Num();
	}

	void AddVotes(float votes, bool opponentAlso)
	{
		if (StateSeatsDone())
		{
			float availableVote = FMath::Max(Count - possesion - OpponentPossesion, 0.0f);
			float OutStandingVotesToBeDeducted = FMath::Max(votes - availableVote, 0.0f);

			possesion += votes;
			possesion = FMath::Clamp(possesion, 0.0f, (float)Count);

			OpponentPossesion -= OutStandingVotesToBeDeducted;
			OpponentPossesion = FMath::Clamp(OpponentPossesion, 0.0f, (float)Count);

			if (opponentAlso)
			{
				if (FDateTime::Now() > OpponentDisableExpireTime)
				{
					float availableVote2 = FMath::Max(Count - possesion - OpponentPossesion, 0.0f);
					float OutStandingVotesToBeDeducted2 = FMath::Max(OpponentVPS - availableVote2, 0.0f);

					OpponentPossesion += OpponentVPS;
					OpponentPossesion = FMath::Clamp(OpponentPossesion, 0.0f,(float)Count);

					possesion -= OutStandingVotesToBeDeducted2;
					possesion = FMath::Clamp(possesion, 0.0f, (float)Count);
				}
			}
		}
		else
		{
			for (int i = 0; i < StateSeatsResult.Num(); i++)
			{
				if (StateSeatsResult[i].Status != ESeatStatus::Done)
				{
					StateSeatsResult[i].AddVotes(votes, opponentAlso, OpponentDisableExpireTime);
					break;
				}
			}
		}
	}


};

/*USTRUCT(BlueprintType)
struct FElectionData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Version;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FParlimentSeatResult> ParlimentSeatsResult;

	FElectionData()
	{
		Version = 0;
		ParlimentSeatsResult = TArray<FParlimentSeatResult>();
	}
};*/


UCLASS()
class NAKJADIPM_API AElectionDataManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElectionDataManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
};
