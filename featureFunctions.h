#ifndef __FEATUREFUNCTIONS_H_INCLUDED__   // if x.h hasn't been included yet...
#define __FEATUREFUNCTIONS_H_INCLUDED__   //   #define this so the compiler knows it has been included


#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/opencv_modules.hpp>

using namespace cv;
using namespace std;

typedef float (*featureFunction) (Mat img, Mat mask);


float meanSquareDev(Mat image, Mat mask);
float sumGradient(Mat image, Mat mask);
float perimeter(Mat image, Mat mask);
float cellSize(Mat image, Mat mask);
float laplacian(Mat image, Mat mask);

Mat calcFeatureVec(Mat img, Mat mask = Mat());



#endif // __FEATUREFUNCTIONS_H_INCLUDED__