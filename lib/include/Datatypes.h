#pragma once
#include <cmath>
#include <cstdint>

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
  return std::abs(lhs.r - rhs.r) <= 1 && std::abs(lhs.g - rhs.g) <= 1 &&
         std::abs(lhs.b - rhs.b) <= 1;
}

/**
 * @brief Структура цветовой модели HSV
 *
 */
struct HSV {
  /// Тон
  uint16_t hue;
  /// Насыщенность
  float saturation;
  /// Яркость
  float value;
};

inline bool operator==(const HSV &lhs, const HSV &rhs) {
  return lhs.hue == rhs.hue &&
         std::fabs(lhs.saturation - rhs.saturation) <= 0.1 &&
         std::fabs(lhs.value - rhs.value) <= 0.1;
}

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
};

inline bool operator==(const YUV &lhs, const YUV &rhs) {
  return std::fabs(lhs.y - rhs.y) <= 0.1 && std::fabs(lhs.y - rhs.y) <= 0.1 &&
         std::fabs(lhs.v - rhs.v) <= 0.1;
}

}; // namespace ColorModels