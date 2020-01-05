#pragma once
#include <string>
#include <vector>
#include <windows.h>
#include <atlstr.h>
#include <math.h>
class GlobalVariables
{
public:
	GlobalVariables();
	~GlobalVariables();
	static void setTabIndex(int tab);
	static void setFolderChosen(int folder);
	static void setNumberOfFolders(int number);
	static void setThumbnail(std::string thumbnail);
	static void setProfileID(int id);
	static void setProgress(int id);
	static void setSavedProfileCancelled(bool status);
	static void setProfileSaved(std::string status);
	static void setProfileName(std::string name);
	static void setUsedOrNew(std::string uOrN);
	static void setLastProfileImageLine(std::string lastImageLine);
	static void setProfileImagesToDetectFace(std::vector<std::string> filesToSearch);
	static void setUserImagesToDetectFace(std::vector<std::string> filesToSearch);
	static void setUserImagesWithFaceDetected(std::vector<std::vector<std::string> > files);
	static void setImagesWithProfileFound(std::vector<std::vector<std::string> > containsProfileImages);
	static int getTabIndex();
	static int getFolderChosen();
	static int getreservedIDs();
	static std::string getThumbnail();
	static int getProfileID();
	static int getProgress();
	static int getNumberOfFolders();
	static bool getSaveProfileCancelled();
	static std::string getProfileSaved();
	static std::string getProfileName();
	static std::string getUsedOrNew();
	static std::string getLastProfileImageLine();
	static std::vector<std::string> getProfileImagesToDetectFace();
	static std::vector<std::string> getUserImagesToDetectFace();
	static std::vector<std::vector<std::string> > getUserImagesWithFaceDetected();
	static std::vector<std::vector<std::string> > getImagesWithProfileFound();
private:
	static int tabIndex;
	static std::string profileSaved;
	static bool saveProfileCancelled;
	static int progress;
	static int reservedIDs;
	static int numberOfFolders;
	static int folderChosen;
	static std::string thumbnailName;
	static int profileID;
	static std::string profileName;
	static std::string usedOrNew;
	static std::string lastProfileImageLine;
	//vectors that store image paths that create a user profile
	static std::vector<std::string> GlobalVariables::profileImagesToDetectFace;
	//vectors that store images paths that are then searched through to find if the profile is in them
	static std::vector<std::string> GlobalVariables::userImagesToDetectFace;
	//vector that stores the images that contain the profile
	static std::vector<std::vector<std::string> > GlobalVariables::imagesRecognisedAsProfile;
	//vector that stores the images that contain detected faces
	static std::vector<std::vector<std::string> > GlobalVariables::imagesWithFaceDetected;
};

