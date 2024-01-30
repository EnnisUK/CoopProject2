// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class CoopProjectTarget : TargetRules
{
	public CoopProjectTarget(TargetInfo Target) : base(Target)
	{
			Type = TargetType.Game;
    		DefaultBuildSettings = BuildSettingsVersion.V3;
		    IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
    		ExtraModuleNames.Add("CoopProject");
		    bUsesSteam = true;
	}
}
