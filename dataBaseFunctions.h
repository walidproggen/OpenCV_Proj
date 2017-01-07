#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <string>
#include <stdio.h>

using namespace cv;


void safeFile(Mat matrix, String name);
Mat loadFile(String name);

