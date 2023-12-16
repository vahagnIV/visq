#include <iostream>
#include "visq/transform/bilinear_resizer.h"
#include "visq/io.h"

void PrintError() {
  std::cout << "Usage:\n" << "resize \"input_image\" \"output_image\" new_width new_height";
}

int main(int argc, char *argv[]) {
  if (argc < 5) {
    PrintError();
    return 1;
  }

  auto [err, im] = visq::LoadImage(argv[1]);
  if (err == visq::ErrorCode::InvalidFormat) {
    std::cout << "Format not supported" << std::endl;
    return 1;
  }

  if (err == visq::ErrorCode::FileNotFound) {
    std::cout << "Could not find the provided file: " << argv[1] << std::endl;
    return 1;
  }

  char *error;
  size_t new_width = std::strtol(argv[3], &error, 10);
  size_t new_height = std::strtol(argv[4], &error, 10);

  visq::BilinearResizer resizer;
  visq::Image resized_image = resizer.visq::Resizer::Resize(im.value(), new_width, new_height);
  visq::SaveImage(resized_image, argv[2], visq::ImageFormat::Jpeg);

}

