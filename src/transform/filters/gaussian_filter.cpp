#include <cmath>
#include "include/visq/transform/filters/gaussian_filter.h"

namespace visq::transform::filters {

static Image<double> CreateGaussianFilterInternal(double sigma, std::size_t size_x, std::size_t size_y) {
  Image<double> result(size_x, size_y, 1);
  double total = 0;
  double inv_sigma2 = 1. / sigma / sigma;
  for (long i = 0; i <= size_y / 2; ++i) {
    for (long j = 0; j <= size_x / 2; ++j) {
      double value = std::exp(-(i * i + j * j) * inv_sigma2);
      result.Set(value, size_y / 2 + i, size_x / 2 + j, 0);
      total += 4 * value;
    }
  }
  total -= 3;
  for (long i = -static_cast<long>(size_y / 2); i <= static_cast<long>(size_y / 2); ++i) {
    for (long j = -static_cast<long>(size_x / 2); j <= static_cast<long>(size_x / 2); ++j) {
      double value = result.At(size_y / 2 + std::abs(i), size_x / 2 + std::abs(j), 0) / total;
      result.Set(value, size_y / 2 + i, size_x / 2 + j, 0);
    }
  }
  return result;
}

Image<double> CreateGaussianFilter(double sigma, std::size_t size_x, std::size_t size_y) {
  return CreateGaussianFilterInternal(sigma, size_x, size_y);
}

Image<double> CreateGaussianFilterSeparable(double sigma, std::size_t size) {
  Image<double> result(size, 1, 1);
  double total = 0;
  double inv_sigma2 = 1. / 2. / sigma / sigma;
  double coefficient = 1. /  std::sqrt(2 * M_PI ) / sigma;
  for (long i = 0; i <= size / 2; ++i) {
    auto distance = static_cast<double>( static_cast<double>(size / 2) - i );
    double value = coefficient * std::exp(-distance * distance * inv_sigma2);
    total += i == size / 2 ? value : 2 * value;
    result.Set(value, 0, i, 0);
    result.Set(value, 0, size - i - 1, 0);
  }

  return result;
}

} // filters
// transform
// visq