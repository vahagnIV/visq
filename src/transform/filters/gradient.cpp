#include <visq/transform/filters/gradient.h>

namespace visq::transform::filters {
Image<double> CreateSobelX() {
  Image<double> result(3, 3, 1);
  result.Set(1., 0, 0, 0);
  result.Set(0., 0, 1, 0);
  result.Set(-1., 0, 2, 0);

  result.Set(2., 1, 0, 0);
  result.Set(0., 1, 1, 0);
  result.Set(-2., 1, 2, 0);

  result.Set(1., 2, 0, 0);
  result.Set(0., 2, 1, 0);
  result.Set(-1., 2, 2, 0);
  return result;
}

Image<double> CreateSobelY() {
  Image<double> result(3, 3, 1);
  result.Set(1., 0, 0, 0);
  result.Set(2., 0, 1, 0);
  result.Set(1., 0, 2, 0);

  result.Set(0., 1, 0, 0);
  result.Set(0., 1, 1, 0);
  result.Set(0., 1, 2, 0);

  result.Set(-1., 2, 0, 0);
  result.Set(-2., 2, 1, 0);
  result.Set(-1., 2, 2, 0);
  return result;
}
}  // namespace visq::transform::filters
