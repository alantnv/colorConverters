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
  static YUV RgbToYuv(const RGB &rgb);
  static HSV RgbToHsv(const RGB &rgb);
  static RGB YuvToRgb(const YUV &yuv);
  static HSV YuvToHsv(const YUV &yuv);
  static RGB HsvToRgb(const HSV &hsv);
  static YUV HsvToYuv(const HSV &hsv);
  static float Round(float number, uint8_t decimalNumbers);
};