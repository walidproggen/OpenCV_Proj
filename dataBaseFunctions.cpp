#include "dataBaseFunctions.h"

void safeFile(Mat matrix, String name) {
	FileStorage fs("test.yml", FileStorage::APPEND);

	fs << name << matrix;
	fs.release();
}

Mat loadFile (String name) {
	Mat result;
	FileStorage fs("test.yml", FileStorage::READ);
	fs["TrainMatrix"] >> result;
	fs.release();
	return result;
}