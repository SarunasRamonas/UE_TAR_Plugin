// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE_TAR_PluginBPLibrary.h"
#include "Tar/untar.h"

using namespace untar;

UUE_TAR_PluginBPLibrary::UUE_TAR_PluginBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	
}

void UUE_TAR_PluginBPLibrary::GetTextFromTAR(FString TarFilename, FString TextFilename, FString& Text, bool& Found)
{
	FString Result = TEXT("");
	
	char* FilenameInChar =TCHAR_TO_ANSI(*TarFilename);
	const untar::tarFile* TarFile = new untar::tarFile(FilenameInChar, untar::File);
	
	auto it = TarFile->entries.find(string(TCHAR_TO_UTF8(*TextFilename)));
	
	if (it != TarFile->entries.end())
	{
		Found = true;
		untar::tarEntry * data = it->second;
		// Get the ifstream, startbyte and filesize in one call
		size_t start;
		int filesize;
		std::ifstream * _tarfile = data->wantToExtract(&filesize, &start);

		// CARE THE OVERFLOW, ALWAYS
		char dataoutput[500];

		// always be sure the file is open before trying to read. Else we got shitty random data.
		if(_tarfile->is_open()){

			// Go to the beginning of the file and read the whole file
			_tarfile->seekg(data->getStartingByte(), ios_base::beg);

			// Read the data
			_tarfile->read(dataoutput, filesize);
			
			const string stringResult = string(dataoutput,filesize);
			Result = stringResult.c_str();
		}
	}
	else
	{
		Found = false;
	}
	Text = Result;

	delete(TarFile);
}
