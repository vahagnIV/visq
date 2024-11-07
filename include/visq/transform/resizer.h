#ifndef VISQ_RESIZER_H
#define VISQ_RESIZER_H

#include <visq/image.h>
#include <visq/transform/sampler.h>

namespace visq {
/*!
 * @brief Resizes image from Sampler
 */
template<typename T>
class Resizer {
public:

  /*!
   * @Brief Resizes the image and returns the new one.
   * @param sampler The sampler of original image.
   * @param new_width The width of the resized image.
   * @param new_height The height of the resized image. 
   * @return A new instance of Image<T> with the provided width and height with resized data.
   */
  static Image<T> Resize(const Sampler<T> * const sampler, size_t new_width, size_t new_height) {
    Image<T> resizedImage(new_width, new_height, sampler->GetImage().GetChannels());
    Resize(sampler, &resizedImage);
    return resizedImage;
  }

  /*!
   * @brief Resizes the image into the provided one.
   * @param sampler The sampler of original image.
   * @param image_to The target image to resize image to.
   */
  static void Resize(const Sampler<T> * const sampler, Image<T> * image_to) {
    double scale_x = static_cast<double>(sampler->GetImage().GetWidth()) /  image_to->GetWidth();
    double scale_y = static_cast<double>(sampler->GetImage().GetHeight()) /  image_to->GetHeight();
    for(size_t y = 0; y < image_to->GetHeight(); ++y) {
      double y_o = scale_y * y;
      for(size_t x = 0; x < image_to->GetWidth(); ++x) {
      double x_o = scale_x * x;
        for(size_t c = 0; c < image_to->GetChannels(); ++c) {
          image_to->Set(sampler->Interpolate(y_o, x_o, c), y,x,c);
        }
      }
    }
  }
};

} // namespace visq

#endif // VISQ_RESIZER_H
