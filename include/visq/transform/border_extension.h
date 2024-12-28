#ifndef VISQPROJECT_INCLUDE_TRANSFORM_BORDER_EXTENSION_H_
#define VISQPROJECT_INCLUDE_TRANSFORM_BORDER_EXTENSION_H_

namespace visq {

/*!
 * @brief Interface for handling borders for filters
 */
template<typename T>
class BorderExtension {
protected:
  Image<T> image_;

public:
  explicit BorderExtension(const Image<T> & image): image_(image) {}

  virtual ~BorderExtension() = default;

  [[nodiscard]] const Image<T> & GetImage() const { return image_; }

  [[nodiscard]] size_t GetWidth() const { return image_.GetWidth(); }

  [[nodiscard]] size_t GetHeight() const { return image_.GetHeight(); }

  [[nodiscard]] size_t GetChannels() const { return image_.GetChannels(); }
  /*!
   * @brief for 0 <= x < image.width and 0 <= y < image.height  returns the value of the pixel. Otherwise returns the interpolated value.
   */  
  [[nodiscard]] virtual T At(long y, long x, size_t c) const = 0;
};

} // visq

#endif //VISQPROJECT_INCLUDE_TRANSFORM_BORDER_EXTENSION_H_
