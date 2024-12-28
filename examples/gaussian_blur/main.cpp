#include <iostream>
#include "visq/transform/border_extensions/constant_border.h"
#include "visq/transform/border_extensions/mirror_border.h"
#include "visq/transform/filter.h"
#include "visq/transform/filters/gaussian_filter.h"
#include "io.h"

void PrintError() {
  std::cout << "Usage:\n"
            << "gaussian_blur \"border-method\"(constant, mirror)  \"input_image\" \"output_image\" kernel_width kernel_height";
}

using namespace visq;

int main(int argc, char * argv[]) {
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

  Image<double> kernel = transform::filters::CreateGaussianFilterSeparable(3.5, 17);
  Image<double> transposed = kernel.Transpose();
//  Image<uint8_t> image(100, 100, 3);

  border_extensions::ConstantBorder<uint8_t> ext_image(im.value());
  Image<uint8_t> result = Filter::ApplySeparable(kernel, transposed, im.value(), BorderType::Mirror);

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
  visq::SaveImage(result, argv[3], visq::ImageFormat::Jpeg);
  return 0;
}

