#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;

void interpolation(Mat src_infor, Mat src_form) {
	Mat src_infor_gray,src_infor_binary;
	cvtColor(src_infor, src_infor_gray, COLOR_BGR2GRAY);
	threshold(src_infor_gray, src_infor_binary, 240, 255, THRESH_BINARY);
	Mat temp_binary, temp_output;
	resize(src_infor_binary, temp_binary, Size(), 0.2, 0.2);
	imshow("temp_binary", temp_binary);
	for (size_t i = 0;i < src_form.rows;i++) {
		for (size_t j = 0;j < src_form.cols;j++) {
			if (i < src_infor.rows && j < src_infor.cols && src_infor_binary.at<uchar>(i, j) == 0) {
				Vec3b intens1 = src_form.at<Vec3b>(i, j);
				Vec3b intens2 = src_infor.at<Vec3b>(i, j);
				for (int k = 0;k < 3;k++) {
					intens1[k] = intens2[k];
				}
				src_form.at<Vec3b>(i, j) = intens1;
			}
		}
	}
	resize(src_form, temp_output, Size(), 0.2, 0.2);
	imshow("Completed_form", temp_output);
	imwrite("Pattern_completed.jpg", src_form);
	waitKey(0);
}

int main() {
	Mat src1 = imread("Pattern_infor.jpeg", IMREAD_COLOR);
	Mat src2 = imread("Pattern_form.jpg", IMREAD_COLOR);
	interpolation(src1, src2);
	return 0;
}