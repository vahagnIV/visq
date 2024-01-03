#ifndef VISQPROJECT_SRC_TRANSFORM_INTERPOLATION_H_
#define VISQPROJECT_SRC_TRANSFORM_INTERPOLATION_H_

#include <memory>
#include "visq/image.h"

namespace visq {

template<typename T>
class Interpolation {
public:
  Interpolation(const Image<T> & image): image_(image) {};
  virtual ~Interpolation() = default;
  [[nodiscard]] virtual T Interpolate(double y, double x, size_t channel) const = 0;
  [[nodiscard]] const Image<T> & GetImage() const { return image_; }
protected:
  const Image<T> image_; 
};

}

#endif // VISQPROJECT_SRC_TRANSFORM_INTERPOLATION_H_


