//
// Created by 钟华松 on 16/11/27.
//


#include <iostream>
#include <sstream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>
#include "RobustTextDetection.h"
#include "ConnectedComponent.h"
#include "seg_pic.h"
#include "key_frame_extraction.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "global_value.h"

using namespace std;
using namespace cv;

void KeyFrameExtraction::init_para() {
	text_detector_path = TEXT_DETECTOR_PATH;
	key_frame_extraction_dir = KEY_FRAME_EXTRACTION_DIR;
}

void KeyFrameExtraction::apply() {

	init_para();

	//遍历pic目录
	struct dirent * child_dir;    // return value for readdir()  
    DIR * dir;                   // return value for opendir()  
    dir = opendir(key_frame_extraction_dir);  
    if( NULL == dir )  
    {  
        cout << "Can not open dir " << key_frame_extraction_dir << endl;  
        return;  
    }  
    /* read all the files in the dir ~ */  
    while( ( child_dir = readdir(dir) ) != NULL )  
    {  
        // get rid of "." and ".."  
        if( strcmp( child_dir->d_name , "." ) == 0 ||   
            strcmp( child_dir->d_name , "..") == 0    )  
            continue;  
        //cout<<filename->d_name <<endl;
        if (child_dir->d_type & DT_DIR) {
        	string tmp, output_file;
        	string s1(key_frame_extraction_dir);
        	string s2(child_dir->d_name);
        	tmp = s1 + s2 + "/" + s2 + ".txt";
        	output_file = s1 + s2 + "/" + s2 + "_labels" + ".txt";
        	//cout << output_file << endl;

        	ifstream in(tmp.c_str());
        	ofstream out(output_file.c_str(), ios::app);
        	string file_name;
        	while (getline(in, file_name)) {
        		string tmp2;
        		tmp2 = s1 + s2 + "/" + file_name;
        		detection_file_name = tmp2.c_str();
        		
        		//cout << detection_file_name << endl;

        		double result = text_detection();
        		stringstream ss;
        		ss << result;
        		string out_ss;
        		ss >> out_ss;
        		out << out_ss;
        		out << "\n";
        	}
        	in.close();
        	out.close();

            // 关键帧出书文件
            string tmp3 = s1 + s2 + "/" + s2 + "_key_frames" + ".txt";
            // 读分割点文件
            string tmp4;
            tmp4 = s1 + s2 + "/" + s2 + "_seg_points" + ".txt";
            ofstream out1(tmp3);
            ifstream in2(tmp4.c_str());
            ifstream in3(output_file);

            string seg_point;
            int start = 1;
            int end;
            while(getline(in2, seg_point)) {
                stringstream ss;
                ss << seg_point;
                ss >> end;
                out1 << start << " " << end << " ";

                int max_value = 0;
                int max_value_index = start;
                for (int i = 0; i < (end - start + 1); i++) {
                    string label;
                    getline(in3, label);
                    stringstream ss_tmp;
                    ss_tmp << label;
                    int tmp_num;
                    ss_tmp >> tmp_num;
                    if (tmp_num > max_value) {
                        max_value = tmp_num;
                        max_value_index = start + i;
                    }
                }
                out1 << max_value_index << "\n";

                start = end + 1;
                max_value = 0;
            }

            out1.close();
            in2.close();
            in3.close();

        } 
    } 

}

double KeyFrameExtraction::text_detection() { 
    Mat image = imread( detection_file_name );

    /* Quite a handful or params */
    RobustTextParam param;
    param.minMSERArea        = 5;    //10
    param.maxMSERArea        = 2000;  //2000
    param.cannyThresh1       = 5;     //20
    param.cannyThresh2       = 80;    //100
    
    param.maxConnCompCount   = 3000;  //3000
    param.minConnCompArea    = 75;    //75
    param.maxConnCompArea    = 800;   //600
    
    param.minEccentricity    = 0.1;   //0.1
    param.maxEccentricity    = 0.995; //0.995
    param.minSolidity        = 0.1;   //0.4
    param.maxStdDevMeanRatio = 0.5;   //0.5
    
    /* Apply Robust Text Detection */
    /* ... remove this temp output path if you don't want it to write temp image files */
    string temp_output_path = "./Robust-Text-Detection/RobustTextDetection/Temp";
    RobustTextDetection detector(param, temp_output_path);
    double result = detector.apply( image );
    
   	return result;
}

