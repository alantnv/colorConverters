#include "../lib/include/Converters.h"
#include "gtest/gtest.h"
#include <iostream>
#include <tuple>

static const uint8_t RGB2YUV = 1;
static const uint8_t RGB2HSV = 2;
static const uint8_t YUV2RGB = 4;
static const uint8_t YUV2HSV = 8;
static const uint8_t HSV2RGB = 16;
static const uint8_t HSV2YUV = 32;

static const uint8_t ALL2ALL =
    RGB2YUV | RGB2HSV | YUV2RGB | YUV2HSV | HSV2RGB | HSV2YUV;

using ConvertMask = uint8_t;
using UseClamp = bool;

using TestCase = std::tuple<RGB, YUV, HSV, UseClamp, ConvertMask>;
// Тестируем Clamp
class ClampTest : public ::testing::Test {
protected:
  void SetUp() {}
  void TearDown() {}

public:
  YUV yuv;
  HSV hsv;
};

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
        // clang-format off
        TestCase{ RGB{0, 0, 0},       YUV{0, 0, 0},         HSV{0, 0, 0},       true,  ALL2ALL },
        TestCase{ RGB{255, 255, 255}, YUV{255, 0, 0},       HSV{0, 0, 100},     true,  ALL2ALL },
        TestCase{ RGB{255, 0, 0},     YUV{54, -54, 201},    HSV{0, 100, 100},   true,  ALL2ALL },
        TestCase{ RGB{255, 128, 0},   YUV{146, -146, 109},  HSV{30, 100, 100},  true,  ALL2ALL },
        TestCase{ RGB{255, 255, 0},   YUV{237, -237, 18},   HSV{60, 100, 100},  true,  ALL2ALL },
        TestCase{ RGB{0, 255, 0},     YUV{182, -182, -182}, HSV{120, 100, 100}, true,  ALL2ALL },
        TestCase{ RGB{0, 255, 255},   YUV{201, 54, -201},   HSV{180, 100, 100}, true,  ALL2ALL },
        TestCase{ RGB{0, 0, 255},     YUV{18, 237, -18},    HSV{240, 100, 100}, true,  ALL2ALL },
        TestCase{ RGB{255, 0, 255},   YUV{73, 182, 182},    HSV{300, 100, 100}, true,  ALL2ALL }, 
        /* Clamp*/
        TestCase{ RGB{88, 180, 88},   YUV{300, 300, 300},   HSV{120, 51, 70},   false, YUV2RGB | YUV2HSV },
        TestCase{ RGB{255, 170, 0},   YUV{176, -176, 79},   HSV{400, 255, 255}, false, HSV2RGB | HSV2YUV }

        // clang-format on
        ));

TEST_P(ConvertersTest, RgbToYuvTest) {
  TestCase testcase = GetParam();
  if (!(std::get<4>(testcase) & RGB2YUV))
    GTEST_SKIP() << "Test case is not intended for this test";

  rgb = std::get<0>(testcase);
  yuv = std::get<1>(testcase);

  if (std::get<3>(testcase)) {
    yuv.Clamp();
  }
  YUV res = Convert::RgbToYuv(rgb);
  EXPECT_NEAR(res.y, yuv.y, 1.0);
  EXPECT_NEAR(res.u, yuv.u, 1.0);
  EXPECT_NEAR(res.v, yuv.v, 1.0);
}

TEST_P(ConvertersTest, RgbToHsvTest) {
  TestCase testcase = GetParam();
  if (!(std::get<4>(testcase) & RGB2HSV))
    GTEST_SKIP() << "Test case is not intended for this test";

  rgb = std::get<0>(testcase);
  hsv = std::get<2>(testcase);

  if (std::get<3>(testcase)) {
    hsv.Clamp();
  }
  HSV res = Convert::RgbToHsv(rgb);
  EXPECT_NEAR(res.hue, hsv.hue, 1.0);
  EXPECT_NEAR(res.saturation, hsv.saturation, 1.0);
  EXPECT_NEAR(res.value, hsv.value, 1.0);
}

TEST_P(ConvertersTest, YuvToRgbTest) {
  TestCase testcase = GetParam();
  if (!(std::get<4>(testcase) & YUV2RGB))
    GTEST_SKIP() << "Test case is not intended for this test";

  rgb = std::get<0>(testcase);
  yuv = std::get<1>(testcase);

  if (std::get<3>(testcase)) {
    yuv.Clamp();
  }
  RGB res = Convert::YuvToRgb(yuv);
  EXPECT_NEAR(res.r, rgb.r, 1);
  EXPECT_NEAR(res.g, rgb.g, 1);
  EXPECT_NEAR(res.b, rgb.b, 1);
}

TEST_P(ConvertersTest, YuvToHsvTest) {
  TestCase testcase = GetParam();
  if (!(std::get<4>(testcase) & YUV2HSV))
    GTEST_SKIP() << "Test case is not intended for this test";

  hsv = std::get<2>(testcase);
  yuv = std::get<1>(testcase);

  if (std::get<3>(testcase)) {
    hsv.Clamp();
    yuv.Clamp();
  }
  HSV res = Convert::YuvToHsv(yuv);
  EXPECT_NEAR(res.hue, hsv.hue, 1.0);
  EXPECT_NEAR(res.saturation, hsv.saturation, 1.0);
  EXPECT_NEAR(res.value, hsv.value, 1.0);
}

TEST_P(ConvertersTest, HsvToRgbTest) {
  TestCase testcase = GetParam();
  if (!(std::get<4>(testcase) & HSV2RGB))
    GTEST_SKIP() << "Test case is not intended for this test";

  hsv = std::get<2>(testcase);
  rgb = std::get<0>(testcase);

  if (std::get<3>(testcase)) {
    hsv.Clamp();
  }
  RGB res = Convert::HsvToRgb(hsv);
  EXPECT_NEAR(res.r, rgb.r, 1.0);
  EXPECT_NEAR(res.g, rgb.g, 1.0);
  EXPECT_NEAR(res.b, rgb.b, 1.0);
}

TEST_P(ConvertersTest, HsvToYuvTest) {
  TestCase testcase = GetParam();
  if (!(std::get<4>(testcase) & HSV2YUV))
    GTEST_SKIP() << "Test case is not intended for this test";

  hsv = std::get<2>(testcase);
  yuv = std::get<1>(testcase);

  if (std::get<3>(testcase)) {
    hsv.Clamp();
    yuv.Clamp();
  }
  YUV res = Convert::HsvToYuv(hsv);
  EXPECT_NEAR(res.y, yuv.y, 1.0);
  EXPECT_NEAR(res.u, yuv.u, 1.0);
  EXPECT_NEAR(res.v, yuv.v, 1.0);
}
