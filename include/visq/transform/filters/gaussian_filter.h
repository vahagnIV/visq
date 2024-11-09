#ifndef VISQPROJECT_INCLUDE_VISQ_TRANSFORM_FILTERS_GAUSSIAN_FILTER_H_
#define VISQPROJECT_INCLUDE_VISQ_TRANSFORM_FILTERS_GAUSSIAN_FILTER_H_

#include <visq/image.h>

namespace visq::transform::filters {

Image<double> CreateGaussianFilter(double sigma, std::size_t size_x = 0, std::size_t size_y = 0);

} // filters
// transform
// visq

#endif //VISQPROJECT_INCLUDE_VISQ_TRANSFORM_FILTERS_GAUSSIAN_FILTER_H_
