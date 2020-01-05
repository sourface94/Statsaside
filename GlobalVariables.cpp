#include "GlobalVariables.h"
#include <string>
#include <vector>
#include <windows.h>
#include <atlstr.h>
#include <math.h>

std::string profilesFileName = "profiles.txt";
std::string imageFilesFileName = "imageFiles.csv";
int GlobalVariables::tabIndex = 0;
int GlobalVariables::folderChosen = 0;
int GlobalVariables::progress = 1;
//one more than the 39 that are actually stored due to idexes starting at 0
int GlobalVariables::reservedIDs = 40;
int GlobalVariables::numberOfFolders = 1;
std::string GlobalVariables::thumbnailName = "";
int GlobalVariables::profileID = 0;
std::string GlobalVariables::profileSaved = "";
bool GlobalVariables::saveProfileCancelled = false;
std::string GlobalVariables::profileName = "";
std::string GlobalVariables::usedOrNew = "";
std::string GlobalVariables::lastProfileImageLine = "";
//vector that store image paths that create a user profile
std::vector<std::string> GlobalVariables::profileImagesToDetectFace;
//vectors that sotre images paths that are then searched through to find if the profile is in them
std::vector<std::string> GlobalVariables::userImagesToDetectFace;
std::vector<std::vector<std::string> > GlobalVariables::imagesRecognisedAsProfile;
//vector that stores the images that contain detected faces
std::vector<std::vector<std::string> > GlobalVariables::imagesWithFaceDetected;

GlobalVariables::GlobalVariables()
{
}

GlobalVariables::~GlobalVariables()
{
}

void GlobalVariables::setTabIndex(int tab) {
	tabIndex = tab;
}

void GlobalVariables::setNumberOfFolders(int number) {
	numberOfFolders = number;
}

void GlobalVariables::setFolderChosen(int folder) {
	folderChosen = folder;
}

void GlobalVariables::setProgress(int progressNumber) {
	progress = progressNumber;
}

void GlobalVariables::setThumbnail(std::string thumbnail) {
	thumbnailName = thumbnail;
}

void GlobalVariables::setProfileID(int id) {
	profileID = id;
}

void GlobalVariables::setProfileName(std::string name) {
	profileName = name;
}

void GlobalVariables::setProfileSaved(std::string status) {
	profileSaved = status;
}

void GlobalVariables::setSavedProfileCancelled(bool status) {
	saveProfileCancelled = status;
}

void GlobalVariables::setUsedOrNew(std::string uOrN) {
	usedOrNew = uOrN;
}

void GlobalVariables::setLastProfileImageLine(std::string lastImageLine) {
	lastProfileImageLine = lastImageLine;
}

void GlobalVariables::setProfileImagesToDetectFace(std::vector<std::string> filesToSearch) {
	profileImagesToDetectFace = filesToSearch;
}

void GlobalVariables::setUserImagesToDetectFace(std::vector<std::string> filesToSearch) {
	userImagesToDetectFace = filesToSearch;
}

void GlobalVariables::setUserImagesWithFaceDetected(std::vector<std::vector<std::string> > files) {
	imagesWithFaceDetected = files;
}

void GlobalVariables::setImagesWithProfileFound(std::vector<std::vector<std::string> > containsProfileImages) {
	imagesRecognisedAsProfile = containsProfileImages;
}

int GlobalVariables::getTabIndex() {
	return tabIndex;
}

int GlobalVariables::getNumberOfFolders() {
	return numberOfFolders;
}

int GlobalVariables::getProgress() {
	return progress;
}

int GlobalVariables::getFolderChosen() {
	return folderChosen;
}

int GlobalVariables::getreservedIDs(){
	return reservedIDs;
}

std::string GlobalVariables::getThumbnail() {
	return thumbnailName;
}

int GlobalVariables::getProfileID() {
	return profileID;
}

std::string GlobalVariables::getProfileName() {
	return profileName;
}

std::string GlobalVariables::getProfileSaved() {
	return profileSaved;
}

bool GlobalVariables::getSaveProfileCancelled() {
	return saveProfileCancelled;
}

std::string GlobalVariables::getUsedOrNew() {
	return usedOrNew;
}

std::string GlobalVariables::getLastProfileImageLine() {
	return lastProfileImageLine;
}

std::vector<std::string> GlobalVariables::getProfileImagesToDetectFace() {
	return profileImagesToDetectFace;
}

std::vector<std::string> GlobalVariables::getUserImagesToDetectFace() {
	return userImagesToDetectFace;
}

std::vector<std::vector<std::string> > GlobalVariables::getUserImagesWithFaceDetected() {
	return imagesWithFaceDetected;
}

std::vector<std::vector<std::string> > GlobalVariables::getImagesWithProfileFound() {
	return imagesRecognisedAsProfile;
}