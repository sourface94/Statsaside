#include <stdio.h>
#include <direct.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <shlobj.h>
#include <algorithm> //for std::transform 
#include <functional> 
#include <cctype>
#include <locale>    // std::wstring_convert
#include <codecvt>		// std::codecvt_utf8
#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>
#include "FacialComputations.h"
#include "GlobalVariables.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace std;
#ifndef UNICODE  
typedef std::string String;
#else
typedef std::wstring String;
#endif
#ifdef UNICODE
typedef wchar_t TCHAR;
#else
typedef unsigned char TCHAR;
#endif
#include <windows.h>
#include "FileComputations.h"

using namespace std;

FileComputations::FileComputations()
{
}

FileComputations::~FileComputations()
{
}
// trim from start
static inline std::string &ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
		std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(),
		std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

// trim from both ends
std::string FileComputations::trim(std::string &s) {
	return ltrim(rtrim(s));
}

bool FileComputations::deleteFiles(const std::vector<std::string> &filePaths) {
	bool success;
	try {
		//for each file path, delete the file
		for (int i = 0; i < filePaths.size(); i++) {
			remove(filePaths[i].c_str());
		}
		success = true;
	}
	catch (exception e) {
		success = false;
	}
	return success;
}

bool FileComputations::moveFiles(const std::vector<std::string> &oldFilePaths, const std::vector<std::string> &newFilePaths) {
	bool success;
	try {
		//for each file name move it to its new location
		for (int i = 0; i < oldFilePaths.size(); i++) {
			rename(oldFilePaths[i].c_str(), newFilePaths[i].c_str());
		}
		success = true;
	}
	catch (exception e) {
		success = false;
	}
	return success;
}

void FileComputations::uploadProfileToFile(string fileName, std::string profileName)
{
	int next_id = getLastIdFromFile(fileName) + 1; // calculate what the next id should be
	char filechar[1024];
	strcpy_s(filechar, profileName.c_str()); // create a char 'filechar' then copy the filename into it
	if (checkFileExistence(fileName)) {// check if the file exists if so find the last id
		std::ofstream my_file;
		my_file.open(fileName, std::ios::app);
		my_file.seekp(0, std::ios::end); //to ensure the put pointer is at the end
		my_file << "\n" << filechar << ";" << next_id;
	}
	else {   //if the file does not exist set the id to '0'
		std::ofstream my_file;
		my_file.open(fileName, std::ios::app);
		my_file.seekp(0, std::ios::end); //to ensure the put pointer is at the end
		my_file << filechar << ";" << 0;
	}
}

bool FileComputations::saveProfile(TextBox^ textBox)
{

	int profileId;

	if (FileComputations::isBoxEmpty(textBox)) {// checks that the user has typed a name in the saveTextbox
		MessageBox::Show("Please choose a name", "Invalid name", MessageBoxButtons::OK);
		return false;
	}
	else {
		// change profileName variable to string
		string pname;
		System::String ^ profileName = textBox->Text;// retrieve text from TextBox

		pname = msclr::interop::marshal_as<std::string>(profileName);
		trim(pname);
		char filechar[1024];
		strcpy_s(filechar, pname.c_str());
		if (FileComputations::searchProfile(profileName)) { // search if the profile name has already been taken
			MessageBox::Show("This profile name already exists",
				"Save Profile", MessageBoxButtons::OK); // message box displayed if prolile name has been taken
			return false;
		}
		else {
			if (FileComputations::checkFileExistence("profiles.txt")) { //check if the profiles text file exists
				// if the profile file exists calculate next id, add it to the profile name, then save
				profileId = FileComputations::getLastIdFromFile("profiles.txt") + 1; // caclulate what the next id should be
				std::ofstream my_file;
				my_file.open("profiles.txt", std::ios::app);
				my_file.seekp(0, std::ios::end); //to ensure the put pointer is at the end
				my_file << "\n" << filechar << ";" << profileId;
			}
			else {
				//if the profile file does not exist then the id will be '0', add it to the profile name, then save
				profileId = 0;
				std::ofstream my_file;
				my_file.open("profiles.txt", std::ios::app);
				my_file.seekp(0, std::ios::end); //to ensure the put pointer is at the end
				my_file << filechar << ";" << profileId;
			}
			GlobalVariables::setProfileID(profileId);
			GlobalVariables::setProfileName(pname);  //save the profile name as a global variable


			//CREATES PROFILE IN THE FACE RECOGNIZER
			vector<string> imagesToDetectFace = GlobalVariables::getProfileImagesToDetectFace();
			vector<vector<string> > imagesWithFaceDetected = FacialComputations::detectAndSaveFace(imagesToDetectFace, pname, profileId, "");
			FacialComputations::addImageToModel(imagesWithFaceDetected, profileId);
			FileComputations::saveThumbnail(); // save the thumbnail to thumbnail folder
			GlobalVariables::setProfileSaved("Yes");
			MessageBox::Show("Profile has been saved", "Save Profile", MessageBoxButtons::OK);
			return true;
		}
	}

}

// checks if a file exist
bool FileComputations::checkFileExistence(string file)
{
	std::ifstream my_file(file);
	if (my_file) {
		return true;
	}
	return false;

}

int FileComputations::getLastIdFromFile(std::string fileName)
{
	int idint = -1;
	string filename = fileName;
	ifstream fin;
	fin.open(filename);
	if (fin.is_open()) {
		fin.seekg(-1, ios_base::end);                // go to one spot before the EOF (end of file)
		bool keepLooping = true;
		while (keepLooping) {
			char ch;
			fin.get(ch);                            // Get current byte's data
			if ((int)fin.tellg() <= 1) {             // If the data was at or before the 0th byte
				fin.seekg(0);                       // The first line is the last line
				keepLooping = false;                // So stop there
			}
			else if (ch == '\n') {                   // If the data was a newline
				keepLooping = false;                // Stop at the current position.
			}
			else {                                  // If the data was neither a newline nor at the 0 byte
				fin.seekg(-2, ios_base::cur);        // Move to the front of that data, then to the front of the data before it
			}
		}
		string lastLine, filepath, id;
		getline(fin, lastLine);                      // Read the current line
		stringstream liness(lastLine);
		getline(liness, filepath, ';');
		getline(liness, id);
		idint = atoi(id.c_str());
		fin.close();
	}
	return idint;
}

bool FileComputations::searchProfile(System::String^ profileName)
{
	string pname;
	pname = msclr::interop::marshal_as<std::string>(profileName);
	Boolean found = false;
	string line;
	size_t pos;
	std::ifstream my_file;
	my_file.open("profiles.txt");
	while (my_file.good()) 	{

		getline(my_file, line); // get line from file					  
		vector<string> profileName = split(line, ';');
		if (profileName[0] == pname)
		{
			found = true;
			break;
		}

	}

	return found;

}

void FileComputations::split(const string &s, char delim, vector<string> &elems) {
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
}

vector<string> FileComputations::split(const string &s, char delim) {
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}

bool FileComputations::isBoxEmpty(TextBox^ box)
{
	if (box->Text->Length == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool FileComputations::copyFile(const char *SRC, const char* DEST)
{
	std::ifstream src(SRC, std::ios::binary);
	std::ofstream dest(DEST, std::ios::binary);
	dest << src.rdbuf();
	return src && dest.good(); // return true if file has been copied
}

bool FileComputations::createFolderAndMove(const std::vector<std::string> &filePaths, std::string folderName) {

	bool success;
	TCHAR appData[MAX_PATH];
	//find path of the users desktop
	try {
		if (SUCCEEDED(SHGetFolderPath(NULL,
			CSIDL_DESKTOPDIRECTORY | CSIDL_FLAG_CREATE,
			NULL,
			SHGFP_TYPE_CURRENT,
			appData)))
			;
		//create a folder on the users desktop
		folderName = "\\" + folderName;
		//String folderPathString = String(appData);
		//std::string folderPath = msclr::interop::marshal_as<std::string>(folderPathString);
		//folderPath += folderName;
		string folderPath = ws2s(appData);
		folderPath += folderName;
		_mkdir(folderPath.c_str());

		//for each file name move it to the newly created folder on the desktop
		for (int i = 0; i < filePaths.size(); i++) {
			//create new file path
			string oldPath = filePaths[i];
			size_t pos = oldPath.find_last_of('\\');
			string fileName = "\\" + oldPath.substr(pos + 1);
			string newPath = folderPath + fileName;
			//move file
			rename(oldPath.c_str(), newPath.c_str());
		}
		success = true;
	}
	catch (exception e) {
		success = false;
	}
	return success;
}

vector<string> FileComputations::getFilesFromFolder(const std::string &folderPath) {
	//vector that contains all file from the folder
	vector<string> fileNames;
	//vector that only contains the image files from the folder
	vector<string> imageFileNames;
	string directoryPathStdString = folderPath + "\\*.*";
	wstring stemp = s2ws(directoryPathStdString);
	LPCWSTR directoryPath = stemp.c_str();
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile(directoryPath, &FindFileData);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (FindFileData.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
			{
				std::wstring ws(FindFileData.cFileName);
				string fileName = ws2s(ws);
				fileNames.push_back(fileName);
			}
		} while (FindNextFile(hFind, &FindFileData));

		FindClose(hFind);
	}
	for (size_t i = 0; i < fileNames.size(); i++) {
		if (hasSuffix(fileNames[i], "jpg") == true || hasSuffix(fileNames[i], "jpeg") == true || hasSuffix(fileNames[i], "jpe") == true ||
			hasSuffix(fileNames[i], "jp2") == true || hasSuffix(fileNames[i], "png") == true || hasSuffix(fileNames[i], "bmp") == true ||
			hasSuffix(fileNames[i], "dib") == true || hasSuffix(fileNames[i], "pbm") == true || hasSuffix(fileNames[i], "pgm") == true ||
			hasSuffix(fileNames[i], "ppm") == true || hasSuffix(fileNames[i], "sr") == true || hasSuffix(fileNames[i], "ras") == true ||
			hasSuffix(fileNames[i], "tiff") == true || hasSuffix(fileNames[i], "tif") == true ||
			hasSuffix(fileNames[i], "JPG") == true || hasSuffix(fileNames[i], "JPEG") == true || hasSuffix(fileNames[i], "JPE") == true ||
			hasSuffix(fileNames[i], "JP2") == true || hasSuffix(fileNames[i], "PNG") == true || hasSuffix(fileNames[i], "BMP") == true ||
			hasSuffix(fileNames[i], "DIB") == true || hasSuffix(fileNames[i], "PBM") == true || hasSuffix(fileNames[i], "PGM") == true ||
			hasSuffix(fileNames[i], "PPM") == true || hasSuffix(fileNames[i], "SR") == true || hasSuffix(fileNames[i], "RAS") == true ||
			hasSuffix(fileNames[i], "TIFF") == true || hasSuffix(fileNames[i], "TIF") == true)
			imageFileNames.push_back(fileNames[i]);
	}
	return imageFileNames;
}

string FileComputations::getAppDataFolder(){
	TCHAR appData[MAX_PATH];
	//find path of the users desktop
	try {
		if (SUCCEEDED(SHGetFolderPath(NULL,
			CSIDL_APPDATA | CSIDL_FLAG_CREATE,
			NULL,
			0,
			appData)))
			;

		string folderPath = ws2s(appData);
		folderPath += "\\Face Finder\\";
		//_mkdir(folderPath.c_str());
		//string filePath = folderPath + "test.txt";
		//std::ofstream file(filePath); //open in constructor
		//std::string data("data to write to file");
		//file << data;
		return folderPath;
	}
	catch (exception e) {
		return NULL;
	}
}

vector<string> FileComputations::getImagesFilesFromHome() {
	//vector that contains all file from the folder
	vector<string> fileNames;
	//vector that only contains the image files from the folder
	vector<string> imageFileNames;
	string directoryPathStdString = "*.*";
	wstring stemp = s2ws(directoryPathStdString);
	LPCWSTR directoryPath = stemp.c_str();
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile(directoryPath, &FindFileData);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (FindFileData.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
			{
				std::wstring ws(FindFileData.cFileName);
				string fileName = ws2s(ws);
				fileNames.push_back(fileName);
			}
		} while (FindNextFile(hFind, &FindFileData));

		FindClose(hFind);
	}
	for (size_t i = 0; i < fileNames.size(); i++) {
		if (hasSuffix(fileNames[i], "pgm") == true ||hasSuffix(fileNames[i], "PGM") == true)
			imageFileNames.push_back(fileNames[i]);
	}
	return imageFileNames;
}

bool FileComputations::hasSuffix(const std::string &str, const std::string &suffix)
{
	return str.size() >= suffix.size() &&
		str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

wstring FileComputations::s2ws(const std::string& str)
{
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.from_bytes(str);
}

string FileComputations::ws2s(const std::wstring& wstr)
{
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.to_bytes(wstr);
}

bool FileComputations::saveThumbnail() {
	System::String^ Destination = "thumbnails\\";
	System::String^ fileExtension;
	string filename = GlobalVariables::getThumbnail();
	fileExtension = msclr::interop::marshal_as<System::String^>(FileComputations::getSuffix(filename));
	char filechar[1024];
	strcpy_s(filechar, filename.c_str());
	System::String^ lastid = FileComputations::getLastIdFromFile("profiles.txt").ToString();// get the last id and convert it to string
	Destination = Destination + "\\" + lastid + "." + fileExtension; // and the name of the file and its file extension to the destination filepath
	string destName = msclr::interop::marshal_as<std::string>(Destination);
	char destChar[1024];
	strcpy_s(destChar, destName.c_str());// copy the destination name into char format
	return FileComputations::copyFile(filechar, destChar);// copy file to the destination
}

string FileComputations::getSuffix(const std::string &filePath) {
	string suffix;
	int pos = filePath.find_last_of('.') + 1;
	suffix = filePath.substr(pos);
	return suffix;
}