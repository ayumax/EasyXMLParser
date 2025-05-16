// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class EasyXMLParserTestEditorTarget : TargetRules
{
	public EasyXMLParserTestEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		CppStandard = CppStandardVersion.Latest;

		ExtraModuleNames.AddRange( new string[] { "EasyXMLParserTest" } );
	}
}
