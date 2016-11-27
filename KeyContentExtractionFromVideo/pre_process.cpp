//
// Created by 钟华松 on 16/11/27.
//

#include "pre_process.h"
#include "global_value.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include "opencv2/opencv.hpp"
#include <unistd.h>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;


void PreProcess::apply() {
    init_para();
    sample_frames();
}

void PreProcess::init_para() {
    pre_process_input_file_name = PRE_PROCESS_INPUT_FILE_NAME;
    pre_process_output_dir = PRE_PROCESS_OUTPUT_DIR;
    interval = SAMPLE_INTERVAL;
}

void PreProcess::sample_frames() {
    string file_name;
    ifstream in(pre_process_input_file_name, ios::in);

    while(getline(in, file_name)) {
        int i = 0;
        IplImage* img = 0;
        int count = 0;
        char image_name[25];
		string output_filename;
		output_filename += pre_process_output_dir + ""
        ofstream out(output_filename, ios::app);

		
        CvCapture* capture = cvCaptureFromAVI(file_name.c_str());
        int nFrame = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);
        int fps = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
        fps = interval * fps;
        cout << "file name: " << file_name << endl;
        cout << "nFrame:" << nFrame << endl;
        cout << "fps:" << fps << endl;

        while (1) {
            img = cvQueryFrame(capture);
            if (!img) {
                break;
            } else {
                count++;
                if (count != fps) {
                    continue;
                }
            }
            count = 0;
            cout << i++ <<endl;
            sprintf(image_name, "%s%d%s", "image_", i, "_.jpg");
            stringstream ss;
            string num;
            ss << i;
            ss >> num;
            string fileName;
            fileName = "image_" + num + "_.jpg";
            out << fileName;
            out << "\n";
            cvSaveImage(image_name, img);
        }

        out.close();

    }
}
