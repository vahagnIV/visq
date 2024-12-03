#include <iostream>
#include <visq/transform/border_extensions/mirror_border.h>
#include <visq/transform/filter.h>
#include <visq/transform/filters/gradient.h>
#include <visq/utils/monochrome.h>
#include "io.h"

void PrintError() {
  std::cout << "Usage:\n"
            << "gradient  \"input_image\" \"output_image(without extension)\"";
}

using namespace visq;

int main(int argc, char *argv[]) {
  if (argc < 3) {
    PrintError();
    return 1;
  }

  auto [err, im] = visq::LoadImage(argv[1]);
  if (err == visq::ErrorCode::InvalidFormat) {
    std::cout << "Format not supported" << std::endl;
    return 1;
  }

  if (err == ErrorCode::FileNotFound) {
    std::cout << "Could not find the provided file: " << argv[2] << std::endl;
    return 1;
  }

  Image<uint8_t> img = utils::ToMonochrome(im.value());


  border_extensions::MirrorBorder<uint8_t> ext_image(img);


  Image<double> sobel_x = transform::filters::CreateSobelX();
  Image<double> sobel_y = transform::filters::CreateSobelX();
//  Image<uint8_t> image(100, 100, 3);

  
  Image<uint8_t> result_x = Filter::Apply(&sobel_x, &ext_image);
  Image<uint8_t> result_y = Filter::Apply(&sobel_y, &ext_image);

  if (strcmp(argv[1], "nearest") == 0) {
    //  std::cout << "Resizing using Nearest neighbor interpolation" << std::endl;
    //  interpolation = std::make_unique<NearestNeighborInterpolation<uint8_t>>(im.value());
  } else if (strcmp(argv[1], "bilinear") == 0) {
    //  std::cout << "Resizing using Bilinear interpolation" << std::endl;
    //  interpolation = std::make_unique<BilinearInterpolation<uint8_t>>(im.value());
  } else {
    //  std::cerr << "Invalid interpolation method." << std::endl;
    //  return 1;
  }

  //auto resized_image = resizer.Resize(interpolation.get(), new_width, new_height);
  visq::SaveImage(result_x, std::string(argv[2]) + "x.jpg", visq::ImageFormat::Jpeg);
  visq::SaveImage(result_y, std::string(argv[2]) + "y.jpg", visq::ImageFormat::Jpeg);
  return 0;
}

