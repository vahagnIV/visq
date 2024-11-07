#ifndef VISQ_RESIZER_H
#define VISQ_RESIZER_H

#include <memory>

#include "visq/image.h"
#include <visq/transform/sampler.h>

namespace visq {

template<typename T>
class Resizer {
public:

  Image<T> Resize(const std::shared_ptr<Sampler<T>> & sampler, size_t new_width, size_t new_height) const {
    Image<T> resizedImage(new_width, new_height, sampler->GetImage().GetChannels());
    Resize(sampler, resizedImage);
    return resizedImage;
  }

  void Resize(const std::shared_ptr<Sampler<T>> & sampler, Image<T> &image_to) const {
    double scale_x = static_cast<double>(sampler->GetImage().GetWidth()) /  image_to.GetWidth();
    double scale_y = static_cast<double>(sampler->GetImage().GetHeight()) /  image_to.GetHeight();
    for(size_t y = 0; y < image_to.GetHeight(); ++y) {
      double y_o = scale_y * y;
      for(size_t x = 0; x < image_to.GetWidth(); ++x) {
      double x_o = scale_x * x;
        for(size_t c = 0; c < image_to.GetChannels(); ++c) {
          image_to.Set(sampler->Interpolate(y_o, x_o, c), y,x,c);
        }
      }
    }
  }
};

} // namespace visq

#endif // VISQ_RESIZER_H
