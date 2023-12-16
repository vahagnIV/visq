#include "io.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "stb_image.h"

namespace visq {

std::tuple<ErrorCode, std::optional<Image>> LoadImage(const std::string& path) {
    int width, height, channels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (data) {
        Image img(static_cast<size_t>(width), static_cast<size_t>(height), static_cast<size_t>(channels));
        std::memcpy(img.Data(), data, width * height * channels * sizeof(uint8_t));
        stbi_image_free(data);
        return {ErrorCode::Ok, img};
    } else {
        return {ErrorCode::FileNotFound, std::nullopt};
    }
}

ErrorCode SaveImage(const Image& image, const std::string& path, ImageFormat format) {
    if (!image.IsContinuous()) {
        Image continuousImage(image.GetWidth(), image.GetHeight(), image.GetChannels());
        if (!image.CopyTo(continuousImage)) {
            return ErrorCode::InvalidFormat;
        }
        return SaveImage(continuousImage, path, format);
    }

    int stride_in_bytes = image.GetWidth() * image.GetChannels() * sizeof(uint8_t);

    switch (format) {
        case ImageFormat::Png:
            if (!stbi_write_png(path.c_str(), image.GetWidth(), image.GetHeight(), image.GetChannels(), image.Data(), stride_in_bytes)) {
                return ErrorCode::FileNotFound;
            }
            break;
        case ImageFormat::Jpeg:
            if (!stbi_write_jpg(path.c_str(), image.GetWidth(), image.GetHeight(), image.GetChannels(), image.Data(), 100)) {
                return ErrorCode::FileNotFound;
            }
            break;
        case ImageFormat::Bmp:
            if (!stbi_write_bmp(path.c_str(), image.GetWidth(), image.GetHeight(), image.GetChannels(), image.Data())) {
                return ErrorCode::FileNotFound;
            }
            break;
        default:
            return ErrorCode::InvalidFormat;
    }

    return ErrorCode::Ok;
}

}  // namespace visq
