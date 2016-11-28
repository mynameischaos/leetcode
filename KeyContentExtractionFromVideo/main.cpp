#include <iostream>
#include "seg_pic.h"
#include "pre_process.h"
#include "key_frame_extraction.h"
#include "seg_pic.h"
#include "text_ocr.h"


using namespace std;

//g++ pre_process.cpp text_ocr.cpp main.cpp  $(pkg-config --cflags --libs opencv tesseract ) RobustTextDetection.cpp  key_frame_extraction.cpp ConnectedComponent.cpp  seg_pic.cpp -std=c++11 -llept -ltesseract

int main() {
	/*
	cout << "Pre process..." << endl;
	PreProcess* pre_process = new PreProcess();
	pre_process->apply();
	
	cout << "Seg pic to sets..." << endl;
	SegPic* seg_pic = new SegPic();
	seg_pic->apply();

	cout << "Key frame extraction..." << endl;
	KeyFrameExtraction* key_frame_extraction = new KeyFrameExtraction();
	key_frame_extraction->apply();
	*/

	cout << "ocr..." << endl;
	TextOCR* text_ocr = new TextOCR();
	text_ocr->ocr();

    return 0;
}
