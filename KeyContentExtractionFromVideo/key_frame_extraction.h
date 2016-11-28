//
// Created by 钟华松 on 16/11/28.
//

#ifndef KEY_FRAME_EXTRACTION_H

class KeyFrameExtraction {
public:
    void init_para();
    void apply();

protected:
    double text_detection();

private:
    const char* detection_file_name;
    const char* text_detector_path;
    const char* key_frame_extraction_dir;
    const char* output_file_name;
    const char* key_frame_extraction_output_file_name;
};

#define KEY_FRAME_EXTRACTION_H

#endif //KEY_FRAME_EXTRACTION_H