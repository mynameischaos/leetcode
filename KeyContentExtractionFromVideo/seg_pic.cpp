//
// Created by 钟华松 on 16/11/27.
//


#include "seg_pic.h"
#include "global_value.h"
#include <dirent.h>

using namespace std;
using namespace cv;

void SegPic::init_para() {
	seg_pic_dir = SEG_PIC_DIR;
}

void SegPic::apply() {
	init_para();

	//遍历pic目录
	struct dirent * child_dir;    // return value for readdir()  
    DIR * dir;                   // return value for opendir()  
    dir = opendir(seg_pic_dir);  
    if( NULL == dir )  
    {  
        cout << "Can not open dir " << seg_pic_dir << endl;  
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
        	string tmp, tmp2, tmp3, tmp4;
        	string s1(seg_pic_dir);
        	string s2(child_dir->d_name);

        	tmp2 = s1 + s2 + "/";
        	//cout << tmp2 << endl;
        	seg_input_dir = tmp2.c_str();        //目录

        	// ./pic/test/test.txt
        	tmp = s1 + s2 + "/" + s2 + ".txt";
        	//cout << tmp <<endl;
        	seg_input_file_name = tmp.c_str();  //读的文件

        	//分割输出的文件
        	tmp3 = tmp2 + s2 + "_seg" + ".txt";
        	seg_output_file_name = tmp3.c_str();
        	//cout << tmp3 << endl;
        	
        	//分割点的输出文件
        	tmp4 = tmp2 + s2 + "_seg_points" + ".txt";
        	seg_point_file_name = tmp4.c_str();

        	cout << "seg pic: " << tmp << endl;
        	segment_pic();
        }  
    }  
}

double SegPic::calculate_distance_mean(vector<double>& dist) {
	double sum = 0;
	for (int i = 0; i < (int)dist.size(); i++) {
		sum += dist[i];
	}
	if (dist.size() != 0) {
		return sum / dist.size();
	}
	return 0.0;
}

// 计算两张图像之间的欧拉距离
double SegPic::calculate_distance(Mat& mat1, Mat& mat2) {
	double result = 0;
	//cout << mat1.rows << "  " << mat1.cols << endl;
	//cout << mat2.rows << "  " << mat2.cols << endl;
	int row = min(mat1.rows, mat2.rows);
	int col = min(mat1.cols, mat2.cols);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			double sum = 0;
			sum += pow((mat1.at<Vec3b>(i, j).val[0] - mat2.at<Vec3b>(i, j).val[0]) / 180, 2);
			sum += pow((mat1.at<Vec3b>(i, j).val[1] - mat2.at<Vec3b>(i, j).val[1]) / 255, 2);
			sum += pow((mat1.at<Vec3b>(i, j).val[2] - mat2.at<Vec3b>(i, j).val[2]) / 255, 2);
			result += sqrt(sum);
		}
	}
	return result;
}

void SegPic::segment_pic() {
	ifstream in(seg_input_file_name, ios::in);
	string file_a, file_b;
	
	vector<string> files;
	vector<double> files_distance;
	while(getline(in, file_a)) {
		files.push_back(file_a);
	}

	ofstream out(seg_output_file_name, ios::app);
	ofstream out2(seg_point_file_name, ios::app);
	for (int i = 0; i < (int)(files.size() - 1); i++) {
		string s1(seg_input_dir);
		string file1;
		string file2;
		file1 = s1 + files[i];
		file2 = s1 + files[i + 1];
		//cout << file1 << endl;
		//cout << file2 << endl;
		out << file1 << " " << file2 << " ";

		Mat tmp1 = rgb2hsv(file1.c_str());
		Mat tmp2 = rgb2hsv(file2.c_str());
		double tmp = calculate_distance(tmp1, tmp2);
		//cout << i + 1 << "  " << i + 2 << "  " << tmp << endl;
		out << tmp << " ";

		if (tmp > 1200) {
			//cout << "up" << endl;
			out << "seg";
			out2 << i + 1 << "\n";

		}

		out << "\n";

		files_distance.push_back(tmp);
	}
	out2 << files.size() - 1;
	
	out.close();
	out2.close();
	/*
	double pre_distance_mean = 0;
	vector<double> vec_pre_distance;
	if (files_distance.size() != 0) {
		pre_distance_mean = files_distance[0];
		vec_pre_distance.push_back(files_distance[0]);
	} else {
		return;
	}

	for (int i = 1; i < (int)files_distance.size(); i++) {
		if (files_distance[i] > pre_distance_mean * para_greater || files_distance[i] < pre_distance_mean * para_smaller) {
			cout << i + 2 << endl;
			vec_pre_distance.clear();
			vec_pre_distance.push_back(files_distance[i]);
			pre_distance_mean = files_distance[i];
		} else {
			vec_pre_distance.push_back(files_distance[i]);
			pre_distance_mean = calculate_distance_mean(vec_pre_distance);
		}	
	}
	*/

	in.close();
}

Mat SegPic::rgb2hsv(const char* filename) {
	//读入图像
	Mat image = imread(filename);
	Mat hsvimage;

	//创建窗口
	namedWindow("HSV", CV_WINDOW_AUTOSIZE);
	//转换RGB to HSV
	cvtColor(image, hsvimage, CV_BGR2HSV);
	//显示图像
	//imshow("HSV", hsvimage);
	//保存图像
	//string saveName;
	//saveName += "hsv_";
	//saveName += filename;
	//imwrite(saveName, hsvimage);
	
	return hsvimage;

}