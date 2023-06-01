#pragma once

#include "Datatypes.h"
#include <vector>
using namespace ColorModels;

/**
 * @brief Класс-конвертор цветовых моделей
 *
 */
class Convert {
public:
  static YUV RgbToYuv(RGB rgb);
  static HSV RgbToHsv(RGB rgb);
  static RGB YuvToRgb(YUV yuv);
  static HSV YuvToHsv(YUV yuv);
  static RGB HsvToRgb(HSV hsv);
  static YUV HsvToYuv(HSV hsv);
};