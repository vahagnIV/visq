#include <iostream>
#include <cmath>
#include "visq/transform/resizer.h"
#include "visq/transform/nearest_neighbor_interpolation.h"
#include "visq/transform/bilinear_interpolation.h"
#include "io.h"

void PrintError() {
  std::cout << "Usage:\n" << "resize \"method\"(nearest, bilinear)  \"input_image\" \"output_image\" new_width new_height";
}

using namespace visq;

int main(int argc, char *argv[]) {
   //int N = 3;
   
   //int M = 13;
  for(int N = 3; N < 15; ++N){
    for( int M = -30; M < 30; ++M){
      double cos_sum = 0;
      double sin_sum = 0;

      for(int n =0; n<N;++n){
        cos_sum += std::cos(2 * M_PI * n * M / N);
        sin_sum += std::sin(2 * M_PI * n * M / N);
      }
      std::cout<<"N = " << N << " M = " << M <<  " Cos: " << cos_sum << " Sin: " << sin_sum << std::endl;
    }
  }
}

