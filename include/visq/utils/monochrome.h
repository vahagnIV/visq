#ifndef VISQPROJECT_INCLUDE_VISQ_UTILS_MONOCHROME_H_
#define VISQPROJECT_INCLUDE_VISQ_UTILS_MONOCHROME_H_

#include <visq/image.h>

namespace visq::utils {
template <typename T, typename O = T>
Image<T> ToMonochrome(const Image<T>& image) {
  if(image.GetChannels() == 1) return image;
  if(image.GetChannels() != 3) return image; // What shoud we do
  
  Image<O> output(image.GetWidth(), image.GetHeight(), 1);
  for (size_t y = 0; y < image.GetHeight(); ++y) {
    for (size_t x = 0; x < image.GetWidth(); ++x) {
      output.Set(0.299 * image.At(y, x, 0) + 0.587 * image.At(y, x, 1) +
                     0.114 * image.At(y, x, 2),
                 y, x, 0);
    }
  }
  return output;
}

}  // namespace visq::utils

#endif  // VISQPROJECT_INCLUDE_VISQ_UTILS_MONOCHROME_H_