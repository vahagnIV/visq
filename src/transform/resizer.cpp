#include "visq/transform/resizer.h"

namespace visq {

Image Resizer::Resize(const Image &image, size_t new_width, size_t new_height) const {
  Image resizedImage(new_width, new_height, image.GetChannels());
  Resize(image, resizedImage);
  return resizedImage;

}

} // visq