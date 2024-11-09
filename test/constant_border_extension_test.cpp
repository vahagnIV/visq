#include "constant_border_extension_test.h"
#include <visq/transform/border_extensions/constant_border.h>

namespace visq::test {

TEST(ConstantBorderExtensionTest, CorrectlyReturnsValues){
  Image<uint8_t> image(5, 5, 1);
  for(uint8_t i = 0; i < image.GetHeight(); ++i) {
    for(uint8_t j = 0; j < image.GetWidth(); ++j) {
      image.Set(i * image.GetWidth() + j, i, j, 0 );
    }
  } 

  border_extensions::ConstantBorder system_under_test(image);
  
  // Top center
  ASSERT_EQ(system_under_test.At(-3, 2, 0), 2); 
 
  // Top left
  ASSERT_EQ(system_under_test.At(-3, -2, 0), 0); 
  
  // Center left
  ASSERT_EQ(system_under_test.At(3, -2, 0), 15); 

  // Bottom  center
  ASSERT_EQ(system_under_test.At(19, 2, 0), 22); 
 
  // Center right
  ASSERT_EQ(system_under_test.At(1, 22, 0), 9); 
  
  // Top right
  ASSERT_EQ(system_under_test.At(-1, 22, 0), 4);

  // Bottom left 
  ASSERT_EQ(system_under_test.At(19, -2, 0), 20);

  // Bottom right
  ASSERT_EQ(system_under_test.At(19, 22, 0), 24);

  // Normal
  ASSERT_EQ(system_under_test.At(2, 3, 0), 13); 
}

} // visq::test
