#ifndef VISQ_RESIZER_H
#define VISQ_RESIZER_H

#include "visq/image.h"

namespace visq {

class Resizer {
 public:
  virtual ~Resizer() = default;

  virtual Image Resize(const Image &image, size_t new_width, size_t new_height) const;

  // Resize an image using the implemented interpolation method
  virtual void Resize(const Image &image_from, Image &image_to) const = 0;
};

} // namespace visq

#endif // VISQ_RESIZER_H
