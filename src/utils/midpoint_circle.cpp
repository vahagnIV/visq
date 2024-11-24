#include "include/visq/utils/midpoint_circle.h"

namespace {
void ExpandToQuarant(std::vector<visq::geometry::Point2D<int>> &pts) {
  for (int i = pts.size() - 1; i >= 0; --i) {
    if (pts[i].x != pts[i].y)
      pts.emplace_back(pts[i].y, pts[i].x);
  }
}

void ExpandToSemiCircle(std::vector<visq::geometry::Point2D<int>> &pts) {
  for (int i = pts.size() - 2; i >= 0; --i) {
    pts.emplace_back(pts[i].y, -pts[i].x);
  }
}

void ExpandToCircle(std::vector<visq::geometry::Point2D<int>> &pts) {
  for (int i = pts.size() - 2; i > 0; --i) {
    pts.emplace_back(pts[i].x, -pts[i].y);
  }
}
}

namespace visq::utils {
std::vector<geometry::Point2D<int>> CirclePixels(unsigned int radius) {
  int t1 = radius / 16;
  int x = radius;
  int y = 0;
  std::vector<geometry::Point2D<int>> result = {{x, y}};

  while (y < x) {
    //Pixel (x, y) and all symmetric pixels are colored (8 times)
    y = y + 1;
    t1 = t1 + y;
    int t2 = t1 - x;
    if (t2 >= 0) {
      t1 = t2;
      x = x - 1;
    }
    result.emplace_back(x, y);

  }
  ExpandToQuarant(result);
  ExpandToSemiCircle(result);
  ExpandToCircle(result);
  return result;
}
} // utils
// visq