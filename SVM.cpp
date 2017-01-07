#include "SVM.h"

CvSVM svm;

void trainSVM(Mat featureMat, Mat labelMat) {
	// Set up SVM's parameters
	CvSVMParams params;
	params.svm_type = CvSVM::C_SVC;
	params.kernel_type = CvSVM::LINEAR;
	params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER, 100, 1e-6);

	// Train the SVM
	
	svm.train(featureMat, labelMat, Mat(), Mat(), params);
}

Mat testSVM(Mat testDataMat) {
	Mat result;
	svm.predict(testDataMat, result);
	return result;
}