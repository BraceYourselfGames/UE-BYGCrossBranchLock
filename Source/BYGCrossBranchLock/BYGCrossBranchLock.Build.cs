// Copyright Brace Yourself Games. All Rights Reserved.

using UnrealBuildTool;

public class BYGCrossBranchLock : ModuleRules
{
	public BYGCrossBranchLock(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			}
			);
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"SourceControl",
			}
			);
	}
}
