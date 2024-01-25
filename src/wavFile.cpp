#include "wavFile.h"
#include <fstream>
#include <iostream>
#include <cstdint>

void WavFile::read(const std::string & fname) {
    std::ifstream fin(fname, std::ios::binary);   
    if (!fin)
    {
        std::cout << "Error!" << std::endl;
        return ;
    }
    fin.read((char*)&header, sizeof(header));

    char* buf = new char[header.subchunk2Size];
    fin.read(buf, header.subchunk2Size);

    switch(header.bitsPerSample) {
        case 8:
            data = reinterpret_cast<uint8_t*>(buf); 
            break;
        case 16:
            data = reinterpret_cast<uint16_t*>(buf); 
            break;
        case 32:
            data = reinterpret_cast<uint32_t*>(buf); 
            break;
        case 64:
            data = reinterpret_cast<uint64_t*>(buf); 
            break;
        default:
            break;
    }
    delete [] buf;
    fin.close();
}
void* WavFile::getData(){
    return data;
}

WAVHEADER WavFile::getHeader(){
    return header;
}
void WavFile::printHeader() {
    float fDurationSeconds =  (float) header.subchunk2Size / (header.bitsPerSample/8) / header.numChannels / header.sampleRate;
    int iDurationMinutes = (int)fDurationSeconds/60;
    fDurationSeconds = fDurationSeconds - (iDurationMinutes * 60);
    std::cout << "Duration - " << iDurationMinutes << ":" << fDurationSeconds << std::endl;
    std::cout << "Sample rate - " << header.sampleRate << std::endl;
    std::cout << "Channels - " << header.numChannels << std::endl;
    std::cout << "Bits per sample - " << header.bitsPerSample <<std::endl;
    std::cout << "Data size - "<< header.subchunk2Size << std::endl; 
    std::cout << "Samples number - " << (float) header.subchunk2Size / (header.bitsPerSample/8) << std::endl;
}