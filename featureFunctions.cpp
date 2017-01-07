#include "featureFunctions.h"

featureFunction functions[] = {
	meanSquareDev
};

static const int MAX_FEAUFUNC = 1;

float meanSquareDev(Mat image, Mat mask) {
	if (image.empty() || mask.empty())
	{
		return EXIT_FAILURE;
	}
	cvtColor(image, image, CV_BGR2GRAY);

	//if (mask.rows > 0 && mask.cols > 0)
		//cvtColor(mask, mask, CV_BGR2GRAY);
	cv::Scalar mean, stddev;
	meanStdDev(image, mean, stddev, mask);

//	std::cout << "square mean deviation: " << stddev.val[0] * stddev.val[0] << std::endl;
	return (float) (stddev.val[0] * stddev.val[0]);
}



/**********************CALCULATE FEATUREVECTOR************************************/

Mat calcFeatureVec(Mat img, Mat mask) {
	Mat featureVec(1, MAX_FEAUFUNC, CV_32FC1);

	std::cout << ".";
	for (int i = 0; i < MAX_FEAUFUNC; i++) {
		featureVec.at<float>(0,i) = functions[i](img, mask);
	}

	return featureVec;
}