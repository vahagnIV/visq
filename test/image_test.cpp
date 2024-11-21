#include "include/visq/image.h"
#include "image_test.h"
#include <gtest/gtest.h>

namespace visq {

// Test the default constructor
TEST(ImageTest, DefaultConstructor) {
  Image<uint8_t> img(100, 100, 3);
  EXPECT_EQ(img.GetWidth(), 100);
  EXPECT_EQ(img.GetHeight(), 100);
  EXPECT_EQ(img.GetChannels(), 3);
  EXPECT_TRUE(img.IsContinuous());
}

// Test the secondary constructor
TEST(ImageTest, SecondaryConstructor) {
  Image<uint8_t> img1(100, 100, 3);
  Image<uint8_t> img2(img1, 50, 50, 0);
  EXPECT_EQ(img2.GetWidth(), 50);
  EXPECT_EQ(img2.GetHeight(), 50);
  EXPECT_EQ(img2.GetStride(), 300);
  EXPECT_EQ(img2.GetOffset(), 0);
}

// Test the Set method
TEST(ImageTest, AtMethod) {
  Image<uint8_t> img(100, 100, 3);
  img.Set(255, 10, 10, 1);
  EXPECT_EQ(img.At(10, 10, 1), 255);
}

// Test the CopyTo method
TEST(ImageTest, CopyToMethod) {
  Image<uint8_t> img1(100, 100, 3);
  Image<uint8_t> img2(100, 100, 3);
  // Set a pixel value in img1
  img1.Set(123, 10, 10, 1);

  img1.CopyTo(img2);
  EXPECT_EQ(img2.At(10, 10, 1), 123);
}

// Test the IsContinuous method
TEST(ImageTest, IsContinuousMethod) {
  Image<uint8_t> img1(100, 100, 3);
  EXPECT_TRUE(img1.IsContinuous());

  Image<uint8_t> img2(img1, 50, 50, 25);
  EXPECT_FALSE(img2.IsContinuous());
}

// Test the CopyTo method
TEST(ImageTest, CopyToWhenContinuousMethod) {
  Image<uint8_t> img1(100, 100, 3);
  uint8_t v = 0;
  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      for (int k = 0; k < 3; ++k) {
        img1.Set(v++, i, j, k);
      }
    }
  }

  Image<uint8_t> img2(100, 100, 3);
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
  Image<uint8_t> img1(1000, 1000, 3);
  Image<uint8_t> img1Test(img1, 100, 100, 3 * 25 * 1000);
  uint8_t v = 0;
  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      for (int k = 0; k < 3; ++k) {
        img1Test.Set(v++, i, j, k);
      }
    }
  }

  Image<uint8_t> img2(800, 800, 3);
  Image<uint8_t> img2Tes(img2, 100, 100, 3 * 800 * 12);
  ASSERT_TRUE(img1Test.CopyTo(img2Tes));
  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      for (int k = 0; k < 3; ++k) {
        ASSERT_EQ(img1Test.At(i, j, k), img2Tes.At(i, j, k));
      }
    }
  }
}

TEST(ImageTest, ConversionOperator) {

  Image<double> img1Test(100, 100, 3);
  uint8_t v = 0;
  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      for (int k = 0; k < 3; ++k) {
        img1Test.Set(v++, i, j, k);
      }
    }
  }

  Image<uint8_t> img1 = img1Test;
  v = 0;
  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      for (int k = 0; k < 3; ++k) {
        ASSERT_EQ(img1.At(i, j, k), v++);
      }
    }
  }
}

TEST(ImageTest, Row){
  const size_t width = 100;
  const size_t height = 100;
  const size_t channels = 2;

  Image<uint8_t> img(width, height, channels);
  uint8_t v = 0;
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      for (int k = 0; k < channels; ++k) {
        img.Set(v++, i, j, k);
      }
    }
  }

  Image<uint8_t> img1(img, width - 2, height -2, width * channels * 2 + channels *2);


  auto r = img1.Row(1);
  ASSERT_EQ(r.GetWidth(), img1.GetWidth());
  ASSERT_EQ(r.GetHeight(), 1);
  for(size_t x =0; x < img1.GetWidth(); ++x){
    for(size_t c = 0; c < channels; ++c){
      ASSERT_EQ(img1.At( 1, x, c), r.At(0, x, c));
    }
  }
}


TEST(ImageTest, Column){
  const size_t width = 100;
  const size_t height = 100;
  const size_t channels = 2;

  Image<uint8_t> img(width, height, channels);
  uint8_t v = 0;
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      for (int k = 0; k < channels; ++k) {
        img.Set(v++, i, j, k);
      }
    }
  }

  Image<uint8_t> img1(img, width - 2, height -2, width * channels * 2 + channels *2);


  auto r = img1.Column(1);
  ASSERT_EQ(r.GetHeight(), img1.GetHeight());
  ASSERT_EQ(r.GetWidth(), 1);
  for(size_t y =0; y < img1.GetHeight(); ++y){
    for(size_t c = 0; c < channels; ++c){
      ASSERT_EQ(img1.At( y, 1, c), r.At(y, 0, c));
    }
  }
}

// Additional tests can be written for edge cases, error conditions, etc.

}  // namespace visq

