#ifndef VISQPROJECT_INCLUDE_VISQ_UTILS_COLOR_H_
#define VISQPROJECT_INCLUDE_VISQ_UTILS_COLOR_H_

#include <cstdint>

namespace visq::utils {

struct Color {
  uint8_t red;
  uint8_t green;
  uint8_t blue;

  Color() {}
  Color(uint8_t r, uint8_t g, uint8_t b): red(r), green(g), blue(b) {}
};

} // utils
// visq

#endif //VISQPROJECT_INCLUDE_VISQ_UTILS_COLOR_H_
