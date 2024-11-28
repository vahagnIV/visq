#ifndef VISQPROJECT_INCLUDE_VISQ_FEATURES_BRIEF_KEYPOINT_DETECTOR_H_
#define VISQPROJECT_INCLUDE_VISQ_FEATURES_BRIEF_KEYPOINT_DETECTOR_H_

#include <visq/features/ikeypoint_detector.h>
#include <visq/utils/midpoint_circle.h>

#include "visq/transform/border_extensions/mirror_border.h"
#include "visq/transform/filter.h"
#include "visq/transform/filters/gaussian_filter.h"

#include <iostream>
namespace visq::features {

template<typename T>
class BRIEFKeypointDetector : public IKeypointDetector<T> {
  const unsigned circle_size_;
  std::vector<geometry::Point2D<int>> circle_; 
  double count_threshold_percent_;
  double value_threshold_;
 public:
  BRIEFKeypointDetector(unsigned circle_size = 3, double count_threshold_percent = 12./16., double value_threshold = 1.): circle_size_(circle_size), count_threshold_percent_(count_threshold_percent), value_threshold_(value_threshold) {
    circle_ = utils::CirclePixels(circle_size);
    std::cout << "Circle size: " << circle_.size() << std::endl;
  }

  std::vector<KeyPoint> ExtractKeyPoints(const Image<T> &image) override {
    if (image.GetWidth() < 2 * circle_size_+ 1 || image.GetHeight() < 2 * circle_size_ + 1)
      return {};

    if (image.GetChannels() != 1 && image.GetChannels() != 3)
      return {};

    if(image.GetChannels() == 1)
      return ExtractKeyPointsImpl(image);
    return ExtractKeyPointsImpl(GetMonochrome(image));    
  }
 private:

  std::vector<KeyPoint> ExtractKeyPointsImpl(const Image<double> &input){
    size_t count_threshold = count_threshold_percent_ * circle_.size();
    Image<double> kernel = transform::filters::CreateGaussianFilter(3, 3, 3);

    border_extensions::MirrorBorder<double> ext_image(input);
    Image<double> image = Filter::Apply(&kernel, &ext_image);

    std::cout << "Count threashold: " << count_threshold << std::endl; 
    std::vector<KeyPoint> result;

    for (size_t y = circle_size_; y < image.GetHeight() - circle_size_ - 1; ++y) {
      for (int x = circle_size_; x < image.GetWidth() - circle_size_- 1; ++x) {
        double value = image.At(y, x, 0) + value_threshold_;
        // std::cout << "V: " << value << std::endl;

        int total_greater = 0;
        for(const auto & p: circle_){
          //std::cout << image.At(y + p.y, x + p.x,0) << std::endl;
          if(image.At(y + p.y, x + p.x,0) > value) { 
            if(++total_greater > count_threshold){
              result.emplace_back(KeyPoint{.pt = geometry::Point2D<double>(x,y)});
              break;
            }
          }
          else
            total_greater = 0;
        }
      }
    }
   

    return result;
  }

  Image<double> GetMonochrome(const Image<T> &image) {
    assert(image.GetChannels() == 3);
    Image<double> output(image.GetWidth(), image.GetHeight(), 1);
    for (size_t y = 0; y < image.GetHeight(); ++y) {
      for (size_t x = 0; x < image.GetWidth(); ++x) {
        output.Set(0.299 * image.At(y, x, 0) + 0.587 * image.At(y, x, 1) + 0.114 *image.At(y, x, 2), y, x, 0);
      }
    }
    return output;
  }
};

} // features
// visq

#endif //VISQPROJECT_INCLUDE_VISQ_FEATURES_BRIEF_KEYPOINT_DETECTOR_H_
