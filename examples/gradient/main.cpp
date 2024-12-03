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
  
  auto sobel_x = transform::filters::CreateSobelX();
  auto sobel_y = transform::filters::CreateSobelY();
  

  Image<uint8_t> result_x = Filter::Apply(&sobel_x, &ext_image);
  Image<uint8_t> result_y = Filter::Apply(&sobel_y, &ext_image);

  visq::SaveImage(result_x, std::string(argv[2]) + "x.jpg", visq::ImageFormat::Jpeg);
  visq::SaveImage(result_y, std::string(argv[2]) + "y.jpg", visq::ImageFormat::Jpeg);
  return 0;
}

