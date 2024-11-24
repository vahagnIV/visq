#ifndef VISQPROJECT_INCLUDE_VISQ_FEATURES_I_KEYPOINT_DETECTOR_H_
#define VISQPROJECT_INCLUDE_VISQ_FEATURES_I_KEYPOINT_DETECTOR_H_

#include <vector>
#include <visq/image.h>
#include <visq/geometry/point_2d.h>

namespace visq {
namespace features {

template<typename T>
class IKeypointDetector {
 public:
  virtual ~IKeypointDetector() = default;
  virtual std::vector<geometry::Point2D<double>> ExtractKeyPoints(const Image<T> & image) = 0;
};

} // features
} // visq

#endif //VISQPROJECT_INCLUDE_VISQ_FEATURES_I_KEYPOINT_DETECTOR_H_
