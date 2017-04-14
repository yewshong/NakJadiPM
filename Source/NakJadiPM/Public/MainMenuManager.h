// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GeneralDataManager.h"
#include "GameFramework/Actor.h"
#include "MainMenuManager.generated.h"


UCLASS()
class NAKJADIPM_API AMainMenuManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMainMenuManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category= "UIEvent")
		bool ChangeToGameLevelIfConditionMet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		AGeneralDataManager* DataManager;
};
