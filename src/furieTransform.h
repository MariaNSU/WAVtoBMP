#pragma once 
#include <fftw3.h>

class FurieTransf {
private:
    double* origin;
    fftw_complex* image;
    size_t originSize;
    size_t imageSize;
    fftw_plan plan;
public:
    FurieTransf() = delete;
    FurieTransf(double* origin_, size_t originSize_);
    void transform();
    fftw_complex* getImage();
    size_t getImageSize();
    ~FurieTransf();

};