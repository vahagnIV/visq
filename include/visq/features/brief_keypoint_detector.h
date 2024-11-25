#ifndef VISQPROJECT_INCLUDE_VISQ_FEATURES_BRIEF_KEYPOINT_DETECTOR_H_
#define VISQPROJECT_INCLUDE_VISQ_FEATURES_BRIEF_KEYPOINT_DETECTOR_H_

#include <visq/features/ikeypoint_detector.h>
#include <visq/utils/midpoint_circle.h>


namespace visq::features {

template<typename T>
class BRIEFKeypointDetector : public IKeypointDetector<T> {
  const unsigned circle_size_;
  std::Point2D<int> circle_; 
 public:
  BRIEFKeypointDetector(unsigned circle_size = 3): circle_size_(circle_size){
    circle_ = utils::CirclePixels(circle_size);
  }

  std::vector<geometry::Point2D<double>> ExtractKeyPoints(const Image<T> &image) override {
    if (image.GetWidth() < 2 * circle_size_+ 1 || image.GetHeight() < 2 * circle_size_ + 1)
      return {};

    if (image.GetChannels() != 1 && image.GetChannels() != 3)
      return {};

    Image<double> monochrome = image.GetChannels() == 1 ? image : GetMonochrome(image);


    for (size_t y = ; y < image.GetHeight(); ++y) {
      for (int x = 2; x < image.GetWidth(); ++x) {
        double value = image.At(y, x, 0);
        int total_greater = 0;
        for(const auto & p: circles_){
          if(image.At(y + p.y, x + p.x,0) > value) ++total_greater;
        }
        if ( total_greater > 10)
           result.emplace_back(x,y);
      }
    }

    return result;
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
