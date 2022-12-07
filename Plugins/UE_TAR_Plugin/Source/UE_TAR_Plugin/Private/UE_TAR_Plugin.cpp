// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE_TAR_Plugin.h"

#define LOCTEXT_NAMESPACE "FUE_TAR_PluginModule"

void FUE_TAR_PluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
}

void FUE_TAR_PluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUE_TAR_PluginModule, UE_TAR_Plugin)