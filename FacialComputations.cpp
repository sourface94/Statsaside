#include "FacialComputations.h"
#include "GlobalVariables.h"
#include "FileComputations.h"
#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <atlstr.h>
#include <math.h>

using namespace cv;
using namespace std;

//size of all images to be trained and recognised with cv::FaceRecognizer
static const int imgRows = 100;
static const int imgCols = 100;

FacialComputations::FacialComputations()
{
}

FacialComputations::~FacialComputations()
{
}
void FacialComputations::prepareListViewVariables(){
	vector<vector<string> > imagesWithFacesDetected;
	vector<string> imagesToSearchForFaces = GlobalVariables::getUserImagesToDetectFace();
	int progress = 1;
	for (int i = 0; i < imagesToSearchForFaces.size(); i++)
	{
		vector<vector<string> > detectedFaces = FacialComputations::detectFacesToFindPersonNoLoop(imagesToSearchForFaces[i], i);
		if (detectedFaces.size() > 0) { imagesWithFacesDetected.push_back(detectedFaces[0]); }

		float percentage = (static_cast<float> (progress) / static_cast<float> (imagesToSearchForFaces.size())) * 100.0;
		GlobalVariables::setProgress(round(percentage));
		progress++;

	}
	GlobalVariables::setUserImagesWithFaceDetected(imagesWithFacesDetected);
	GlobalVariables::setProgress(100);
}
//Used to to detect the faces in an image for a specific person. The images are then saved
vector<vector<string> > FacialComputations::detectAndSaveFace(const vector<string> &filePaths, const string &name, const int &label, string lastLine) {
	vector<vector<string> > detectedPaths;
	string fn_haar = "haarcascade_frontalface_alt.xml";
	CascadeClassifier haar_cascade;
	haar_cascade.load(fn_haar);
	bool lastLineUsed = false;
	Mat resizedFace;
	resizedFace.rows = imgRows;
	resizedFace.cols = imgCols;

	//Get image
	for (int i = 0; i < filePaths.size(); i++) {
		Mat image = imread(filePaths[i], CV_LOAD_IMAGE_COLOR);
		//Make image greyscale
		Mat gray;
		cvtColor(image, gray, CV_BGR2GRAY);

		//Detect faces in image
		vector< Rect_<int> > faces;
		haar_cascade.detectMultiScale(gray, faces, 1.05, 5, 0, cv::Size(20, 20));

		//if faces are found in image
		if (faces.size() != 0) {
			//if one face is found in image
			if (faces.size() == 1) {
				Mat face = gray(faces[0]);
				string fileName = "";
				if (lastLine.empty())
				{
					int filenumber = label;
					stringstream ssfn;
					ssfn << filenumber << "_" << i << ".pgm";
					fileName = ssfn.str();
				}
				string appFolder = FileComputations::getAppDataFolder();
				fileName = appFolder + fileName;
				//resize and save the image
				resize(face, resizedFace, resizedFace.size(), 0, 0, INTER_AREA);
				//equalizeHist(resizedFace, resizedFace);
				Ptr<CLAHE> clahe = createCLAHE(4);
				clahe->apply(resizedFace, resizedFace);
				resizedFace = rotateFace(resizedFace);
				imwrite(fileName, resizedFace);
				vector<string> row;
				//Add an element (column) to the row
				row.push_back(fileName);
				row.push_back(filePaths[i]);
				detectedPaths.push_back(row);
			}
			// if more than one face is found in image
			else {
				for (size_t j = 0; j < faces.size(); j++)
				{
					Mat face = gray(faces[j]);
					//check if face is the intended person
					if (isPerson(face, name)) {
						string fileName = "";
						if (lastLine.empty())
						{
							int filenumber = label;
							stringstream ssfn;
							ssfn << filenumber << "_" << i << ".pgm";
							fileName = ssfn.str();
						}
						string appFolder = FileComputations::getAppDataFolder();
						fileName = appFolder + fileName;
						//resize and save the image
						resize(face, resizedFace, resizedFace.size(), 0, 0, INTER_AREA);
						Ptr<CLAHE> clahe = createCLAHE(4);
						clahe->apply(resizedFace, resizedFace);
						resizedFace = rotateFace(resizedFace);
						imwrite(fileName, resizedFace);
						vector<string> row;
						//Add an element (column) to the row
						row.push_back(fileName);
						row.push_back(filePaths[i]);
						detectedPaths.push_back(row);
						break;
					}
				}
			}
		}
	}
	return detectedPaths;
}

vector<vector<string> > FacialComputations::detectFacesToFindPerson(const vector<string> &filePaths) {
	vector<vector<string> > detectedPaths;
	string fn_haar = "haarcascade_frontalface_alt.xml";
	CascadeClassifier haar_cascade;
	haar_cascade.load(fn_haar);
	Mat resizedFace;
	resizedFace.rows = imgRows;
	resizedFace.cols = imgCols;

	//Get image
	for (int i = 0; i < filePaths.size(); i++) {
		Mat image = imread(filePaths[i], CV_LOAD_IMAGE_COLOR);
		//Make image greyscale
		Mat gray;
		cvtColor(image, gray, CV_BGR2GRAY);

		//Detect faces in image
		vector< Rect_<int> > faces;
		haar_cascade.detectMultiScale(gray, faces, 1.05, 5, 0, cv::Size(20, 20));

		//if faces are found in image
		if (faces.size() != 0) {
			//if one face is found in image
			if (faces.size() == 1) {
				Mat face = gray(faces[0]);
				string fileName = "";
				int filenumber = i;
				stringstream ssfn;
				ssfn << filenumber << ".pgm";
				fileName = ssfn.str();
				string appFolder = FileComputations::getAppDataFolder();
				fileName = appFolder + fileName;
				//resize and save the image
				resize(face, resizedFace, resizedFace.size(), 0, 0, INTER_AREA);
				Ptr<CLAHE> clahe = createCLAHE(4);
				clahe->apply(resizedFace, resizedFace);
				resizedFace = rotateFace(resizedFace);
				imwrite(fileName, resizedFace);
				vector<string> row;
				//Add an element (column) to the row
				row.push_back(fileName);
				row.push_back(filePaths[i]);
				detectedPaths.push_back(row);
			}
			// if more than one face is found in image
			else {
				for (size_t j = 0; j < faces.size(); j++)
				{
					Mat face = gray(faces[j]);
					//check if face is the intended person
					string fileName = "";
					int filenumber = i;
					stringstream ssfn;
					ssfn << filenumber << "_" << j << ".pgm";
					fileName = ssfn.str();
					string appFolder = FileComputations::getAppDataFolder();
					fileName = appFolder + fileName;
					//resize and save the image
					resize(face, resizedFace, resizedFace.size(), 0, 0, INTER_AREA);
					Ptr<CLAHE> clahe = createCLAHE(4);
					clahe->apply(resizedFace, resizedFace);
					resizedFace = rotateFace(resizedFace);
					imwrite(fileName, resizedFace);
					vector<string> row;
					//Add an element (column) to the row
					row.push_back(fileName);
					row.push_back(filePaths[i]);
					detectedPaths.push_back(row);
				}
			}
		}
	}
	return detectedPaths;
}

vector<vector<string> > FacialComputations::detectFacesToFindPersonNoLoop(string filePath, int loopIter) {
	vector<vector<string> > detectedPaths;
	string fn_haar = "haarcascade_frontalface_alt.xml";
	CascadeClassifier haar_cascade;
	haar_cascade.load(fn_haar);
	Mat resizedFace;
	resizedFace.rows = imgRows;
	resizedFace.cols = imgCols;

	//Get image
	Mat image = imread(filePath, CV_LOAD_IMAGE_COLOR);
	//Make image greyscale
	Mat gray;
	cvtColor(image, gray, CV_BGR2GRAY);

	//Detect faces in image
	vector< Rect_<int> > faces;
	haar_cascade.detectMultiScale(gray, faces, 1.05, 5, 0, cv::Size(20, 20));

	//if faces are found in image
	if (faces.size() != 0) {
		//if one face is found in image
		if (faces.size() == 1) {
			Mat face = gray(faces[0]);
			string fileName = "";
			int filenumber = loopIter;
			stringstream ssfn;
			ssfn << filenumber << ".pgm";
			fileName = ssfn.str();
			string appFolder = FileComputations::getAppDataFolder();
			fileName = appFolder + fileName;
			//resize and save the image
			resize(face, resizedFace, resizedFace.size(), 0, 0, INTER_AREA);
			Ptr<CLAHE> clahe = createCLAHE(4);
			clahe->apply(resizedFace, resizedFace);
			resizedFace = rotateFace(resizedFace);
			imwrite(fileName, resizedFace);
			vector<string> row;
			//Add an element (column) to the row
			row.push_back(fileName);
			row.push_back(filePath);
			detectedPaths.push_back(row);
		}
		// if more than one face is found in image
		else {
			for (size_t j = 0; j < faces.size(); j++)
			{
				Mat face = gray(faces[j]);
				//check if face is the intended person
				string fileName = "";
				int filenumber = loopIter;
				stringstream ssfn;
				ssfn << filenumber << "_" << j << ".pgm";
				fileName = ssfn.str();
				string appFolder = FileComputations::getAppDataFolder();
				fileName = appFolder + fileName;
				//resize and save the image
				resize(face, resizedFace, resizedFace.size(), 0, 0, INTER_AREA);
				Ptr<CLAHE> clahe = createCLAHE(4);
				clahe->apply(resizedFace, resizedFace);
				resizedFace = rotateFace(resizedFace);
				imwrite(fileName, resizedFace);
				vector<string> row;
				//Add an element (column) to the row
				row.push_back(fileName);
				row.push_back(filePath);
				detectedPaths.push_back(row);
			}
		}
	}
	return detectedPaths;
}

bool FacialComputations::isPerson(const Mat &face, const string &name) {
	bool isPerson;
	imshow("Face", face);
	//display message box asking if face is the intended person
	CString message;
	CString intendedPerson(name.c_str());
	message.Format(_T("Is this %s ?"), intendedPerson);
	const int result = ::MessageBox(NULL, message, L"", MB_YESNOCANCEL | MB_ICONQUESTION);
	switch (result)
	{
	case IDYES:
		isPerson = true;
		break;
	case IDNO:
		isPerson = false;
		break;
	case IDCANCEL:
		isPerson = false;
		break;
	}
	destroyWindow("Face");
	return isPerson;
}

string FacialComputations::nameFile(string lastLine) {
	//remove ".jpg" from file path
	int dotPos = lastLine.find_last_of('.');
	lastLine.replace(dotPos, 4, "");
	//get only the incremented number from file name
	int pos = lastLine.find_last_of('_');
	string fileNumb = lastLine.substr(pos + 1);
	//add one to the incremented number
	int number = atoi(fileNumb.c_str()) + 1;
	string numb = to_string(number);
	//set new file name
	string newFileName = lastLine.replace(pos + 1, 2, numb) + ".jpg";
	return newFileName;
}

void FacialComputations::addImageToModel(const vector<vector<string> > &filePaths, const int &label) {
	Ptr<cv::FaceRecognizer> model;
	vector<Mat> images;
	vector<int> labels;
	string modelpath = "LBPHModel.yml";
	string appFolder = FileComputations::getAppDataFolder();
	modelpath = appFolder + modelpath;

	for (int i = 0; i < filePaths.size(); i++) {
		Mat image = imread(filePaths[i][0], 0);
		//add image and its corresponding label to vectors that contain them
		//when all the images and labels have been added they will be trained
		//in the cv::FaceRecognizer
		images.push_back(image);
		labels.push_back(label);
	}
	model = createLBPHFaceRecognizer();
	model->load(modelpath);
	model->update(images, labels);
	model->save(modelpath);
}

vector<vector<string> > FacialComputations::recognizeFace(vector<vector<string> > filePaths, const int &expectedLabel) {
	string modelpath = "LBPHModel.yml";
	string appFolder = FileComputations::getAppDataFolder();
	modelpath = appFolder + modelpath;
	Ptr<cv::FaceRecognizer> model;
	vector<vector<string> > matches;
	model = createLBPHFaceRecognizer(1, 8, 8, 8, 150);
	model->load(modelpath);
	int progress = 1;
	//see if person is in each image
	for (int i = 0; i < filePaths.size(); i++) {
		Mat image = imread(filePaths[i][0], 0);

		int predictedLabel = model->predict(image);
		//cout << i << ": " << confidence;
		if (expectedLabel == predictedLabel) {
			//if the image isnt already in the matches vector
			if (matches.size() > 0 && matches[matches.size() - 1][1] != filePaths[i][1]) {
				vector<string> row;
				row.push_back(filePaths[i][0]);
				row.push_back(filePaths[i][1]);
				matches.push_back(row);
			}
			else if (matches.size() == 0) {
				vector<string> row;
				row.push_back(filePaths[i][0]);
				row.push_back(filePaths[i][1]);
				matches.push_back(row);
			}
		}
		float percentageOfImagesInLV = (static_cast<float> (progress) / static_cast<float> (filePaths.size())) * 100.0;
		float equivalentPercentageOf20 = (percentageOfImagesInLV * 20.0) / 100.0;
		GlobalVariables::setProgress(100 + round(equivalentPercentageOf20));
		progress++;
	}
	GlobalVariables::setProgress(120);
	return matches;
}

void FacialComputations::createLBPHFaceRecognitionModel(const string &pathOfModel) {
	Ptr<cv::FaceRecognizer> model;
	model = createLBPHFaceRecognizer();
	model->save(pathOfModel);
	model->load(pathOfModel);
}

Mat FacialComputations::rotateFace(Mat face) {
	Mat rotatedFace;
	vector<int> posOfEyes = positionOfEyes(face);
	//if 4 coordinates arent found in vector then exit the method
	if (posOfEyes.size() != 4)
		return face;
	int leftEyeX = posOfEyes[0];
	int leftEyeY = posOfEyes[1];
	int rightEyeX = posOfEyes[2];
	int rightEyeY = posOfEyes[3];

	//if the eyes are fairly horizontal then exit the function
	if ((leftEyeY - rightEyeY) <= 8 && (leftEyeY - rightEyeY) >= -8)
		return face;
	double dy = (rightEyeY - leftEyeY);
	double dx = (rightEyeX - leftEyeX);
	double angle = atan2(dy, dx) * 180.0 / CV_PI;
	//if the angle is bigger than 90 then the face will be upside down after rotations
	if (angle > 90)
		angle += 180;
	else if (angle < -90)
		angle -= 180;
	int len = max(face.cols, face.rows);
	Point2f pt(len / 2., len / 2.);
	//specificitons for how the image will be transformed
	Mat transformation = cv::getRotationMatrix2D(pt, angle, 1.0);
	//rotate the face
	warpAffine(face, rotatedFace, transformation, face.size());
	return rotatedFace;
}

vector<int> FacialComputations::positionOfEyes(const Mat &face) {
	vector<int> posOfEyes;
	//load eye cascade
	string fn_haar = "haarcascade_eye.xml";
	CascadeClassifier haar_cascade;
	haar_cascade.load(fn_haar);

	//Detect eyes in image
	vector< Rect_<int> > eyes;
	haar_cascade.detectMultiScale(face, eyes, 1.05, 5, 0, cv::Size(20, 20));
	//if both eyes arent found exit the method
	if (eyes.size() != 2)
		return posOfEyes;
	//get position of eyes and add them to vector
	Rect_<int> leftEye = eyes[0];
	Rect_<int> rightEye = eyes[1];
	posOfEyes.push_back(leftEye.x);
	posOfEyes.push_back(leftEye.y);
	posOfEyes.push_back(rightEye.x);
	posOfEyes.push_back(rightEye.y);
	return posOfEyes;
}