#ifndef VISQPROJECT_INCLUDE_TRANSFORM_BORDER_EXTENSIONS_CONSTANT_BORDER_H_
#define VISQPROJECT_INCLUDE_TRANSFORM_BORDER_EXTENSIONS_CONSTANT_BORDER_H_

#include <visq/image.h>
#include <visq/transform/border_extension.h>

namespace visq::border_extensions {

template<typename T>
class ConstantBorder: public BorderExtension<T> {
public:

  ConstantBorder(const Image<T> & image): BorderExtension<T>(image) {}

  [[nodiscard]] const T At(long y, long x, size_t c) const override {
    y = std::max(0l, y);
    y = std::min(static_cast<long>(this->image_.GetHeight()) - 1, y);
    x = std::max(0l, x);
    x = std::min(static_cast<long>(this->image_.GetWidth()) - 1, x);

    return this->image_.At(static_cast<size_t>(y), static_cast<size_t>(x), c);    
  }
};


} // visq

#endif // VISQPROJECT_INCLUDE_TRANSFORM_BORDER_EXTENSIONS_CONSTANT_BORDER_H_
