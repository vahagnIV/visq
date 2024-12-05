#ifndef VISQPROJECT_INCLUDE_VISQ_FEATURES_HARRIS_CORNER_DETECTOR_H_
#define VISQPROJECT_INCLUDE_VISQ_FEATURES_HARRIS_CORNER_DETECTOR_H_

#include <visq/features/ikeypoint_detector.h>
#include <visq/math/hadamard.h>
#include <visq/transform/border_extensions/mirror_border.h>
#include <visq/transform/filter.h>
#include <visq/transform/filters/gradient.h>
#include <visq/utils/monochrome.h>

#include <iostream>
namespace visq::features {

template <typename T>
class HarrisCornerDetector : public IKeypointDetector<T> {
  size_t window_size_ = 3;
  double k_ = 0.04;

 public:
  HarrisCornerDetector() {}

  std::vector<KeyPoint> ExtractKeyPoints(const Image<T> &image) override {
    if (image.GetWidth() < 2 * window_size_ + 1 ||
        image.GetHeight() < 2 * window_size_ + 1)
      return {};

    if (image.GetChannels() != 1 && image.GetChannels() != 3) return {};

    if (image.GetChannels() == 1) return ExtractKeyPointsImpl(image);
    return ExtractKeyPointsImpl(utils::ToMonochrome<T, double>(image));
  }

 private:
  Image<double> ComputeSlidingSum(const Image<double> &input) {
    border_extensions::MirrorBorder<uint8_t> ext_image(input);
    Image<double> sum_kernel(window_size_, window_size_, 1, 1.);
    return Filter::Apply(&sum_kernel, &ext_image);
  }

  std::vector<KeyPoint> ExtractKeyPointsImpl(const Image<double> &input) {
    border_extensions::MirrorBorder<uint8_t> ext_image(input);

    auto sobel_x = transform::filters::CreateSobelX();
    auto sobel_y = transform::filters::CreateSobelY();

    Image<double> Ix = Filter::Apply(&sobel_x, &ext_image);
    Image<double> Iy = Filter::Apply(&sobel_y, &ext_image);

    auto Ix2 = math::HadamardProduct(Ix, Ix);
    auto Iy2 = math::HadamardProduct(Iy, Iy);
    auto IxIy = math::HadamardProduct(Ix, Iy);

    auto Ix2Sum = ComputeSlidingSum(Ix2);
    auto Iy2Sum = ComputeSlidingSum(Iy2);
    auto IxIySum = ComputeSlidingSum(IxIy);


    Image<double> R(input.GetWidth(), input.GetHeight(), 1);

    for (size_t y = 0; y < input.GetHeight(); ++y) {
      for (size_t x = 0; x < input.GetWidth(); ++x) {
        double det_M = Ix2Sum.At(y, x, 0) * Iy2Sum.At(y, x, 0) - IxIySum.At(y, x, 0) * IxIySum.At(y, x, 0);
        double trace_M = Ix2Sum.At(y, x, 0)  + Iy2Sum.At(y, x, 0);
        R.Set(det_M - k_ * trace_M,y,x,0 );
      }
    }
    std::vector<KeyPoint> result;
    for (size_t y = window_size_; y < input.GetHeight()-window_size_; ++y) {
      for (size_t x = window_size_; x < input.GetWidth()-window_size_; ++x) {
        double value = R.At(y,x,0);
        if(value > 1000000 && value > R.At(y-1,x,0) && value > R.At(y-1,x-1,0) && value > R.At(y,x-1,0) && value > R.At(y+1,x-1,0) && value > R.At(y+1,x,0) && value > R.At(y+1,x+1,0) && value > R.At(y,x+1,0) && value > R.At(y-1,x+1,0)){
            std::cout << "Value: " << value << std::endl;
            result.push_back(KeyPoint{
                .pt = geometry::Point2D<double>(x,y),
                .strength = value
            });
        }
      }
    }

    return result;
  }
};

}  // namespace visq::features
// visq

#endif  // VISQPROJECT_INCLUDE_VISQ_FEATURES_HARRIS_CORNER_DETECTOR_H_
