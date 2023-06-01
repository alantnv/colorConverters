#include <Converters.h>
#include <algorithm>
#include <cmath>

using namespace ColorModels;

// Done
YUV Convert::RgbToYuv(RGB rgb) {
  YUV yuv;
  yuv.y = std::ceil(Kr * rgb.r + (1 - Kr - Kb) * rgb.g + Kb * rgb.b);
  yuv.u = std::ceil(rgb.b - yuv.y);
  yuv.v = std::ceil(rgb.r - yuv.y);
  return yuv;
}

// Done
HSV Convert::RgbToHsv(RGB rgb) {
  HSV hsv;
  float r = float(rgb.r / 255.0);
  float g = float(rgb.g / 255.0);
  float b = float(rgb.b / 255.0);
  float max = std::max({r, g, b});
  float min = std::min({r, g, b});
  float diff = max - min;
#pragma region "Value"
  hsv.value = max * 100;
#pragma endregion
#pragma region "Saturation"
  hsv.saturation = max == 0 ? 0 : (1 - min / max) * float(100.0);
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
RGB Convert::YuvToRgb(YUV yuv) {
  yuv.Clamp();
  uint8_t r = yuv.y + yuv.v;
  uint8_t g = yuv.y - (Kr * yuv.v + Kb * yuv.u) / (1 - Kr - Kb);
  uint8_t b = yuv.y + yuv.u;
  return RGB{r, g, b};
}
// Done
HSV Convert::YuvToHsv(YUV yuv) {
  RGB rgb = YuvToRgb(yuv);
  return RgbToHsv(rgb);
}

// Done
RGB Convert::HsvToRgb(HSV hsv) {
  hsv.Clamp();
  float C = hsv.value / float(100.0) * hsv.saturation / float(100.0);

  float X =
      C * (1 - std::abs(std::fmod(hsv.hue / float(60.0), float(2.0)) - 1));
  float m = hsv.value / float(100.0) - C;

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
YUV Convert::HsvToYuv(HSV hsv) {
  hsv.Clamp();
  RGB rgb = HsvToRgb(hsv);
  return RgbToYuv(rgb);
}
