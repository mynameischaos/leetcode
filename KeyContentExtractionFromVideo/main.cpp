#include <iostream>
#include "seg_pic.h"
#include "pre_process.h"
#include "seg_pic.h"


using namespace std;

//g++ pre_process.cpp  main.cpp  $(pkg-config --cflags --libs opencv)

int main() {
	PreProcess* pre_process = new PreProcess();
	pre_process->apply();
	SegPic* seg_pic = new SegPic();
	seg_pic->apply();

    return 0;
}
