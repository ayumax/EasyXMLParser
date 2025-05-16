// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EasyXMLParser : ModuleRules
{
	public EasyXMLParser(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		CppStandard = CppStandardVersion.Latest;
		bEnableExceptions = true;

		PublicDependencyModuleNames.Add("Core");
		
		PrivateDependencyModuleNames.AddRange(new string[]{
			"CoreUObject",
			"Engine",
			"Slate",
			"SlateCore",
			"XmlParser"
		});
	}
}
