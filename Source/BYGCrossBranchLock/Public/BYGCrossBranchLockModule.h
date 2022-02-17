// Copyright Brace Yourself Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogBYGCrossBranchLock, Log, All);

class FBYGCrossBranchLockModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
protected:
	bool HandleSettingsSaved();

	void OnStateBranchConfigChanged();
};
