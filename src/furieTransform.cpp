#include "furieTransform.h"

FurieTransf::FurieTransf(double* origin_, size_t originSize_){
    origin = new double [originSize_];
    for(int i = 0; i < originSize_; i++){
         origin[i] = origin_[i];
    }
    image = reinterpret_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex) * (originSize_ / 2 + 1)));
    originSize = originSize_;
    imageSize = originSize_ / 2 + 1;
    
}

void FurieTransf::transform() {
    plan = fftw_plan_dft_r2c_1d(originSize, origin, image, FFTW_ESTIMATE);
    fftw_execute(plan);
    fftw_destroy_plan(plan);
}

fftw_complex* FurieTransf::getImage(){
    return image;
}

size_t FurieTransf::getImageSize(){
    return imageSize;
}
FurieTransf::~FurieTransf(){
    
    fftw_free(image);
    delete [] origin;
}