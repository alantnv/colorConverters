#include "../include/Converters.h"
#include <algorithm>
#include <cmath>

using namespace ColorModels;

float Convert::Round(float number, uint8_t decimalNumbers) {
  float roundingPart = float(std::pow(10, decimalNumbers));
  return std::round(number * roundingPart) / roundingPart;
}
// Done
YUV Convert::RgbToYuv(const RGB &rgb) {
  YUV yuv;
  yuv.y = Round(Kr * rgb.r + (1 - Kr - Kb) * rgb.g + Kb * rgb.b, 0);
  yuv.u = Round(rgb.b - yuv.y, 0);
  yuv.v = Round(rgb.r - yuv.y, 0);
  return yuv;
}

// Done
HSV Convert::RgbToHsv(const RGB &rgb) {
  HSV hsv;
  float r = float(rgb.r / 255.0);
  float g = float(rgb.g / 255.0);
  float b = float(rgb.b / 255.0);
  float max = std::max({r, g, b});
  float min = std::min({r, g, b});
  float diff = max - min;
#pragma region "Value"
  hsv.value = Round(max * float(100.0), 0);
#pragma endregion
#pragma region "Saturation"
  hsv.saturation = max == 0 ? 0 : Round(((1 - min / max) * float(100.0)), 1);
#pragma endregion

#pragma region "Hue"
  hsv.hue = 0;
  if (max == r && g >= b)
    hsv.hue = uint16_t(std::round(60.0 * std::fmod((g - b) / diff, 6)));
  if (max == g)
    hsv.hue = uint16_t(std::round(60.0 * ((b - r) / diff + 2)));
  if (max == b && r >= g)
    hsv.hue = uint16_t(std::round(60.0 * ((r - g) / diff + 4)));
  return hsv;
#pragma endregion
}

// Done
RGB Convert::YuvToRgb(const YUV &yuv) {
  uint8_t r = yuv.y + yuv.v;
  uint8_t g = yuv.y - (Kr * yuv.v + Kb * yuv.u) / (1 - Kr - Kb);
  uint8_t b = yuv.y + yuv.u;
  return RGB{r, g, b};
}
// Done
HSV Convert::YuvToHsv(const YUV &yuv) { return RgbToHsv(YuvToRgb(yuv)); }

// Done
RGB Convert::HsvToRgb(const HSV &hsv) {
  float C = hsv.value / 100 * hsv.saturation / 100;

  float X =
      C * (1 - std::abs(std::fmod(hsv.hue / float(60.0), float(2.0)) - 1));
  float m = hsv.value / 100 - C;

  float R, G, B;
  if (hsv.hue >= 0 && hsv.hue < 60) {
    R = C;
    G = X;
    B = 0;
  } else if (hsv.hue >= 60 && hsv.hue < 120) {
    R = X;
    G = C;
    B = 0;
  } else if (hsv.hue >= 120 && hsv.hue < 180) {
    R = 0;
    G = C;
    B = X;
  } else if (hsv.hue >= 180 && hsv.hue < 240) {
    R = 0;
    G = X;
    B = C;
  } else if (hsv.hue >= 240 && hsv.hue < 300) {
    R = X;
    G = 0;
    B = C;
  } else {
    R = C;
    G = 0;
    B = X;
  }
  RGB rgb = {uint8_t(std::round((R + m) * 255.0)),
             uint8_t(std::round((G + m) * 255.0)),
             uint8_t(std::round((B + m) * 255.0))};
  return rgb;
}

// Done
YUV Convert::HsvToYuv(const HSV &hsv) { return RgbToYuv(HsvToRgb(hsv)); }
