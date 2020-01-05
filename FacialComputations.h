#pragma once
#ifndef FACIALCOMPUTATIONS_H
#define FACIALCOMPUTATIONS_H
#include <string>
#include <vector>
#include <memory>
#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"

class FacialComputations
{
public:
	FacialComputations();
	~FacialComputations();
	static void prepareListViewVariables();
	static std::vector<std::vector<std::string> > detectAndSaveFace(const std::vector<std::string> &filePaths, const std::string &name, const int &label, std::string lastLine);
	static std::vector<std::vector<std::string> > detectFacesToFindPerson(const std::vector<std::string> &filePaths);
	static std::vector<std::vector<std::string> > FacialComputations::detectFacesToFindPersonNoLoop(std::string filePath, int loopIter);
	static void addImageToModel(const std::vector<std::vector<std::string> > &filePaths, const int &label);
	static std::vector<std::vector<std::string> > recognizeFace(std::vector<std::vector<std::string> > filePaths, const int &expectedLabel);
	static cv::Mat rotateFace(cv::Mat face);
	static void createLBPHFaceRecognitionModel(const std::string &pathOfModel);
private:
	//size of all images to be trained and recognised with cv::FaceRecognizer
	static const int imgRows = 100;
	static const int imgCols = 100;
	static bool isPerson(const cv::Mat &face, const std::string &name);
	static std::vector<int> positionOfEyes(const cv::Mat &face);
	static std::string nameFile(std::string lastLine);
};
#endif