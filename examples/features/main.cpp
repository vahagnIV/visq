#include <iostream>

#include "io.h"
#include "visq/features/fast_keypoint_detector.h"
#include "visq/features/harris_corner_detector.h"
#include "visq/utils/draw_keypoints.h"

void PrintError() {
  std::cout << "Usage:\n"
            << "features \"method\"(nearest, bilinear)  \"input_image\" "
               "\"output_image\""
            << std::endl;
}

using namespace visq;

int main(int argc, char *argv[]) {
  if (argc < 4) {
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

  std::cout << "Read input image. Width: " << im.value().GetWidth()
            << " Height: " << im.value().GetHeight() << std::endl;

  std::unique_ptr<features::IKeypointDetector<uint8_t>> kp_detector;

  if (strcmp(argv[1], "brief") == 0) {
    std::cout << "Extracting keypoints with BRIEF" << std::endl;
    kp_detector = std::make_unique<features::FASTKeypointDetector<uint8_t>>();
  } else if (strcmp(argv[1], "harris") == 0) {
    std::cout << "Extracting keypoints with Harris" << std::endl;
    kp_detector = std::make_unique<features::HarrisCornerDetector<uint8_t>>();
  } else {
    std::cerr << "Invalid interpolation method." << std::endl;
    return 1;
  }

  Image<uint8_t> image = im.value();

//  std::cout <<"Applying Gaussian filter" << std::endl;
//  Image<double> kernel = transform::filters::CreateGaussianFilter(20, 11, 11);
//  border_extensions::MirrorBorder<uint8_t> ext_image(image);
//  image = Filter::Apply(&kernel, &ext_image);
//  std::cout << "Done" << std::endl;


  auto keypoints = kp_detector->ExtractKeyPoints(image);
  std::cout << "Found " << keypoints.size() << " keypoints." << std::endl;
  utils::DrawKeypoints(keypoints, image);

  visq::SaveImage(image, argv[3], visq::ImageFormat::Jpeg);
}
