#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>

using namespace cv;


void trainSVM(Mat featureMat, Mat labelMat);
Mat testSVM(Mat testDataMat);