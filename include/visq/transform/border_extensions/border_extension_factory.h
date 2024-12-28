#ifndef VISQPROJECT_INCLUDE_VISQ_TRANSFORM_BORDER_EXTENSIONS_BORDER_EXTENSION_FACTORY_H_
#define VISQPROJECT_INCLUDE_VISQ_TRANSFORM_BORDER_EXTENSIONS_BORDER_EXTENSION_FACTORY_H_

#include <visq/transform/border_extensions/constant_border.h>
#include <visq/transform/border_extensions/mirror_border.h>
#include <visq/transform/border_extensions/border_type.h>

namespace visq {

class BorderExtensionFactory {
 public:
  template<typename T>
  static std::shared_ptr<BorderExtension<T>> Create(const Image<T> & image, BorderType type) {
    switch (type) {
      case BorderType::Mirror:
        return std::make_shared<border_extensions::MirrorBorder<T>>(image);
      case BorderType::Constant:
        return std::make_shared<border_extensions::ConstantBorder<T>>(image);
      default:
        return nullptr;
    }
  }
};

} // visq

#endif //VISQPROJECT_INCLUDE_VISQ_TRANSFORM_BORDER_EXTENSIONS_BORDER_EXTENSION_FACTORY_H_
