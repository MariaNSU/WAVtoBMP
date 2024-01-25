#pragma once 
#include <string>
#include "wavHeader.h"

class WavFile {
private:
    WAVHEADER header;
    void* data;
public:
    void read(const std::string& fname);
    void* getData();
    WAVHEADER getHeader();
    void printHeader();
};