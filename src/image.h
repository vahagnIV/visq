#ifndef VISQ_IMAGE_H
#define VISQ_IMAGE_H

#include <memory>
#include <cstring>  // For std::memcpy

namespace visq {

/**
 * @brief Class representing an image with given width, height, and channels.
 */
class Image {
 public:
  /**
   * @brief Constructs an Image object with specified width, height, and channels.
   * @param width Width of the image.
   * @param height Height of the image.
   * @param channels Number of color channels in the image.
   */
  Image(size_t width, size_t height, size_t channels);

  /**
   * @brief Constructs an Image object as a sub-image of another image.
   * @param other Reference to the source Image object.
   * @param new_width Width of the sub-image.
   * @param new_height Height of the sub-image.
   * @param stride Stride (row length in memory) of the sub-image.
   * @param offset Offset from the start of the source image data to the sub-image.
   */
  Image(const Image& other, size_t new_width, size_t new_height, size_t offset);

  /**
   * @brief Accesses or modifies a pixel's channel value.
   * @param y Y-coordinate of the pixel.
   * @param x X-coordinate of the pixel.
   * @param c Channel index.
   * @return Reference to the pixel's channel value.
   */
  uint8_t& At(size_t y, size_t x, size_t c);

  /**
   * @brief Accesses a pixel's channel value in a read-only fashion.
   * @param y Y-coordinate of the pixel.
   * @param x X-coordinate of the pixel.
   * @param c Channel index.
   * @return Constant reference to the pixel's channel value.
   */
  [[nodiscard]] const uint8_t& At(size_t y, size_t x, size_t c) const;

  /**
   * @brief Gets a raw pointer to the image data.
   * @note Direct access to the data can be unsafe. Use with caution.
   * @return Raw pointer to the image data.
   */
  uint8_t* Data();

  /**
   * @brief Gets a read-only raw pointer to the image data.
   * @return Constant raw pointer to the image data.
   */
  [[nodiscard]] const uint8_t* Data() const;

  /**
   * @brief Copies the content to another Image object.
   * @param image Reference to the destination Image object.
   * @return True if the copy is successful, false otherwise.
   */
  bool CopyTo(Image &image) const;

  /**
   * @brief Checks if the underlying data is continuous.
   * @return True if the data is continuous, false otherwise.
   */
  [[nodiscard]] bool IsContinuous() const;

  // Getters
  [[nodiscard]] size_t GetWidth() const;
  [[nodiscard]] size_t GetHeight() const;
  [[nodiscard]] size_t GetChannels() const;
  [[nodiscard]] size_t GetStride() const;
  [[nodiscard]] size_t GetOffset() const;

 private:
  size_t width_;
  size_t height_;
  size_t channels_;
  size_t stride_;
  size_t offset_;
  std::shared_ptr<uint8_t[]> data_;
};

}  // namespace visq

#endif  // VISQ_IMAGE_H
