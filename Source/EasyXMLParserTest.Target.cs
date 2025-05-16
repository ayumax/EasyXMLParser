// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class EasyXMLParserTestTarget : TargetRules
{
	public EasyXMLParserTestTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		CppStandard = CppStandardVersion.Latest;

		ExtraModuleNames.AddRange( new string[] { "EasyXMLParserTest" } );
	}
}
