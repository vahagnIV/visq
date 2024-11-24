#include "utils_test.h"
#include <visq/utils/midpoint_circle.h>

namespace visq::test {

TEST(UtilsTest, MidpontCircle3px){
  auto pts = utils::CirclePixels(3);

  ASSERT_EQ(pts, std::vector<geometry::Point2D<int>>{{3,0}});
}
} // test
// visq