#ifndef VISQPROJECT_INCLUDE_TRANSFORM_FILTER_H_
#define VISQPROJECT_INCLUDE_TRANSFORM_FILTER_H_

#include <cassert>
#include <visq/image.h>
#include <visq/transform/border_extension.h>
#include <visq/transform/border_extensions/border_extension_factory.h>
namespace visq {

/*!
 * @brief
 */
class Filter {
 public:
  template<typename T, typename K= T>
  static Image<decltype(std::declval<T>() * std::declval<K>())> Apply(const Image<K> * const kernel,
                                                                      const BorderExtension<T> * const image) {

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
          K value = K(0);
          for (long ky = -ky2; ky <= ky2; ++ky) {
            for (long kx = -kx2; kx <= kx2; ++kx) {
              value += kernel->At(ky + ky2, kx + ky2, 0) * image->At(y + ky, x + kx, c);
            }
          }
          result.Set(value,
                     y,
                     x,
                     c);
        }
      }
    }

    return result;
  }

  template<typename T, typename K= T>
  static Image<decltype(std::declval<T>() * std::declval<K>())> ApplySeparable(const Image<K> & kernel_x,
                                                                               const Image<K> & kernel_y,
                                                                               const Image<T> & image,
                                                                               BorderType border_type) {

    using ResultType = decltype(std::declval<T>() * std::declval<K>());

    // Ensure kernel_x and kernel_y are 1D
    assert(kernel_x.GetHeight() == 1 || kernel_x.GetWidth() == 1);
    assert(kernel_y.GetHeight() == 1 || kernel_y.GetWidth() == 1);

    size_t image_width = image.GetWidth();
    size_t image_height = image.GetHeight();

    auto extended_image = BorderExtensionFactory::Create(image, border_type);
    // Temporary image for intermediate results (horizontal filtering)
    Image<ResultType> temp_image(image_width, image_height, image.GetChannels());


    // Apply horizontal filter (kernel_x)
    for (int c = 0; c < image.GetChannels(); ++c) {
      for (int y = 0; y < image_height; ++y) {
        for (int x = 0; x < image_width; ++x) {

          ResultType value = 0;
          int kernel_size = kernel_x.GetWidth();
          for (int k = 0; k < kernel_size; ++k) {
            int src_x = x + k - kernel_size / 2;
            value += extended_image->At(y, src_x, c) * kernel_x.At(0, k, 0);
          }
          temp_image.Set(value, y, x, c);
        }
      }
    }

    auto tmp_image_extension = BorderExtensionFactory::Create(temp_image, border_type);
    Image<ResultType> result_image(image_width, image_height, image.GetChannels());

    // Apply vertical filter (kernel_y)
    for (int c = 0; c < image.GetChannels(); ++c) {
      for (int y = 0; y < image_height; ++y) {
        for (int x = 0; x < image_width; ++x) {
          ResultType value = 0;
          int kernel_size = kernel_y.GetHeight();
          for (int k = 0; k < kernel_size; ++k) {
            int src_y = y + k - kernel_size / 2;
            value += tmp_image_extension->At(src_y, x, c) * kernel_y.At(k, 0, 0);
          }
          result_image.Set(value, y, x, c);
        }
      }
    }
    return result_image;
  }

};

}

#endif // VISQPROJECT_INCLUDE_TRANSFORM_FILTER_H_
