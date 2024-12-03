#ifndef VISQPROJECT_INCLUDE_TRANSFORM_FILTER_H_
#define VISQPROJECT_INCLUDE_TRANSFORM_FILTER_H_

#include <cassert>
#include <visq/image.h>
#include <visq/transform/border_extension.h>
namespace visq {

/*!
 * @brief
 */
class Filter {
 public:
  template<typename T, typename K= T>
  static Image<decltype(std::declval<T>() * std::declval<K>())> Apply(const Image<K> *const kernel,
                                                                      const BorderExtension<T> *const image) {

    assert((kernel->GetWidth() & 1) == 1);
    assert((kernel->GetHeight() & 1) == 1);
    assert(kernel->GetChannels() == 1);

    typedef decltype(std::declval<T>() * std::declval<K>()) result_t;
    Image<result_t> result(image->GetWidth(), image->GetHeight(), image->GetChannels(), result_t(0));

    long kx2 = kernel->GetWidth() / 2;
    long ky2 = kernel->GetHeight() / 2;

//#pragma omp parallel for
    for (long y = 0; y < image->GetHeight(); ++y) {
//#pragma omp parallel for
      for (long x = 0; x < image->GetWidth(); ++x) {
//#pragma omp parallel for
        for (size_t c = 0; c < image->GetChannels(); ++c) {

          for (long ky = -ky2; ky <= ky2; ++ky) {
            for (long kx = -kx2; kx <= kx2; ++kx) {
              result.Set(result.At(y, x, c) + kernel->At(ky + ky2, kx + ky2, 0) * image->At(y + ky, x + kx, c),
                         y,
                         x,
                         c);
            }
          }
        }
      }
    }

    return result;
  }

};

}

#endif // VISQPROJECT_INCLUDE_TRANSFORM_FILTER_H_
