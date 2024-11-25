#ifndef VISQ_IMAGE_H
#define VISQ_IMAGE_H

#include <memory>
#include <cstring>  // For std::memcpy
#include <cassert>

namespace visq {

/**
 * @brief Class representing an image with given width, height, and channels.
 */

template<typename T>
class Image {
 public:
  /**
   * @brief Constructs an Image object with specified width, height, and channels.
   * @param width Width of the image.
   * @param height Height of the image.
   * @param channels Number of color channels in the image.
   */
  Image(size_t width, size_t height, size_t channels)
      : width_(width), height_(height), channels_(channels),
        stride_(width * channels), offset_(0),
        data_(new T[width * height * channels]) {}

  /**
  * @brief Constructs an Image object with specified width, height, and channels and sets all values to @value.
  * @param width Width of the image.
  * @param height Height of the image.
  * @param channels Number of color channels in the image.
  * @param value Value for initialization.
  */
  Image(size_t width, size_t height, size_t channels, T value) : Image(width, height, channels) {
    for (size_t i = 0; i < height * width * channels; ++i) data_[i] = value;

  }

  /**
   * @brief Constructs an Image object as a sub-image of another image.
   * @param other Reference to the source Image object.
   * @param new_width Width of the sub-image.
   * @param new_height Height of the sub-image.
   * @param stride Stride (row length in memory) of the sub-image.
   * @param offset Offset from the start of the source image data to the sub-image.
   */
  Image(const Image<T> &other, size_t new_width, size_t new_height, size_t offset)
      : width_(new_width), height_(new_height), channels_(other.channels_),
        stride_(other.stride_), offset_(offset),
        data_(other.data_) {}

  /**
   * @brief Accesses or modifies a pixel's channel value.
   * @param y Y-coordinate of the pixel.
   * @param x X-coordinate of the pixel.
   * @param c Channel index.
   * @return Reference to the pixel's channel value.
   */
  void Set(T value, size_t y, size_t x, size_t c) {
    assert((y * stride_) + (x * channels_) + c  < stride_ * height_);
    data_.get()[(y * stride_) + (x * channels_) + c + offset_] = value;
  }

  /**
   * @brief Accesses a pixel's channel value in a read-only fashion.
   * @param y Y-coordinate of the pixel.
   * @param x X-coordinate of the pixel.
   * @param c Channel index.
   * @return Constant reference to the pixel's channel value.
   */
  [[nodiscard]] const T &At(size_t y, size_t x, size_t c) const {
    assert((y * stride_) + (x * channels_) + c  < stride_ * height_);
    return data_.get()[(y * stride_) + (x * channels_) + c + offset_];
  }

  /**
   * @brief Gets a raw pointer to the image data.
   * @note Direct access to the data can be unsafe. Use with caution.
   * @return Raw pointer to the image data.
   */
  T *Data() {
    return data_.get();
  }

  /**
   * @brief Gets a read-only raw pointer to the image data.
   * @return Constant raw pointer to the image data.
   */
  [[nodiscard]] const T *Data() const {
    return data_.get();
  }

  /**
   * @brief Copies the content to another Image object.
   * @param image Reference to the destination Image object.
   * @return True if the copy is successful, false otherwise.
   */
  template<typename R>
  bool CopyTo(Image<R> &other) const {
    if (this->width_ != other.GetWidth() || this->height_ != other.GetHeight()
        || this->channels_ != other.GetChannels()) {
      return false;
    }

    for (size_t y = 0; y < this->height_; ++y) {
      for (size_t x = 0; x < this->width_; ++x) {
        for (size_t c = 0; c < channels_; ++c) {
          other.Set(At(y, x, c), y, x, c);
        }
      }
    }
    return true;
  }

  /**
   * @brief Checks if the underlying data is continuous.
   * @return True if the data is continuous, false otherwise.
   */
  [[nodiscard]] bool IsContinuous() const {
    return stride_ == width_ * channels_;
  }

  /*!
   * Conversion operator
   * @tparam K template parameter of the target image
   * @return The converted image.
   */
  template<class K>
  operator Image<K>() const {
    Image<K> result(GetWidth(), GetHeight(), GetChannels());
    for (int i = 0; i < GetHeight(); ++i) {
      for (int j = 0; j < GetWidth(); ++j) {
        for (int k = 0; k < GetChannels(); ++k) {
          result.Set(At(i, j, k), i, j, k);
        }
      }
    }
    return result;
  }

  operator T() const {
    return At(0, 0, 0);
  }

  Image<T> Row(size_t row) {
    return Image<T>(*this, width_, 1, offset_ + row * stride_);
  }

  Image<T> Column(size_t column) {
    return Image<T>(*this, 1, height_, offset_ + column * channels_);
  }

  // Getters
  [[nodiscard]] size_t GetWidth() const { return width_; }
  [[nodiscard]] size_t GetHeight() const { return height_; }
  [[nodiscard]] size_t GetChannels() const { return channels_; }
  [[nodiscard]] size_t GetStride() const { return stride_; }
  [[nodiscard]] size_t GetOffset() const { return offset_; }

  ~Image() {

  }

 private:
  size_t width_;
  size_t height_;
  size_t channels_;
  size_t stride_;
  size_t offset_;
  std::shared_ptr<T[]> data_;
};

using UImage = Image<uint8_t>;
}  // namespace visq



#endif  // VISQ_IMAGE_H
