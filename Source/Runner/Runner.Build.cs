// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Runner : ModuleRules
{
	public Runner(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Runner",
			"Runner/Variant_Platforming",
			"Runner/Variant_Platforming/Animation",
			"Runner/Variant_Combat",
			"Runner/Variant_Combat/AI",
			"Runner/Variant_Combat/Animation",
			"Runner/Variant_Combat/Gameplay",
			"Runner/Variant_Combat/Interfaces",
			"Runner/Variant_Combat/UI",
			"Runner/Variant_SideScrolling",
			"Runner/Variant_SideScrolling/AI",
			"Runner/Variant_SideScrolling/Gameplay",
			"Runner/Variant_SideScrolling/Interfaces",
			"Runner/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
