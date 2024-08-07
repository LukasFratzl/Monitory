// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Monitory_ClientEditorTarget : TargetRules
{
	public Monitory_ClientEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		// bOverrideBuildEnvironment = true;
		ExtraModuleNames.Add("Monitory_Client");
	}
}
