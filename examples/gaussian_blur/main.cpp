#include <iostream>
#include "visq/transform/border_extensions/constant_border.h"
#include "visq/transform/border_extensions/mirror_border.h"
#include "visq/transform/filter.h"
#include "io.h"

void PrintError() {
  std::cout << "Usage:\n" << "gaussian_blur \"border-method\"(constant, mirror)  \"input_image\" \"output_image\" kernel_width kernel_height";
}

using namespace visq;

int main(int argc, char *argv[]) {
  if (argc < 6) {
    PrintError();
    return 1;
  }

  auto [err, im] = visq::LoadImage(argv[2]);
  if (err == visq::ErrorCode::InvalidFormat) {
    std::cout << "Format not supported" << std::endl;
    return 1;
  }

  if (err == ErrorCode::FileNotFound) {
    std::cout << "Could not find the provided file: " << argv[2] << std::endl;
    return 1;
  }

  char *error;
  size_t new_width = std::strtol(argv[4], &error, 10);
  size_t new_height = std::strtol(argv[5], &error, 10);

  Image<double> kernel(5, 5, 3);
  Image<uint8_t> image(100, 100, 3);

  border_extensions::MirrorBorder<uint8_t> ext_image(image);
  Filter::Apply(&kernel, &ext_image);
  

  if(strcmp(argv[1], "nearest") == 0) {
  //  std::cout << "Resizing using Nearest neighbor interpolation" << std::endl;
  //  interpolation = std::make_unique<NearestNeighborInterpolation<uint8_t>>(im.value());
  } else if(strcmp(argv[1], "bilinear") == 0) {
  //  std::cout << "Resizing using Bilinear interpolation" << std::endl;
  //  interpolation = std::make_unique<BilinearInterpolation<uint8_t>>(im.value());  
  } else {
  //  std::cerr << "Invalid interpolation method." << std::endl;
  //  return 1;
  }

  //auto resized_image = resizer.Resize(interpolation.get(), new_width, new_height);
  //visq::SaveImage(resized_image, argv[3], visq::ImageFormat::Jpeg);
  return 0;
}

