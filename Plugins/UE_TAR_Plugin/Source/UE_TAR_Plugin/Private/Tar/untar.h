#pragma once
/**
*
* @brief To simplify the extraction of TAR files into a stream in memory.
* @author Sarunas Ramonas
* @version 0.0.1
* @date  2022
* @description based on Alexis Paques https://https://github.com/AlexisTM/untar
*
*/


#include <stdio.h>
#include <tchar.h>
#include <fstream>
#include <string>
#include <map>
#include <ios>

namespace UnTar {
	
	using namespace std;

	// Type of file in the TAR documentation
	enum tarEntryType {
		FileCompatibilityType = '\0',
		FileType = '0',
		HardlinkType = '1',
		SymlinkType,
		CharacterDeviceType,
		BlockDeviceType,
		DirType,
		FifoType,
		ReservedType,
		OtherType
	};

	// Limit entries to Files or Dir to limit the map size
	enum tarMode {
		File = 1,
		Hardlink = 2,
		Symlink = 4,
		CharacterDevice = 8,
		BlockDevice = 16,
		Dir = 32,
		Fifo = 64,
		Reserved = 128,
		All = 255
	};

	// The tarEntry class represents an ENTRY inside a TAR file. It can be a File, Dir, Symlink, ... Important parts to be able to use it : 
	// tarEntry::tarEntry(string filename, int filesize, size_t startOfFile, tarEntryType type, string parentTarFilename, ifstream * _tarfile);
	// ifstream * tarEntry::wantToExtract(int * filesize, size_t * startInMemory);
	// string getFilename();
	// size_t getStartingByte();
	class tarEntry {
		friend class tarFile;
	public :
		// To be able to create null tarEntry
		tarEntry();
		// Default constructor, prefer this one
		tarEntry(string filename, int filesize, size_t startOfFile, tarEntryType type, string parentTarFilename, ifstream * _tarfile);
		// Constructor to avoid error for people who failed the instantiation. Could disapear when I will have properly documented the library.
		tarEntry(tarEntry const & cpy);
		// Destructor
		~tarEntry();
		// Get the tar filename where this file comes from
		string getParentFilename();
		// Get the file size
		int getFileSize();
		// Get the filename (containing the path)
		string getFilename();
		// Get the starting byte in the stream
		size_t getStartingByte();
		// Get the tar type. Is it a DirType, FileType, SymlinkType ?
		tarEntryType getType();
		// Get all usefull data we need to extract our data in one call
		ifstream * tarEntry::wantToExtract(int * filesize, size_t * startInMemory);

	private:
		// The stream, this is the same as the one of the tarFile object. Opened by default.
		std::ifstream * _tarfile;
		// If the file is extacted, set to true.
		// For future usage, in my project in SFML
		bool _extracted;
		// Starting byte in the tar file (stream)
		size_t _startOfFile;
		// Filesize
		int _filesize;
		// Filename (containing the path)
		string _filename;
		// Type of the entry
		tarEntryType _type;
		// What is my dad TAR ?
		string  _parentTarFilename;
	};
	
	// tarFile represents a TAR FILE opened. Important parts to be able to use it : 
	// tarFile::tarFile(char * filename, int filter = All);
	// static map<string, tarEntry *> tarFile::entries
	class tarFile {
		friend class tarEntry;
	public:
		// If you don't give a filename, don't forget to initiate via tarFile::open(...)  
		tarFile();
		// Default initiation
		tarFile(char * filename, int filter = All);
		// The destructor 
		~tarFile();

		// Open a file in case you didn't instanciated the class with a filename
		void open(char * filename, int filter = All);
		// Get the filename of the opened file
		string getFilename();
		// Map of tarEntries, containing all the files
		// TODO 
		// Put entries as private and wrap the find function in the class
		static map<string, tarEntry *> entries;
		// This is the tar filestream
		static std::ifstream _tarfile;

	private:
		// Read the file and store entries
		void getAllEntries(int filter = All);
		// Add a new tarEntry into the map (entries)
		void addEntryToMap(string filename, int filesize, tarEntryType type);
		// Check if the header is Null. The tar file ends on two Null headers
		bool isNullHeader(const char *p);
		// Verify the checksum, actually, it stops the reading on error
		static int verifyChecksum(const char *p);
		// Used to read the header
		static int parseoct(const char *p, size_t n);
		// Did we get entries ? If yes, don't get them again
		bool _get_all_entries;
		// Remember where comes the data form
		char * _filename;
	};

}

