// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LunaEpoc : ModuleRules
{
	public LunaEpoc(ReadOnlyTargetRules target) : base(target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{   
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"NavigationSystem",
			"AIModule",
			"Niagara",
			"EnhancedInput",
            "GameplayAbilities",
            "Wwise",
            "AkAudio", 
            "WwiseSoundEngine"
        });

		PrivateDependencyModuleNames.AddRange(new string[]
		{   
			"GameplayTags",
			"GameplayTasks"
		});
	}
}
