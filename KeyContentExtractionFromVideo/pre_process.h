//
// Created by 钟华松 on 16/11/27.
//

#ifndef KEYCONTENTEXTRACTIONFROMVIDEO_PRE_PROCESS_H

#include <vector>
#include <string>

using namespace std;

class PreProcess{
private:
    const char* pre_process_input_file_name;
    const char* current_file_name;
    const char* pre_process_output_dir;
	const char* pre_process_input_dir;
    int interval;

public:
    void apply();

protected:
    void init_para();
    void sample_frames();
	//字符串分割
	vector<string> split(const string& s, const string& delim);


};
#define KEYCONTENTEXTRACTIONFROMVIDEO_PRE_PROCESS_H

#endif //KEYCONTENTEXTRACTIONFROMVIDEO_PRE_PROCESS_H
