#pragma once
#include <Clamp.h>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <typeinfo>

namespace ColorModels {
constexpr float Kr = float(0.2125);
constexpr float Kb = float(0.0722);

/**
 * @brief Структура цветовой модели RGB
 *
 */
struct RGB {
  /// Компонента красного
  uint8_t r;
  /// Компонента зелёного
  uint8_t g;
  /// Компонента синего
  uint8_t b;
};

inline bool operator==(const RGB &lhs, const RGB &rhs) {
  return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b;
}

inline bool operator!=(const RGB &lhs, const RGB &rhs) { return !(lhs == rhs); }

/**
 * @brief Структура цветовой модели HSV
 *
 */
struct HSV {
  /// Тон
  uint16_t hue;
  /// Насыщенность
  uint8_t saturation;
  /// Яркость
  uint8_t value;
  // Ограничиваем диапазон значений
  void Clamp() {
    hue %= 360;
    if (saturation > 100)
      saturation = 100;
    if (value > 100)
      value = 100;
  }
};

inline bool operator==(const HSV &lhs, const HSV &rhs) {
  return lhs.hue == rhs.hue && lhs.saturation == rhs.saturation &&
         lhs.value == rhs.value;
}
inline bool operator!=(const HSV &lhs, const HSV &rhs) { return !(lhs == rhs); }

/**
 * @brief Структура цветовой модели YUV
 *
 */
struct YUV {
  /// Яркость
  float y;
  /// Цветоразностная компонента U
  float u;
  /// Цветоразностная компонента V
  float v;
  // Ограничиваем диапазон значений
  void Clamp() {
    float maxU = (1 - Kb) * 255;
    float maxV = (1 - Kr) * 255;
    clamp(y, float(0), float(255));
    clamp(u, -maxU, maxU);
    clamp(v, -maxV, maxV);
  }
};

inline bool operator==(const YUV &lhs, const YUV &rhs) {
  return std::fabs(lhs.y - rhs.y) < 0.1 && std::fabs(lhs.y - rhs.y) < 0.1 &&
         std::fabs(lhs.v - rhs.v) < 0.1;
}
inline bool operator!=(const YUV &lhs, const YUV &rhs) { return !(lhs == rhs); }

}; // namespace ColorModels