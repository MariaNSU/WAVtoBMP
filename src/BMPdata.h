#pragma once 
#include <vector>
#include <limits>
#include <fftw3.h>
#include <math.h>

class BMPdata {
private:
    std::vector<std::pair<double, double>> amplAndFreq;
    size_t N; //vector length
    double maxAmpl = 0;
    double maxFreq = 0;
    double minAmpl = std::numeric_limits<double>::max();
    double minFreq = std::numeric_limits<double>::max();
public:
    void computeAmlFreq(fftw_complex* transformedData, size_t N, double T);
    std::vector<std::pair<double, double>> getData();
    double getMaxAmpl();
    double getMinAmpl();
    double getMaxFreq();
    double getMinFreq();
};
