// Fill out your copyright notice in the Description page of Project Settings.

#include "NakJadiPM.h"
#include "ElectionDataManager.h"


// Sets default values
AElectionDataManager::AElectionDataManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AElectionDataManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AElectionDataManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

