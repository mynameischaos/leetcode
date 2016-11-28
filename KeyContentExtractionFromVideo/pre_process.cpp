//
// Created by 钟华松 on 16/11/27.
//

#include "pre_process.h"
#include "global_value.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
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
	pre_process_input_dir = PRE_PROCESS_INPUT_DIR;
}

vector<string> PreProcess::split(const string& s, const string& delim) {
	std::vector<std::string> elems;  
	    size_t pos = 0;  
		size_t len = s.length();  
		size_t delim_len = delim.length();  
		if (delim_len == 0) return elems;  
		while (pos < len) {  
			int find_pos = s.find(delim, pos);  
			if (find_pos < 0)  {  
				elems.push_back(s.substr(pos, len - pos));  
				break;  
			}  
			elems.push_back(s.substr(pos, find_pos - pos));  
			pos = find_pos + delim_len;  
		}  
	return elems;   
}

void PreProcess::sample_frames() {
    string file_name;
    ifstream in(pre_process_input_file_name, ios::in);

    while(getline(in, file_name)) {
        int i = 0;
        IplImage* img = 0;
        int count = 0;
        char image_name[100];
		string output_filename;
		string output_dir;
		output_dir = pre_process_output_dir + split(file_name, ".")[0];
		mkdir(output_dir.c_str(), 0755);
		output_filename = output_dir + "/" + split(file_name, ".")[0] + ".txt";
        ofstream out(output_filename, ios::app);
		
		file_name = pre_process_input_dir + file_name;
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
            sprintf(image_name, "%s%s%d%s", (output_dir + "/").c_str(), "image_", i, ".jpg");
            stringstream ss;
            string num;
            ss << i;
            ss >> num;
            string fileName;
            fileName = "image_" + num + ".jpg";
            out << fileName;
            out << "\n";
            cvSaveImage(image_name, img);
        }

        out.close();

    }
}
