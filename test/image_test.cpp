#include "image.h"
#include "image_test.h"
#include <gtest/gtest.h>

namespace visq {

// Test the default constructor
TEST(ImageTest, DefaultConstructor) {
  Image img(100, 100, 3);
  EXPECT_EQ(img.GetWidth(), 100);
  EXPECT_EQ(img.GetHeight(), 100);
  EXPECT_EQ(img.GetChannels(), 3);
  EXPECT_TRUE(img.IsContinuous());
}

// Test the secondary constructor
TEST(ImageTest, SecondaryConstructor) {
  Image img1(100, 100, 3);
  Image img2(img1, 50, 50, 0);
  EXPECT_EQ(img2.GetWidth(), 50);
  EXPECT_EQ(img2.GetHeight(), 50);
  EXPECT_EQ(img2.GetStride(), 300);
  EXPECT_EQ(img2.GetOffset(), 0);
}

// Test the At method
TEST(ImageTest, AtMethod) {
  Image img(100, 100, 3);
  uint8_t &pixel_val = img.At(10, 10, 1);
  pixel_val = 255;
  EXPECT_EQ(img.At(10, 10, 1), 255);
}

// Test the CopyTo method
TEST(ImageTest, CopyToMethod) {
  Image img1(100, 100, 3);
  Image img2(100, 100, 3);
  // Set a pixel value in img1
  img1.At(10, 10, 1) = 123;

  img1.CopyTo(img2);
  EXPECT_EQ(img2.At(10, 10, 1), 123);
}

// Test the IsContinuous method
TEST(ImageTest, IsContinuousMethod) {
  Image img1(100, 100, 3);
  EXPECT_TRUE(img1.IsContinuous());

  Image img2(img1, 50, 50, 25);
  EXPECT_FALSE(img2.IsContinuous());
}

// Test the CopyTo method
TEST(ImageTest, CopyToWhenContinuousMethod) {
  Image img1(100, 100, 3);
  uint8_t v = 0;
  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      for (int k = 0; k < 3; ++k) {
        img1.At(i, j, k) = v++;
      }
    }
  }

  Image img2(100, 100, 3);
  ASSERT_TRUE(img1.CopyTo(img2));
  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      for (int k = 0; k < 3; ++k) {
        ASSERT_EQ(img1.At(i, j, k), img2.At(i, j, k));
      }
    }
  }
}

TEST(ImageTest, CopyToWhenNotContinuous) {
  Image img1(1000, 1000, 3);
  Image img1Test(img1, 100, 100, 3 * 25 * 1000);
  uint8_t v = 0;
  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      for (int k = 0; k < 3; ++k) {
        img1Test.At(i, j, k) = v++;
      }
    }
  }

  Image img2(800, 800, 3);
  Image img2Tes(img2, 100, 100, 3 * 800 * 12);
  ASSERT_TRUE(img1Test.CopyTo(img2Tes));
  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      for (int k = 0; k < 3; ++k) {
        ASSERT_EQ(img1Test.At(i, j, k), img2Tes.At(i, j, k));
      }
    }
  }
}

// Additional tests can be written for edge cases, error conditions, etc.

}  // namespace visq

