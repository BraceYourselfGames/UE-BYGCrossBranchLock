// Copyright Brace Yourself Games. All Rights Reserved.

#include "BYGCrossBranchLockModule.h"
#include "BYGCrossBranchLockSettings.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "ISettingsContainer.h"
#include "ISourceControlModule.h"
#include "ISourceControlProvider.h"

#define LOCTEXT_NAMESPACE "FBYGCrossBranchLockModule"

DEFINE_LOG_CATEGORY( LogBYGCrossBranchLock );

void FBYGCrossBranchLockModule::StartupModule()
{
	if ( ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>( "Settings" ) )
	{
		ISettingsContainerPtr SettingsContainer = SettingsModule->GetContainer( "Project" );
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings( "Project", "Plugins", "BYG Cross Branch Lock",
		                                                                        LOCTEXT( "RuntimeGeneralSettingsName", "BYG Cross Branch Lock" ),
		                                                                        LOCTEXT( "RuntimeGeneralSettingsDescription", "Warn when files are checked out in other branches." ),
		                                                                        GetMutableDefault<UBYGCrossBranchLockSettings>()
			);

		if ( SettingsSection.IsValid() )
		{
			SettingsSection->OnModified().BindRaw( this, &FBYGCrossBranchLockModule::HandleSettingsSaved );
		}
	}

	OnStateBranchConfigChanged();
}

void FBYGCrossBranchLockModule::ShutdownModule()
{
	if ( ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>( "Settings" ) )
	{
		SettingsModule->UnregisterSettings( "Project", "CustomSettings", "General" );
	}
}

bool FBYGCrossBranchLockModule::HandleSettingsSaved()
{
	OnStateBranchConfigChanged();
	return true;
}

void FBYGCrossBranchLockModule::OnStateBranchConfigChanged()
{
	ISourceControlModule& SourceControlModule = ISourceControlModule::Get();
	if ( SourceControlModule.IsEnabled() )
	{
		ISourceControlProvider& SourceControlProvider = SourceControlModule.GetProvider();
		if ( SourceControlProvider.GetName() == "Perforce" )
		{
			const UBYGCrossBranchLockSettings* Settings = GetDefault<UBYGCrossBranchLockSettings>();
			FString ContentDir = FPaths::ProjectContentDir();
			SourceControlProvider.RegisterStateBranches( Settings->BranchNames, Settings->ContentRoot );
		}
		else
		{
			UE_LOG( LogBYGCrossBranchLock, Warning, TEXT("BYG Cross Branch Locking only works with Perforce") );
		}
	}
	else
	{
		UE_LOG( LogBYGCrossBranchLock, Error, TEXT("Source Control Module is not enabled, cannot run BYG Cross Branch Locking") );
	}
	
}


#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE( FBYGCrossBranchLockModule, BYGCrossBranchLock )
