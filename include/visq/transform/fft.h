#ifndef VISQPROJECT_TRANSFORM_FFT_H_
#define VISQPROJECT_TRANSFORM_FFT_H_

#include "image.h"
#include <complex>
#include <vector>

namespace visq {

/**
 * Performs the Cooley-Tukey 2D FFT on an Image<double>.
 *
 * @param input The input image of type Image<double>.
 * @return An Image<std::complex<double>> containing the FFT result.
 */
Image<std::complex<double>> CooleyTukeyFFT(const Image<double> input);

}  // namespace visq

#endif  // VISQPROJECT_TRANSFORM_FFT_H_ 

