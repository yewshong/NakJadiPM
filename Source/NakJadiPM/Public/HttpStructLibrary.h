// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "HttpStructLibrary.generated.h"

USTRUCT()
struct FRequest_Login {
	GENERATED_BODY()
		UPROPERTY() FString email;
	UPROPERTY() FString password;

	FRequest_Login() {}
};

USTRUCT()
struct FResponse_Login {
	GENERATED_BODY()
		UPROPERTY() int id;
	UPROPERTY() FString email;
	UPROPERTY() FString name;
	UPROPERTY() FString hash;

	FResponse_Login() {}
};


UCLASS()
class NAKJADIPM_API AHttpStructLibrary : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHttpStructLibrary();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
