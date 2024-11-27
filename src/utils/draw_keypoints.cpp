#include <visq/utils/draw_keypoints.h>
#include <visq/utils/midpoint_circle.h>


namespace visq::utils{

void DrawKeypoints(const std::vector<features::KeyPoint> & key_points, Image<uint8_t> & target, Color color, unsigned radius){

  auto circle = CirclePixels(radius);
  
  for(const auto & kp: key_points) {
    const auto & pt = kp.pt;
    for(const auto & cp: circle) {
      size_t x = pt.x + cp.x;
      size_t y = pt.y + cp.y; 
      if(x < target.GetWidth() && y < target.GetHeight()){
        target.Set(color.red, y, x, 0);
        target.Set(color.green, y, x, 1);
        target.Set(color.blue, y, x, 2);
      }
    }
  }

}

}
