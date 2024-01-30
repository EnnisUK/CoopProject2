// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class CoopProject : ModuleRules
{
	public CoopProject(ReadOnlyTargetRules Target) : base(Target)
	{
	
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "AdvancedSessions", "AdvancedSteamSessions", "Niagara", "ApplicationCore", "SlateCore", "UniversalVoiceChatPro"});
        
		PrivateDependencyModuleNames.AddRange(new string[] { "OnlineSubsystem", "OnlineSubsystemUtils", "OnlineSubsystemSteam" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
