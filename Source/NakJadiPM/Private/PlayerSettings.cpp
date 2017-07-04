// Fill out your copyright notice in the Description page of Project Settings.

#include "NakJadiPM.h"
#include "PlayerSettings.h"




UPlayerSettings::UPlayerSettings()
{
	SaveSlotName = TEXT("PlayerSettings");
	UserIndex = 0;

	SoundOn = true;
	MusicOn = true;
	Language = ELanguage::English;
}
