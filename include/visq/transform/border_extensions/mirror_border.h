#ifndef VISQPROJECT_INCLUDE_TRANSFORM_BORDER_EXTENSIONS_MIRROR_BORDER_H_
#define VISQPROJECT_INCLUDE_TRANSFORM_BORDER_EXTENSIONS_MIRROR_BORDER_H_

#include <visq/image.h>
#include <visq/transform/border_extension.h>

namespace visq::border_extensions {

template<typename T>
class MirrorBorder: public BorderExtension<T> {
public:

  MirrorBorder(const Image<T> & image): BorderExtension<T>(image) {}

  [[nodiscard]] const T At(long y, long x, size_t c) const override {

    if (y < 0) 
      y = (static_cast<size_t>(-y) -1l) % this->image_.GetHeight();
    else if(y >= this->image_.GetHeight()) 
      y = static_cast<long>(this->image_.GetHeight()) - 1l -  ((y - static_cast<long>(this->image_.GetHeight()))  % static_cast<long>(this->image_.GetHeight()));

    if (x < 0) 
      x = (static_cast<size_t>(-x) - 1l) % this->image_.GetWidth();
    else if(x >= this->image_.GetWidth()) 
      x = static_cast<long>(this->image_.GetWidth()) - 1l -  ((x- static_cast<long>(this->image_.GetWidth()))  % static_cast<long>(this->image_.GetWidth()));

    return this->image_.At(static_cast<size_t>(y), static_cast<size_t>(x), c);
  }
};


} // visq

#endif // VISQPROJECT_INCLUDE_TRANSFORM_BORDER_EXTENSIONS_MIRROR_BORDER_H_
