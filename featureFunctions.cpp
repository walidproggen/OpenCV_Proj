#include "featureFunctions.h"

//Mat grad;

featureFunction functions[] = {
	meanSquareDev,
	perimeter,
	cellSize
};

static const int MAX_FEAUFUNC = 3;

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


float sumGradient(Mat image, Mat mask) {
	Mat maskedSrc, src_gray;
	Mat grad;	//Sobel-Gradient
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	int c;

	image.copyTo(maskedSrc, mask);

	GaussianBlur(maskedSrc, maskedSrc, Size(3, 3), 0, 0, BORDER_DEFAULT);

	/// Convert it to gray
	cvtColor(maskedSrc, src_gray, CV_BGR2GRAY);

	/// Generate grad_x and grad_y
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;

	/// Gradient X
	//Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
	Sobel(src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);

	/// Gradient Y
	//Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
	Sobel(src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);

	/// Total Gradient (approximate)
	addWeighted(abs_grad_x, 1.0, abs_grad_y, 1.0, 0, grad);
	imshow("Sobel", grad);
	waitKey(30);
	//Scalar s = sum(grad);

	cv::Scalar mean, stddev;
	meanStdDev(grad, mean, stddev, mask);
	
	//Scalar s = mean(src_gray, mask);
	cout << stddev.val[0] * stddev.val[0] << endl;

	return (float)stddev.val[0] * stddev.val[0];
}

float laplacian (Mat image, Mat mask) {
	Mat dst, abs_dst, maskedSrc, src_gray;
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	char* window_name = "Laplace Demo";

	image.copyTo(maskedSrc, mask);


	// Remove noise by blurring with a Gaussian filter
	GaussianBlur(maskedSrc, maskedSrc, Size(3, 3), 0, 0, BORDER_DEFAULT);

	// Convert the image to grayscale
	cvtColor(maskedSrc, src_gray, CV_BGR2GRAY);

	// Apply Laplace function
	Laplacian(src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(dst, abs_dst);
	
	cv::Scalar mean, stddev;
	meanStdDev(src_gray, mean, stddev, mask);

	return (float) (stddev[0] * stddev[0]) ;
}

float perimeter(Mat image, Mat mask) {
	Mat canny_output, maskedSrc, src_gray, dst;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	
	image.copyTo(maskedSrc, mask);

	// Threshhold to draw only outer contours
	cvtColor(maskedSrc, src_gray, CV_BGR2GRAY);
	threshold(src_gray, dst, 1, 255, 0);

	/// Detect edges using canny
	Canny(dst, canny_output, 0.0, 0.0, 3);
	/// Find contours
	findContours(canny_output, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	//cout << "Contours found: " << contours.size() << endl;
	//cout << "Contour perimeter: " << arcLength(contours[0], true) << endl;

	// return perimeter
	return (float) arcLength(contours[0], true); 
	return 0.0;
}

float cellSize(Mat image, Mat mask) {
	float size = 0.0;
	int nonZero = countNonZero(mask);

	size = (float) (mask.rows * mask.cols) / (float) nonZero;
	//size = (float)nonZero;
	//cout << size << endl;

	return size;
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