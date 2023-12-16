#include <cmath>
#include "visq/transform/bilinear_resizer.h"

namespace visq {

void BilinearResizer::Resize(const Image &image_from, Image &image_to) const {
  double x_ratio = static_cast<double>(image_from.GetWidth()) / image_to.GetWidth();
  double y_ratio = static_cast<double>(image_from.GetHeight()) / image_to.GetHeight();
  double px, py;

  for (size_t y = 0; y < image_to.GetHeight(); ++y) {
    for (size_t x = 0; x < image_to.GetWidth(); ++x) {

      px = std::floor(x * x_ratio);
      py = std::floor(y * y_ratio);

      for (size_t c = 0; c < image_from.GetChannels(); ++c) {
        double f1 = (x_ratio - (x * x_ratio - px)) * image_from.At(py, px, c)
            + ((x * x_ratio - px) * image_from.At(py, px + 1, c));

        double f2 = (x_ratio - (x * x_ratio - px)) * image_from.At(py + 1, px, c)
            + ((x * x_ratio - px) * image_from.At(py + 1, px + 1, c));

        image_to.At(y, x, c) = static_cast<uint8_t>(std::min(255.,
                                                             std::max(0.,
                                                                      (y_ratio - (y * y_ratio - py)) * f1
                                                                          + ((y * y_ratio - py) * f2))/4.));
      }
    }
  }
}

} // visq