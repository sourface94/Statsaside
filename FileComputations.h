#pragma once
#ifndef FILECOMPUTATIONS_H
#define FILECOMPUTATIONS_H
#include <string>
#include <vector>

using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
class FileComputations
{
public:
	FileComputations();
	~FileComputations();

	static inline std::string trim(std::string &s);
	static bool deleteFiles(const std::vector<std::string> &filePaths);
	static void uploadProfileToFile(std::string filename, std::string profilename);
	static int getLastIdFromFile(std::string filename);
	static bool searchProfile(System::String^ profileName);
	static bool isBoxEmpty(TextBox^ box);
	static void split(const std::string &s, char delim, std::vector<std::string> &elems);
	static std::vector<std::string> split(const std::string &s, char delim);
	static bool copyFile(const char *SRC, const char* DEST);
	static bool saveProfile(TextBox^ textBox);
	static bool checkFileExistence(std::string file);
	static bool moveFiles(const std::vector<std::string> &oldFilePaths, const std::vector<std::string> &newFilePaths);
	static bool createFolderAndMove(const std::vector<std::string> &filePaths, std::string folderName);
	static std::vector<std::string> getFilesFromFolder(const std::string &folderPath);
	static std::vector<std::string> FileComputations::getImagesFilesFromHome();
	static bool hasSuffix(const std::string &str, const std::string &suffix);
	static bool saveThumbnail();
	static std::string getSuffix(const std::string &filePath);
	static std::string getAppDataFolder();
private:
	static std::wstring s2ws(const std::string& str);
	static std::string ws2s(const std::wstring& wstr);
};
#endif
