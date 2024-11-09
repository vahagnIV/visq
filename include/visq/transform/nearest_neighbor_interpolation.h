#ifndef VISQPROJECT_SRC_TRANSFORM_NEAREST_NEIGHBOR_INTERPOLATION_H_
#define VISQPROJECT_SRC_TRANSFORM_NEAREST_NEIGHBOR_INTERPOLATION_H_

#include <cmath>
#include <visq/transform/sampler.h>

namespace visq {

template<typename T>
class NearestNeighborInterpolation: public Sampler<T> {
public:
  explicit NearestNeighborInterpolation(const Image<T> & image): Sampler<T>(image) {}
 
  [[nodiscard]] uint8_t Interpolate(double y, double x, size_t channel) const override {
    y = std::max(0., y);
    y = std::min(static_cast<double>(this->image_.GetHeight()), y);

    x = std::max(0., x);
    x = std::min(static_cast<double>(this->image_.GetWidth()), x);

    auto y_int = static_cast<size_t>(std::round(y));
    auto x_int = static_cast<size_t>(std::round(x));

    return this->image_.At(y_int, x_int, channel);    
  }
};

}

#endif // VISQPROJECT_SRC_TRANSFORM_NEAREST_NEIGHBOR_INTERPOLATION_H_
