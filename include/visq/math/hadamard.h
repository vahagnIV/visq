#ifndef VISQPROJECT_INCLUDE_MATH_HADAMARD_H_
#define VISQPROJECT_INCLUDE_MATH_HADAMARD_H_

#include <visq/image.h>

namespace visq::math {
template <typename T, typename K,
          typename O = decltype(std::declval<T>() * std::declval<K>())>
Image<O> HadamardProduct(const Image<T>& im1, const Image<K>& im2) {
  assert(im1.GetWidth() == im2.GetWidth());
  assert(im1.GetHeight() == im2.GetHeight());
  assert(im1.GetChannels() == im2.GetChannels());
  Image<O> result(im1.GetWidth(), im1.GetHeight(), im1.GetChannels());
  for (size_t y = 0; y < im1.GetHeight(); ++y) {
    for (size_t x = 0; x < im1.GetWidth(); ++x) {
      for (size_t c = 0; c < im1.GetChannels(); ++c) {
                    result.Set(im1.At(y,x,c) * im2.At(y,x,c),y,x,c);
      }
    }
  }
  return result;
}

}  // namespace visq::math

#endif  // VISQPROJECT_INCLUDE_MATH_HADAMARD_H_