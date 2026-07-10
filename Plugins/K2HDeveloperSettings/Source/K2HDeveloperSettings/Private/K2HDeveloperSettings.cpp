// Copyright Epic Games, Inc. All Rights Reserved.

#include "K2HDeveloperSettings.h"

#define LOCTEXT_NAMESPACE "FK2HDeveloperSettingsModule"

void FK2HDeveloperSettingsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FK2HDeveloperSettingsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FK2HDeveloperSettingsModule, K2HDeveloperSettings)