//
// Created by 钟华松 on 16/11/27.
//

#ifndef KEYCONTENTEXTRACTIONFROMVIDEO_PRE_PROCESS_H

class PreProcess{
private:
    const char* pre_process_input_file_name;
    const char* current_file_name;
    const char* pre_process_output_dir;
    int interval;

public:
    PreProcess();
    virtual ~PreProcess();
    void apply();

protected:
    void init_para();
    void sample_frames();


};
#define KEYCONTENTEXTRACTIONFROMVIDEO_PRE_PROCESS_H

#endif //KEYCONTENTEXTRACTIONFROMVIDEO_PRE_PROCESS_H
