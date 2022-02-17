// Copyright Brace Yourself Games. All Rights Reserved.

#pragma once

#include "BYGCrossBranchLockSettings.generated.h"

UCLASS( config = Game, defaultconfig )
class UBYGCrossBranchLockSettings : public UObject
{
	GENERATED_BODY()

public:
	// Path to your project's content directory, relative to your Perforce root directory
	// e.g. MyProject/Content
	UPROPERTY( config, EditAnywhere, Category="Branch Setup" )
	FString ContentRoot;
	
	// Branch names of all the branches you want to check for locks
	// e.g. //depot/Development, //depot/SomeFeatureBranch
	UPROPERTY( config, EditAnywhere, Category="Branch Setup" )
	TArray<FString> BranchNames;
};
