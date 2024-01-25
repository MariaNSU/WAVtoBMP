#include "BMPdata.h"

void BMPdata::computeAmlFreq(fftw_complex* transformedData, size_t N, double T) {
    for(int i = 0; i < N; i++){
        auto amplitude = sqrt(pow(transformedData[i][0], 2) + pow(transformedData[i][1], 2));
        auto freq = (double)i/((N-1)*2*T);
        amplAndFreq.push_back(std::make_pair(amplitude, freq));
        if(freq > maxFreq){
            maxFreq = freq;
        }
        if (freq < minFreq) {
            minFreq = freq;
        }
        if(amplitude > maxAmpl){
            maxAmpl= amplitude;
        }
        if (amplitude < minAmpl) {
            minAmpl = amplitude;
        }
    }
}

std::vector<std::pair<double, double>> BMPdata::getData() {
    return amplAndFreq;
}
double BMPdata::getMaxAmpl(){
    return maxAmpl;
}
double BMPdata::getMinAmpl(){
    return minAmpl;
}
double BMPdata::getMaxFreq(){
    return maxFreq;
}
double BMPdata::getMinFreq(){
    return minFreq;
}