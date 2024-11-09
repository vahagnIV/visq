#ifndef VISQPROJECT_INCLUDE_TRANSFORM_FILTER_H_
#define VISQPROJECT_INCLUDE_TRANSFORM_FILTER_H_

#include <cassert>
#include <visq/image.h>
#include <visq/transform/border_extension.h>
namespace visq {

/*!
 * 
 */
class Filter {
public:
  //typedef decltype(std::declval<T>() * std::declval<K>()) return_t;
  template<typename T, typename K= T>
  static auto Apply(const Image<K> * const kernel, const BorderExtension<T> * const image)->Image<decltype(std::declval<T>() * std::declval<K>())> {

    assert((kernel->GetWidth() & 1) == 1);
    assert((kernel->GetHeight() & 1) == 1);
    assert(kernel->GetChannels() == 1);

    typedef decltype(std::declval<T>() * std::declval<K>()) result_t; 
    Image<result_t> result(image->GetWidth(), image->GetHeight(), image->GetChannels(), result_t(0));

    long kx2 = kernel->GetWidth() / 2;
    long ky2 = kernel->GetHeight() / 2;
    for(long y = 0; y < image->GetHeight(); ++y){
      for(long x = 0; x < image->GetWidth(); ++x) {
        for(size_t c = 0; c < image->GetChannels(); ++c){
      
          result_t value(0);
          for(long ky = -ky2; ky <= ky2; ++ky) {
            for(long kx = -kx2; kx < kx2; ++kx) {
              result.Set(result.At(y,x,c) +  kernel->At(ky + ky2, kx + ky2, 0) * image->At(y+ky, x+kx,c), y,x,c);  
            }
          }
        }    
      }
    }

     return result;
  }
  
  
      
};

}

#endif // VISQPROJECT_INCLUDE_TRANSFORM_FILTER_H_
