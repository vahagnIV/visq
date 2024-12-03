#ifndef VISQPROJECT_INCLUDE_VISQ_TRANSFORM_FILTERS_GRADIENT_H_
#define VISQPROJECT_INCLUDE_VISQ_TRANSFORM_FILTERS_GRADIENT_H_

#include <visq/image.h>

namespace visq::transform::filters {

Image<double> CreateSobelX();


Image<double> CreateSobelY();

} // filters
// transform
// visq

#endif //VISQPROJECT_INCLUDE_VISQ_TRANSFORM_FILTERS_GRADIENT_H_
