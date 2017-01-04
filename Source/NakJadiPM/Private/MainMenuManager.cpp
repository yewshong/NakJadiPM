// Fill out your copyright notice in the Description page of Project Settings.

#include "NakJadiPM.h"
#include "MainMenuManager.h"


// Sets default values
AMainMenuManager::AMainMenuManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainMenuManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMainMenuManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

bool AMainMenuManager::ChangeToGameLevelIfDataExists()
{
	//load from save 
	//if exists, load game-> jump to game level 
	//if not create game 
	UE_LOG(LogTemp,Warning,TEXT("Intro clicked call stack works!"))
	if(DataManager)
	{
	if (DataManager->GameSaveDataExists())
	{
		return true;
	}
	else
		return false;
	}
	return false;
}

