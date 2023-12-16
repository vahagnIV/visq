#include "visq/image.h"

namespace visq {

Image::Image(size_t width, size_t height, size_t channels)
    : width_(width), height_(height), channels_(channels),
      stride_(width * channels), offset_(0),
      data_(new uint8_t[width * height * channels]) {}

Image::Image(const Image& other, size_t new_width, size_t new_height, size_t offset)
    : width_(new_width), height_(new_height), channels_(other.channels_),
      stride_(other.stride_), offset_(offset),
      data_(other.data_) {}

uint8_t& Image::At(size_t y, size_t x, size_t c) {
  return data_.get()[(y * stride_) + (x * channels_) + c + offset_];
}

const uint8_t& Image::At(size_t y, size_t x, size_t c) const {
  return data_.get()[(y * stride_) + (x * channels_) + c + offset_];
}

uint8_t* Image::Data() {
  return data_.get();
}

const uint8_t* Image::Data() const {
  return data_.get();
}

bool Image::CopyTo(Image &other) const {
  if (this->width_ != other.width_ || this->height_ != other.height_ || this->channels_ != other.channels_) {
    return false;
  }

  if (this->stride_ == this->width_ * this->channels_ && other.stride_ == other.width_ * other.channels_ &&
      this->offset_ == 0 && other.offset_ == 0) {
    std::memcpy(other.data_.get(), this->data_.get(), this->height_ * this->stride_ * sizeof(uint8_t));
  } else {
    for (int y = 0; y < this->height_; ++y) {
      std::memcpy(other.data_.get() + other.offset_ + y * other.stride_,
                  this->data_.get() + this->offset_ + y * this->stride_,
                  this->width_ * this->channels_ * sizeof(uint8_t));
    }
  }

  return true;
}

bool Image::IsContinuous() const {
  return stride_ == width_ * channels_;
}

size_t Image::GetWidth() const { return width_; }
size_t Image::GetHeight() const { return height_; }
size_t Image::GetChannels() const { return channels_; }
size_t Image::GetStride() const { return stride_; }
size_t Image::GetOffset() const { return offset_; }

}  // namespace visq
