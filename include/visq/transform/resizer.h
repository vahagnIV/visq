#ifndef VISQ_RESIZER_H
#define VISQ_RESIZER_H

#include <memory>

#include "visq/image.h"
#include "visq/transform/interpolation.h"

namespace visq {

template<typename T>
class Resizer {
public:

  Image<T> Resize(const std::shared_ptr<Interpolation<T>> & interpolation, size_t new_width, size_t new_height) const {
    Image<T> resizedImage(new_width, new_height, interpolation->GetImage().GetChannels());
    Resize(interpolation, resizedImage);
    return resizedImage;
  }

  void Resize(const std::shared_ptr<Interpolation<T>> & interpolation, Image<T> &image_to) const {
    double scale_x = static_cast<double>(interpolation->GetImage().GetWidth()) /  image_to.GetWidth();
    double scale_y = static_cast<double>(interpolation->GetImage().GetHeight()) /  image_to.GetHeight();
    for(size_t y = 0; y < image_to.GetWidth(); ++y) {
      double y_o = scale_y * y;
      for(size_t x = 0; x < image_to.GetHeight(); ++x) {
      double x_o = scale_x * x;
        for(size_t c = 0; c < image_to.GetChannels(); ++c) {
          image_to.Set(interpolation->Interpolate(y_o, x_o, c), y,x,c);
        }
      }
    }
  }
};

} // namespace visq

#endif // VISQ_RESIZER_H
