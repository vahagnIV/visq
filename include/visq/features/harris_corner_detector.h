#ifndef VISQPROJECT_INCLUDE_VISQ_FEATURES_HARRIS_CORNER_DETECTOR_H_
#define VISQPROJECT_INCLUDE_VISQ_FEATURES_HARRIS_CORNER_DETECTOR_H_

#include <visq/features/ikeypoint_detector.h>
#include <visq/math/hadamard.h>
#include <visq/transform/border_extensions/mirror_border.h>
#include <visq/transform/filter.h>
#include <visq/transform/filters/gradient.h>
#include <visq/utils/monochrome.h>
#include <visq/io.h>

#include <iostream>
namespace visq::features {

template<typename T>
class HarrisCornerDetector : public IKeypointDetector<T> {
  size_t window_size_ = 3;
  double k_ = 0.04;
  Image<double> sum_kernel;

 public:
  HarrisCornerDetector() : sum_kernel(transform::filters::CreateGaussianFilterSeparable(3, 3)) {
  }

  std::vector<KeyPoint> ExtractKeyPoints(const Image<T> &image) override {
    if (image.GetWidth() < 2 * window_size_ + 1 ||
        image.GetHeight() < 2 * window_size_ + 1)
      return {};

    if (image.GetChannels() != 1 && image.GetChannels() != 3) return {};

    if (image.GetChannels() == 1) return ExtractKeyPointsImpl(image);
    return ExtractKeyPointsImpl(utils::ToMonochrome<T, double>(image));
  }

 private:
  void SaveNormalized(const Image<double> &image, const std::string &path) const {
    double max = image.Max();
//    double min = image.Min();
    double min = 0;//image.Min();
    double scale = 255. / (max - min);
    Image<uint8_t> normalized(image.GetWidth(), image.GetHeight(), 1);
    for (int i = 0; i < image.GetHeight(); ++i) {
      for (int j = 0; j < image.GetWidth(); ++j) {

        double value = std::max(0., (image.At(i, j, 0) - min) * scale);
        normalized.Set(value, i, j, 0);
      }
    }
    SaveImage(normalized, path, ImageFormat::Jpeg);
  }

  Image<double> ComputeSlidingSum(const Image<double> &input) {
    border_extensions::MirrorBorder<uint8_t> ext_image(input);
//    Image<double> sum_kernel(window_size_, window_size_, 1, 1.);
    return Filter::ApplySeparable<double, double>(sum_kernel, sum_kernel.Transpose(), input, BorderType::Mirror);
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
        double m11 = Ix2Sum.At(y, x, 0);
        double m22 = Iy2Sum.At(y, x, 0);
        double m12 = IxIySum.At(y, x, 0);
        double m21 = m12;

        double det_M = m11 * m22 - m12 * m21;
        double trace_M = m11 + m22;

        R.Set(det_M - k_ * trace_M * trace_M, y, x, 0);
      }
    }
//    SaveNormalized(R, "/home/vahagn/Pictures/R.jpg");

    double threshold = 0.01 * R.Max();
    std::vector<KeyPoint> result;
    for (size_t y = window_size_; y < input.GetHeight() - window_size_; ++y) {
      for (size_t x = window_size_; x < input.GetWidth() - window_size_; ++x) {
        double value = R.At(y, x, 0);
        if (value > threshold
            && value > R.At(y - 1, x, 0)
            && value > R.At(y - 1, x - 1, 0)
            && value > R.At(y, x - 1, 0)
            && value > R.At(y + 1, x - 1, 0)
            && value > R.At(y + 1, x, 0)
            && value > R.At(y + 1, x + 1, 0)
            && value > R.At(y, x + 1, 0)
            && value > R.At(y - 1, x + 1, 0)) {
          std::cout << "Value: " << value
                    << " R(y-1,x):" << R.At(y - 1, x, 0)
                    << " R(y-1,x-1):" << R.At(y - 1, x - 1, 0)
                    << " R(y,x-1):" << R.At(y, x - 1, 0)
                    << " R(y+1,x-1):" << R.At(y + 1, x - 1, 0)
                    << " R(y+1,x):" << R.At(y + 1, x, 0)
                    << " R(y+1,x+1):" << R.At(y + 1, x + 1, 0)
                    << " R(y,x+1):" << R.At(y, x + 1, 0)
                    << " R(y-1,x+1):" << R.At(y - 1, x + 1, 0)
                    << std::endl;
          result.push_back(KeyPoint{
              .pt = geometry::Point2D<double>(x, y),
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
