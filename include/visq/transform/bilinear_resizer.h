#ifndef VISQPROJECT_SRC_TRANSFORM_BILINEAR_RESIZER_H_
#define VISQPROJECT_SRC_TRANSFORM_BILINEAR_RESIZER_H_

#include "resizer.h"

namespace visq {

class BilinearResizer : public Resizer {
 public:
  void Resize(const Image &image_from, Image &image_to) const override;
};

} // visq

#endif //VISQPROJECT_SRC_TRANSFORM_BILINEAR_RESIZER_H_
