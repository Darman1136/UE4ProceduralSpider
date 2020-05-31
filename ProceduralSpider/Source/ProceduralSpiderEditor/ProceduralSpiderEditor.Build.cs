// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProceduralSpiderEditor : ModuleRules
{
	public ProceduralSpiderEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
            new string[]
            {
                "ProceduralSpiderEditor/Public"
            });

        PrivateIncludePaths.AddRange(
            new string[] 
            {
				"ProceduralSpiderEditor/Private"
			});
			
		PublicDependencyModuleNames.AddRange(
		new string[] 
			{ 
				"ProceduralSpider"
			});
			
		PrivateDependencyModuleNames.AddRange(
            new string[] 
            {
				"UnrealEd", "Engine", "Core", "CoreUObject"
            });

        PrivateIncludePathModuleNames.AddRange(
            new string[]
            {
            });

        DynamicallyLoadedModuleNames.AddRange(
            new string[] 
            {
            });
	}
}
