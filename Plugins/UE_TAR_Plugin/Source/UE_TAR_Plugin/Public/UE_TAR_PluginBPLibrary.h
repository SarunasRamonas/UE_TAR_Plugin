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

	/**
	 * @brief 
	 * @param TarFilename 
	 * @param TextFilename 
	 * @param Text 
	 * @param Found 
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetTextFromTarFile", Keywords = "TarFileExtractor"), Category = "Tar Plugin")
	static void GetTextFromTAR(FString TarFilename, FString TextFilename, FString &Text, bool &Found);

	/**
	 * @brief 
	 * @param TarFilename 
	 * @param Text 
	 * @param Found 
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetFileNamesInTarFile", Keywords = "TarFileExtractor"), Category = "Tar Plugin")
	static void GetFilenamesInTAR(FString TarFilename, TArray<FString> &OutFileNames, bool &Found);
};
