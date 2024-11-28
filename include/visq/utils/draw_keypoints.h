#ifndef VISQPROJECT_INCLUDE_VISQ_UTILS_DRAW_KEYPOINTS_H_
#define VISQPROJECT_INCLUDE_VISQ_UTILS_DRAW_KEYPOINTS_H_

#include <vector>
#include <visq/features/keypoint.h>
#include <visq/image.h>
#include <visq/utils/color.h>

namespace visq::utils {

void DrawKeypoints(const std::vector<features::KeyPoint> & key_points, Image<uint8_t> & target, Color color = Color(0, 255, 0), unsigned radius = 2); 

} // utils
// visq

#endif //VISQPROJECT_INCLUDE_VISQ_UTILS_DRAW_KEYPOINTS_H_
