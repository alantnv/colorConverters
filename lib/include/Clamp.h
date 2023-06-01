/**
 * @file Clamp.h
 * @author АО ЦНИИ Циклон ОП Великий Новгород
 * @brief Объявление и реализация метода, вписывающего значение в заданные границы
 */
#pragma once

#if defined(_MSVC_LANG) && (_MSVC_LANG >= 201703L) || (__cplusplus >= 201703L)

#include <algorithm> // std::clamp
#define clamp std::clamp

#else
/**
 * @brief Вписывает значение в заданные границы
 *
 * @tparam T Тип данных значения и границ
 * @param[in] v  Вписываемое значение
 * @param[in] lo Нижняя граница
 * @param[in] hi Верхняя граница
 * @return Возвращает значение вписанное в заданные границы
 */
template<typename T>
inline constexpr const T&
clamp(const T& v, const T& lo, const T& hi)
{
  return v < lo ? lo : (v > hi ? hi : v);
}
#endif