#include <iostream>
#include <fftw3.h>
#include <cstdint>
#include <cmath>
#include "wavFile.h"
#include "EasyBMP.hpp"
//#include "furieTransform.h"
#include "BMPdata.h"

int main() {
    // Define WAV file name
    const std::string& fname = "../samples/sample-6s.wav";
    WavFile wf;
    // Read WAV file data
    wf.read(fname);
    void* data = wf.getData();
    auto header = wf.getHeader();
    size_t size = header.subchunk2Size/(header.bitsPerSample/8) -  1;
    double T = (double)header.subchunk2Size / (header.bitsPerSample/8) / header.numChannels / header.sampleRate;
    // Cast data pointer
    uint16_t* buf = reinterpret_cast<uint16_t*>(data);

    /*void* buf;
    switch(wf.getHeader().bitsPerSample) {
        case 8:
            buf = reinterpret_cast<uint8_t*>(data);
            break;
        case 16:
            buf = reinterpret_cast<uint16_t*>(data);
            break;
        case 32:
            buf = reinterpret_cast<uint32_t*>(data);
            break;
        case 64:
            buf = reinterpret_cast<uint64_t*>(data);
            break;
        default:
            break;
    }*/


    // Prepare data for FFT
    double* input = new double [size];
    for(int i = 0; i < size; i++) {
       input[i] = (double)buf[i];
    }
    // Create FFTW plans
    fftw_complex* fft_output = reinterpret_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex) * (size / 2 + 1)));
    fftw_plan plan = fftw_plan_dft_r2c_1d(size, input, fft_output, FFTW_ESTIMATE);
    // Perform the FFT transform
    fftw_execute(plan);

    // Prepare data for BMP creation
    BMPdata bd;
    bd.computeAmlFreq(fft_output, size/2 - 1, T);
    auto amplAndFreqVect = bd.getData();
    auto yMin = bd.getMinFreq();
    auto yMax = bd.getMaxFreq();
    auto aMax = bd.getMaxAmpl();
    auto aMin = bd.getMinAmpl();
    auto xMax = amplAndFreqVect.size();
    int xMin = 0;
    std::cout << yMin << " yMin" << std::endl;
    std::cout << xMin << " xMin" << std::endl;
    std::cout << yMax << " yMax" << std::endl;
    std::cout << xMax << " xMax" << std::endl;
    
    EasyBMP::RGBColor black(0, 0, 0);  
    // sizeX, sizeY, FileName, BackgroundColor
    EasyBMP::Image img(xMax, yMax, "test.bmp", black);
    // Fill picture colors
    img.Write();
    
    // Clean up
    fftw_destroy_plan(plan);
    fftw_free(fft_output);
    delete [] input;
    return 0;
}