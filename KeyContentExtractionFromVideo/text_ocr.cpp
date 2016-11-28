
#include "text_ocr.h"
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <iostream>

using namespace std;


void TextOCR::ocr() {
	char *outText;

    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (api->Init("/Users/zhonghuasong/code/c++/tesseract/tessdata", "eng")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    // Open input image with leptonica library
    Pix *image = pixRead("./pic/math/image_7.jpg");
    api->SetImage(image);
    // Get OCR result
    outText = api->GetUTF8Text();
    printf("OCR output:\n%s", outText);

    // Destroy used object and release memory
    api->End();
    delete [] outText;

}

