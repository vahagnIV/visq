#ifndef VISQPROJECT_INCLUDE_VISQ_FEATURES_I_KEYPOINT_DETECTOR_H_
#define VISQPROJECT_INCLUDE_VISQ_FEATURES_I_KEYPOINT_DETECTOR_H_

#include <vector>
#include <visq/image.h>
#include <visq/features/keypoint.h>

namespace visq::features {

template<typename T>
class IKeypointDetector {
 public:
  virtual ~IKeypointDetector() = default;
  virtual std::vector<KeyPoint> ExtractKeyPoints(const Image<T> & image) = 0;
};

} // features
// visq

#endif //VISQPROJECT_INCLUDE_VISQ_FEATURES_I_KEYPOINT_DETECTOR_H_
