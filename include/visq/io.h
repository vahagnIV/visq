#ifndef VISQ_IO_H
#define VISQ_IO_H

#include "visq/image.h"
#include <string>
#include <tuple>
#include <optional>

namespace visq {

/**
 * @enum ErrorCode
 * @brief Enumerates potential error codes for image I/O operations.
 */
enum class ErrorCode {
    Ok,             ///< Operation successful
    FileNotFound,   ///< File not found or could not be opened
    InvalidFormat,  ///< Invalid file format or image data
    // Other error codes as needed
};

/**
 * @enum ImageFormat
 * @brief Enumerates supported image formats for saving.
 */
enum class ImageFormat {
    Png,  ///< Portable Network Graphics format
    Jpeg, ///< Joint Photographic Experts Group format
    Bmp   ///< Bitmap format
    // Add other formats if needed
};

/**
 * @brief Loads an image from a file.
 * @param path The file path of the image to be loaded.
 * @return A tuple containing an error code and an optional Image object.
 *         The Image object is non-empty if the load operation is successful.
 */
std::tuple<ErrorCode, std::optional<UImage>> LoadImage(const std::string& path);

/**
 * @brief Saves an image to a file in the specified format.
 * @param image The Image object to be saved.
 * @param path The file path where the image will be saved.
 * @param format The format in which the image will be saved.
 * @return ErrorCode indicating the result of the save operation.
 */
ErrorCode SaveImage(const UImage& image, const std::string& path, ImageFormat format);

}  // namespace visq

#endif  // VISQ_IO_H
