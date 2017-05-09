// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class NakJadiPM : ModuleRules
{
	public NakJadiPM(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Slate", "SlateCore" });

        //PrivateDependencyModuleNames.AddRange(new string[] {  });

        //Uncomment if you are using Slate UI
        //PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");
        DynamicallyLoadedModuleNames.Add("OnlineSubsystemNull");

        //added to support http get from php
        PrivateDependencyModuleNames.AddRange(new string[] { "Http", "Json", "JsonUtilities" });

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            // DynamicallyLoadedModuleNames.Add("OnlineSubsystemGooglePlay");

            //PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "OnlineSubsystem", "AndroidAdvertising","OnlineSubsystemGooglePlay" });

            PrivateDependencyModuleNames.Add("OnlineSubsystem");
            PrivateDependencyModuleNames.Add("OnlineSubsystemGooglePlay");
        }
    }
}
