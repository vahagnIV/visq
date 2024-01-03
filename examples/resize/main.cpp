#include <iostream>
#include "visq/transform/resizer.h"
#include "visq/transform/nearest_neighbor_interpolation.h"
#include "visq/transform/bilinear_interpolation.h"
#include "io.h"

void PrintError() {
  std::cout << "Usage:\n" << "resize \"method\"(nearest, bilinear)  \"input_image\" \"output_image\" new_width new_height";
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


  Resizer<uint8_t> resizer;
  
  std::shared_ptr<Interpolation<uint8_t>> interpolation{nullptr};

  if(strcmp(argv[1], "bilinear") == 0)
    interpolation = std::make_shared<NearestNeighborInterpolation<uint8_t>>(im.value());
  else if(strcmp(argv[1], "nearest") == 0)
    interpolation = std::make_shared<BilinearInterpolation<uint8_t>>(im.value());  
  else {
    std::cerr << "Invalid interpolation method." << std::endl;
    return 1;
  }

  auto resized_image = resizer.Resize(interpolation, new_width, new_height);
  visq::SaveImage(resized_image, argv[3], visq::ImageFormat::Jpeg);

}

