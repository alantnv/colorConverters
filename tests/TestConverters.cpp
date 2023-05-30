#include "../lib/include/Converters.h"
#include "gtest/gtest.h"
#include <iostream>
#include <tuple>

using TestCase = std::tuple<RGB, YUV, HSV>;
// Тестируем Clamp
class ClampTest : public ::testing::Test {
protected:
  void SetUp() {}
  void TearDown() {}

public:
  YUV yuv{300, 300, 300};
  HSV hsv{400, 255, 255};
};

TEST_F(ClampTest, YUV_RGB) {
  YUV cmp{255, (1 - Kb) * 255, (1 - Kr) * 255};
  EXPECT_EQ(Convert::YuvToRgb(yuv), Convert::YuvToRgb(cmp));
}

TEST_F(ClampTest, YUV_HSV) {
  YUV cmp{255, (1 - Kb) * 255, (1 - Kr) * 255};
  EXPECT_EQ(Convert::YuvToHsv(yuv), Convert::YuvToHsv(cmp));
}

TEST_F(ClampTest, HSV_RGB) {
  HSV cmp{360, 255, 255};
  EXPECT_EQ(Convert::HsvToRgb(hsv), Convert::HsvToRgb(cmp));
}

TEST_F(ClampTest, HSV_YUV) {
  HSV cmp{360, 255, 255};
  EXPECT_EQ(Convert::HsvToYuv(hsv), Convert::HsvToYuv(cmp));
}

// Тестируем сами конвертеры
class ConvertersTest : public ::testing::TestWithParam<TestCase> {
protected:
  void SetUp() {}
  void TearDown() {}

public:
  RGB rgb;
  YUV yuv;
  HSV hsv;
};

INSTANTIATE_TEST_SUITE_P(
    ColorConverters, ConvertersTest,
    ::testing::Values(
        TestCase{RGB{0, 0, 0}, YUV{0, 0, 0}, HSV{0, 0, 0}},
        TestCase{RGB{255, 255, 255}, YUV{255, 0, 0}, HSV{0, 0, 100}},
        TestCase{RGB{255, 0, 0}, YUV{54, -54, 201}, HSV{0, 100, 100}},
        TestCase{RGB{255, 128, 0}, YUV{146, -146, 109}, HSV{30, 100, 100}},
        TestCase{RGB{255, 255, 0}, YUV{237, -237, 18}, HSV{60, 100, 100}},
        TestCase{RGB{0, 255, 0}, YUV{182, -182, -182}, HSV{120, 100, 100}},
        TestCase{RGB{0, 255, 255}, YUV{201, 54, -201}, HSV{180, 100, 100}},
        TestCase{RGB{0, 0, 255}, YUV{18, 237, -18}, HSV{240, 100, 100}},
        TestCase{RGB{255, 0, 255}, YUV{73, 182, 182}, HSV{300, 100, 100}}));

TEST_P(ConvertersTest, RgbToYuvTest) {
  TestCase testcase = GetParam();
  rgb = std::get<0>(testcase);
  yuv = std::get<1>(testcase);
  rgb.Clamp();
  yuv.Clamp();
  EXPECT_EQ(Convert::RgbToYuv(rgb), yuv);
}

TEST_P(ConvertersTest, RgbToHsvTest) {
  TestCase testcase = GetParam();
  rgb = std::get<0>(testcase);
  hsv = std::get<2>(testcase);
  rgb.Clamp();
  hsv.Clamp();
  EXPECT_EQ(Convert::RgbToHsv(rgb), hsv);
}

TEST_P(ConvertersTest, YuvToRgbTest) {
  TestCase testcase = GetParam();
  rgb = std::get<0>(testcase);
  yuv = std::get<1>(testcase);
  rgb.Clamp();
  yuv.Clamp();
  EXPECT_EQ(Convert::YuvToRgb(yuv), rgb);
}

TEST_P(ConvertersTest, YuvToHsvTest) {
  TestCase testcase = GetParam();
  hsv = std::get<2>(testcase);
  yuv = std::get<1>(testcase);
  hsv.Clamp();
  yuv.Clamp();
  EXPECT_EQ(Convert::YuvToHsv(yuv), hsv);
}

TEST_P(ConvertersTest, HsvToRgbTest) {
  TestCase testcase = GetParam();
  hsv = std::get<2>(testcase);
  rgb = std::get<0>(testcase);
  hsv.Clamp();
  rgb.Clamp();
  EXPECT_EQ(Convert::HsvToRgb(hsv), rgb);
}

TEST_P(ConvertersTest, HsvToYuvTest) {
  TestCase testcase = GetParam();
  hsv = std::get<2>(testcase);
  yuv = std::get<1>(testcase);
  hsv.Clamp();
  yuv.Clamp();
  EXPECT_EQ(Convert::HsvToYuv(hsv), yuv);
}
