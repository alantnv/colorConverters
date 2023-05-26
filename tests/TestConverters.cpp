#include "../lib/include/Converters.h"
#include "gtest/gtest.h"
#include <iostream>
#include <vector>
class ConvertersTest : public ::testing::Test {
protected:
  void SetUp() {}
  void TearDown() {}

public:
  std::vector<RGB> rgb{RGB{0, 0, 0},     RGB{255, 255, 255}, RGB{255, 0, 0},
                       RGB{255, 128, 0}, RGB{255, 255, 0},   RGB{0, 255, 0},
                       RGB{0, 255, 255}, RGB{0, 0, 255},     RGB{255, 0, 255}};
  std::vector<YUV> yuv{
      YUV{0, 0, 0},        YUV{255, 0, 0},     YUV{54, -54, 201},
      YUV{146, -146, 109}, YUV{237, -237, 18}, YUV{182, -182, -182},
      YUV{201, 54, -201},  YUV{18, 237, -18},  YUV{73, 182, 182}};
  std::vector<HSV> hsv{
      HSV{0, 0, 0},       HSV{0, 0, 100},     HSV{0, 100, 100},
      HSV{30, 100, 100},  HSV{60, 100, 100},  HSV{120, 100, 100},
      HSV{180, 100, 100}, HSV{240, 100, 100}, HSV{300, 100, 100}};
};

TEST_F(ConvertersTest, RgbToYuvTest) {
  for (size_t i = 0; i < rgb.size(); ++i)
    EXPECT_EQ(Convert::RgbToYuv(rgb[i]), yuv[i]);
}

TEST_F(ConvertersTest, RgbToHsvTest) {
  for (size_t i = 0; i < rgb.size(); ++i)
    EXPECT_EQ(Convert::RgbToHsv(rgb[i]), hsv[i]);
}

TEST_F(ConvertersTest, YuvToRgbTest) {
  for (size_t i = 0; i < yuv.size(); ++i)
    EXPECT_EQ(Convert::YuvToRgb(yuv[i]), rgb[i]);
}

TEST_F(ConvertersTest, YuvToHsvTest) {
  for (size_t i = 0; i < yuv.size(); ++i)
    EXPECT_EQ(Convert::YuvToHsv(yuv[i]), hsv[i]);
}

TEST_F(ConvertersTest, HsvToRgbTest) {
  for (size_t i = 0; i < hsv.size(); ++i)
    EXPECT_EQ(Convert::HsvToRgb(hsv[i]), rgb[i]);
}

TEST_F(ConvertersTest, HsvToYuvTest) {
  for (size_t i = 0; i < hsv.size(); ++i)
    EXPECT_EQ(Convert::HsvToYuv(hsv[i]), yuv[i]);
}
