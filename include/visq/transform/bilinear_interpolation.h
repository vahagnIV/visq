#ifndef VISQPROJECT_SRC_TRANSFORM_BILINEAR_INTERPOLATION_H_
#define VISQPROJECT_SRC_TRANSFORM_BILINEAR_INTERPOLATION_H_

#include <cmath>
#include <visq/transform/sampler.h>

namespace visq {

template<typename T>
class BilinearInterpolation : public Sampler<T> {
 public:
  BilinearInterpolation(const Image<T> &image) : Sampler<T>(image) {}

  [[nodiscard]] T Interpolate(double y, double x, size_t channel) const override {

    size_t rx = std::min(static_cast<size_t>(std::floor(std::max(0., x))), this->image_.GetWidth() - 1);
    size_t ty = std::min(static_cast<size_t>(std::floor(std::max(0., y))), this->image_.GetHeight() - 1);

    size_t lx = rx == this->image_.GetWidth() - 1 ? rx : rx + 1;
    size_t by = ty == this->image_.GetHeight() - 1 ? ty : ty + 1;

    double value_at_top =
        InterpolateOnZeroOneInterval(this->image_.At(ty, rx, channel), this->image_.At(ty, lx, channel), x - rx);
    double value_at_bottom =
        InterpolateOnZeroOneInterval(this->image_.At(by, rx, channel), this->image_.At(by, lx, channel), x - rx);

    double result = InterpolateOnZeroOneInterval(value_at_top, value_at_bottom, y - ty);

    result = std::max(static_cast<double>(std::numeric_limits<T>::min()),
                      std::min(static_cast<double>(std::numeric_limits<T>::max()), result));
    return static_cast<T>(result);
  }

 private:
  double InterpolateOnZeroOneInterval(double value_at_zero, double value_at_one, double x) const {
    return (value_at_one - value_at_zero) * x + value_at_zero;
  }

};

} // visq

#endif //VISQPROJECT_SRC_TRANSFORM_BILINEAR_INTERPOLATION_H_
