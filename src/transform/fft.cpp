#include "visq/transform/fft.h"
#include <cmath>
#include <complex>
#include <vector>

namespace visq {

namespace {

Image<std::complex<double>> GetOdds(const Image<std::complex<double>> & input_row){
  Image<std::complex<double>> result(input_row.GetWidth() / 2, 1, input_row.GetChannels());
  for(size_t i = 0; i < input_row.GetWidth() / 2; ++i){
    for(size_t c = 0; c < input_row.GetChannels(); ++c){
      result.Set(input_row.At(0, 2 * i + 1, c), 0, i, c);
    }
  }
  return result;
}

Image<std::complex<double>> GetEvens(const Image<std::complex<double>> & input_row){
  Image<std::complex<double>> result(input_row.GetWidth() / 2, 1, input_row.GetChannels());
  for(size_t i = 0; i < input_row.GetWidth() / 2; ++i){
    for(size_t c = 0; c < input_row.GetChannels(); ++c){
      result.Set(input_row.At(0, 2*i, c), 0, i, c);
    }
  }
  return result;
}

void FFT1D(Image<std::complex<double>> & input_row){
  size_t N = input_row.GetWidth();
  if (input_row.GetWidth() == 1) return;
  else {
    auto odds = GetOdds(input_row);
    auto evens = GetEvens(input_row);

    FFT1D(odds);
    FFT1D(evens);
    
    for (size_t  k = 0; k < N / 2; ++k ){
      for(size_t c = 0; c < input_row.GetChannels(); ++c){
        std::complex<double> e = evens.At(0,k,c);
        std::complex<double> o = odds.At(0,k,c)* std::polar(1., -2 * M_PI * k / N);
        input_row.Set(e + o, 0, k, c);
        input_row.Set(e - o, 0, k + N /2 , c);
   
      }
   }
  }
}

size_t FindNearestPowerOf2(size_t x){
    if((x -1) & x == 0)
      return x;

    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
// We assume that we are building for a 64 bit machine
    x |= (x >> 32);
// #endif
    return(x+1);
}

}  // namespace

Image<std::complex<double>> CooleyTukeyFFT(const Image<double> input) {
  size_t width = input.GetWidth();
  size_t height = input.GetHeight();

  // Allocate output image
  size_t nearest_power_of_2 =FindNearestPowerOf2(input.GetWidth());

  Image<std::complex<double>> output(nearest_power_of_2,height,input.GetChannels(),0);
  Image<std::complex<double>> input_c (output,width, height,0);
  input.CopyTo(input_c);

  for (size_t y = 0; y < height; ++y) {
    auto row = output.Row(y);
    FFT1D(row);
  }

  return input_c;
}

}  // namespace visq

