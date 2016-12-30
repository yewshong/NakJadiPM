// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CandidateDataManager.generated.h"

USTRUCT(BlueprintType)
struct FCandidateSkills : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Cost;

	FCandidateSkills()
	{
	}
};

USTRUCT(BlueprintType)
struct FCandidate : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FCandidateSkills> Skills;

	FCandidate()
	{
		Skills = TArray<FCandidateSkills>();
	}
};

USTRUCT(BlueprintType)
struct FAllCandidatesData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Version;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FCandidate> AllCandidates;

	FAllCandidatesData()
	{
		Version = 0;
		AllCandidates = TArray<FCandidate>();
	}
};


UCLASS()
class NAKJADIPM_API ACandidateDataManager : public AActor
{
	GENERATED_BODY()
	 
public:	
	// Sets default values for this actor's properties
	ACandidateDataManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
