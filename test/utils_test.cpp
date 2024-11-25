#include "utils_test.h"
#include <visq/utils/midpoint_circle.h>


namespace visq::test {


TEST(UtilsTest, MidpontCircle3px){
  auto pts = utils::CirclePixels(3);
  ASSERT_EQ(16, pts.size());
  std::vector<geometry::Point2D<int>> expected{
					geometry::Point2D<int>(3,0),
					geometry::Point2D<int>(3,1),
					geometry::Point2D<int>(2,2),
					geometry::Point2D<int>(1,3),
					geometry::Point2D<int>(0,3),
					geometry::Point2D<int>(-1,3),
					geometry::Point2D<int>(-2,2),
					geometry::Point2D<int>(-3,1),
					geometry::Point2D<int>(-3,0),
					geometry::Point2D<int>(-3,-1),
					geometry::Point2D<int>(-2,-2),
					geometry::Point2D<int>(-1,-3),
					geometry::Point2D<int>(0,-3),
					geometry::Point2D<int>(1,-3),
					geometry::Point2D<int>(2,-2),
					geometry::Point2D<int>(3,-1)};
  ASSERT_EQ(pts, expected);
}

} // test
// visq
