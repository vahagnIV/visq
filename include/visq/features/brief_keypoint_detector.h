#ifndef VISQPROJECT_INCLUDE_VISQ_FEATURES_BRIEF_KEYPOINT_DETECTOR_H_
#define VISQPROJECT_INCLUDE_VISQ_FEATURES_BRIEF_KEYPOINT_DETECTOR_H_

#include <visq/features/ikeypoint_detector.h>
namespace visq::features {

template<typename T>
class BRIEFKeypointDetector : public IKeypointDetector<T> {
 public:
  std::vector<geometry::Point2D<double>> ExtractKeyPoints(const Image<T> &image) override {
    if (image.GetWidth() < 5 || image.GetHeight() < 5)
      return {};

    if (image.GetChannels() != 1 && image.GetChannels() != 3)
      return {};

    Image<double> monochrome = image.GetChannels() == 1 ? image : GetMonochrome(image);

    int total_greater = 0;

    for (size_t y = 2; y < image.GetHeight(); ++y) {
      for (int x = 2; x < image.GetWidth(); ++x) {
        double value = image.At(y, x, 0);
        if (image.At(y - 2, x - 1, 0) > value)
          ++total_greater;
      }
    }

    return std::vector<geometry::Point2D<double>>();
  }
 private:
  Image<double> GetMonochrome(const Image<T> &image) {
    assert(image.GetChannels() == 3);
    Image<double> output(image.GetWidth(), image.GetHeight(), 1);
    for (size_t y = 0; y < image.GetHeight(); ++y) {
      for (size_t x = 0; x < image.GetWidth(); ++x) {
        output.Set(0.299 * image.At(y, x, 0) + 0.587 * image.At(y, x, 1) + 0.114 * *image.At(y, x, 2), y, x, 0);
      }
    }
    return output;
  }
};

} // features
// visq

#endif //VISQPROJECT_INCLUDE_VISQ_FEATURES_BRIEF_KEYPOINT_DETECTOR_H_
