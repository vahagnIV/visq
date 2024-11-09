#ifndef VISQPROJECT_INCLUDE_TRANSFORM_SAMPLER_H_
#define VISQPROJECT_INCLUDE_TRANSFORM_SAMPLER_H_

#include <memory>
#include <visq/image.h>

namespace visq {

/*!
 * Interface that represents an image sampler.
 */
template<typename T>
class Sampler {
public:
  Sampler(const Image<T> & image): image_(image) {};
  virtual ~Sampler() = default;
  
  /*!
   * Returns the interpolated value of provided image volume at real point (x,y, channel)
   */
  [[nodiscard]] virtual T Interpolate(double y, double x, size_t channel) const = 0;

  /*!
   * A getter for the procided image
   */
  [[nodiscard]] const Image<T> & GetImage() const { return image_; }
protected:
  const Image<T> image_; 
};

}

#endif // VISQPROJECT_INCLUDE_TRANSFORM_SAMPLER_H_


