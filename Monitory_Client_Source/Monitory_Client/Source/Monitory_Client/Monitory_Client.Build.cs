// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Monitory_Client : ModuleRules
{
	public Monitory_Client(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore" ,
			"UMG", 
			"UMGSpline",
			"SlateCore",
			"Slate",
			"Sockets",
			"Networking",
			"HTTP",
			"MediaAssets"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"Sockets",
			"Networking",
			"HTTP",
			"UMG",
			"SlateCore",
			"Slate",
			"GeometryCore"

		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
