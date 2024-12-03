#ifndef VISQPROJECT_FEATURES_KEYPOINT_H_
#define VISQPROJECT_FEATURES_KEYPOINT_H_

#include <visq/geometry/point_2d.h>

namespace visq::features{


struct KeyPoint{
  geometry::Point2D<double> pt;
  double angle;
};

} // visq::features

#endif // VISQPROJECT_FEATURES_KEYPOINT_H_
