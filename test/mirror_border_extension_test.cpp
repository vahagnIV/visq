#include "constant_border_extension_test.h"
#include <visq/transform/border_extensions/mirror_border.h>

namespace visq::test {

TEST(MirrorBorderExtensionTest, CorrectlyReturnsValues){
  Image<uint8_t> image(5, 5, 1);
  for(uint8_t i = 0; i < image.GetHeight(); ++i) {
    for(uint8_t j = 0; j < image.GetWidth(); ++j) {
      image.Set(i * image.GetWidth() + j, i, j, 0 );
    }
  } 

  border_extensions::MirrorBorder system_under_test(image);
  
  // Top center
  ASSERT_EQ(system_under_test.At(-3, 2, 0), 12); 
 
  // Top left
  ASSERT_EQ(system_under_test.At(-3, -2, 0), 11); 
  
  // Center left
  ASSERT_EQ(system_under_test.At(3, -2, 0), 16); 

  // Bottom  center
  ASSERT_EQ(system_under_test.At(7, 2, 0), 12); 
 
  // Center right
  ASSERT_EQ(system_under_test.At(1, 6, 0), 8); 
  
  // Top right
  ASSERT_EQ(system_under_test.At(-1, 22, 0), 2);

  // Bottom left 
  ASSERT_EQ(system_under_test.At(19, -2, 0), 1);

  // Bottom right
  ASSERT_EQ(system_under_test.At(19, 22, 0), 2);

  // Normal
  ASSERT_EQ(system_under_test.At(2, 3, 0), 13); 
}

} // visq::test
