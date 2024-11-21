#include <iostream>
#include <cmath>
#include "visq/transform/resizer.h"
#include "visq/transform/nearest_neighbor_interpolation.h"
#include "visq/transform/bilinear_interpolation.h"
#include "visq/transform/fft.h"
#include "io.h"

void PrintError() {
  std::cout << "Usage:\n" << "resize \"method\"(nearest, bilinear)  \"input_image\" \"output_image\" new_width new_height";
}

using namespace visq;

int main(int argc, char *argv[]) {
   Image<uint8_t> image(4,1,1);
   image.Set(0, 0, 0, 0);
   image.Set(1, 0, 1, 0);
   image.Set(2, 0, 2, 0);
   image.Set(3, 0, 3, 0);
   auto result  = CooleyTukeyFFT(image);
   
   for(size_t i =0; i < image.GetWidth(); ++i)
     std::cout << result.At(0,i,0) <<" ";
   return 0;   
}

