// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "RetrieveTextManager.generated.h"

USTRUCT(BlueprintType)
struct FDisplayText : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Content;
};

UCLASS()
class NAKJADIPM_API ARetrieveTextManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARetrieveTextManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


	UPROPERTY(EditAnywhere, Category = "DataTable")
		UDataTable* DisplayTextDataTable;

	UPROPERTY(EditAnywhere, Category = "DataTable")
		TArray<FDisplayText> DisplayTextData;

	UFUNCTION(BlueprintCallable, Category = "DataTable")
		void ConstructAllDisplayTextDataFromDataTable();

	UFUNCTION(BlueprintPure, Category = "DataTable")
		FText GetText(FString ID);

	bool DataConstructed = false;
	UPROPERTY(EditAnywhere, Category = "DataTable")
	FString UnknowString = "???";

};
