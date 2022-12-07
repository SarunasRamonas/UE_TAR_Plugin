// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "UE_TAR_PluginBPLibrary.generated.h"

/*
*	Function library class.
*	
*/
UCLASS()
class UUE_TAR_PluginBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetTextFromTarFile", Keywords = "GetTextFromTarFile"), Category = "Tar Plugin")
	static void GetTextFromTAR(FString TarFilename, FString TextFilename, FString &Text, bool &Found);
};
