#ifndef VISQPROJECT_INCLUDE_MATH_DOT_H_
#define VISQPROJECT_INCLUDE_MATH_DOT_H_

#include <visq/image.h>

namespace visq::math {
template <typename T, typename K,
          typename O = decltype(std::declval<T>() * std::declval<K>())>
Image<O> Dot(const Image<T>& im1, const Image<K>& im2) {
  assert(im1.GetWidth() == im2.GetHeight());
  assert(im1.GetChannels() == 1);
  assert(im2.GetChannels() == 1);
  Image<O> result(im2.GetWidth(), im1.GetHeight(), 1);

  for (size_t y = 0; y < result.GetHeight(); ++y) {
    for (size_t x = 0; x < result.GetWidth(); ++x) {
      O val = O(0);
      for (size_t c = 0; c < im1.GetWidth(); ++c) {
        val += im1.At(y, c, 0) * im2.At(c, x0);
      }
      result.Set(val, y, x, 0);
    }
  }
  return result;
}

}  // namespace visq::math

#endif  // VISQPROJECT_INCLUDE_MATH_DOT_H_