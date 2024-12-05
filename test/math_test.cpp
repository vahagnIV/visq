#include "math_test.h"

#include <visq/image.h>
#include <visq/math/hadamard.h>

namespace visq::test {

TEST_F(MathTest, CorrectlyCompuesHadamardProduct) {
  Image<int> im1(2, 3, 1);
  im1.Set(1., 0, 0, 0);
  im1.Set(2., 0, 1, 0);
  im1.Set(3., 1, 0, 0);
  im1.Set(4., 1, 1, 0);
  im1.Set(5., 2, 0, 0);
  im1.Set(6., 2, 1, 0);
  Image<int> im2(2, 3, 1);
  im2.Set(6., 0, 0, 0);
  im2.Set(5., 0, 1, 0);
  im2.Set(4., 1, 0, 0);
  im2.Set(3., 1, 1, 0);
  im2.Set(2., 2, 0, 0);
  im2.Set(1., 2, 1, 0);

  auto result = math::HadamardProduct(im1, im2);

  ASSERT_DOUBLE_EQ(result.At(0,0,0), 6.);
}

}  // namespace visq::test