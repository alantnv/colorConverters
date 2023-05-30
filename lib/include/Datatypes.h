#pragma once
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
  // Ограничиваем диапазон значений
  void Clamp() {
    if (r > 255)
      r = 255;
    if (g > 255)
      g = 255;
    if (b > 255)
      b = 255;
  }
};

inline bool operator==(const RGB &lhs, const RGB &rhs) {
  return std::abs(lhs.r - rhs.r) <= 1 && std::abs(lhs.g - rhs.g) <= 1 &&
         std::abs(lhs.b - rhs.b) <= 1;
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
    if (hue > 360)
      hue = 360;
    if (saturation > 100)
      saturation = 100;
    if (value > 100)
      value = 100;
  }
};

inline bool operator==(const HSV &lhs, const HSV &rhs) {
  return std::abs(lhs.hue - rhs.hue) <= 1 &&
         std::abs(lhs.saturation - rhs.saturation) <= 1 &&
         std::abs(lhs.value - rhs.value) <= 1;
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
    y = y > 255 ? 255 : y < 0 ? 0 : y;
    u = u > maxU ? maxU : u < -1 * maxU ? -1 * maxU : u;
    v = v > maxV ? maxV : v < -1 * maxV ? -1 * maxV : v;
  }
};

inline bool operator==(const YUV &lhs, const YUV &rhs) {
  return std::fabs(lhs.y - rhs.y) <= 1 && std::fabs(lhs.y - rhs.y) <= 1 &&
         std::fabs(lhs.v - rhs.v) <= 1;
}
inline bool operator!=(const YUV &lhs, const YUV &rhs) { return !(lhs == rhs); }

}; // namespace ColorModels