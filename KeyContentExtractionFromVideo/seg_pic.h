//
// Created by 钟华松 on 16/11/27.
//

#ifndef KEYCONTENTEXTRACTIONFROMVIDEO_SEG_PIC_H

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

class SegPic {
public:
	void init_para();
	void apply();

protected:
	double calculate_distance(Mat& mat1, Mat& mat2);
	double calculate_distance_mean(vector<double>& dist);
	Mat rgb2hsv(const char* filename);
	void segment_pic();

private:
	const char* seg_pic_dir;
	const char* seg_input_dir;
	const char* seg_input_file_name;
	const char* seg_output_file_name;

};
#define KEYCONTENTEXTRACTIONFROMVIDEO_SEG_PIC_H

#endif //KEYCONTENTEXTRACTIONFROMVIDEO_SEG_PIC_H
