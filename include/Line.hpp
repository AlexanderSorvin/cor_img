#pragma once

#include "CorrectionPoint.hpp"

/**
 * @brief Структура линии интерполяции
 *
 */
struct Line {
  Line() = default;
  Line(CorrectionPoint&& p1, CorrectionPoint&& p2);

  /**
   * @brief Получить валидность линии
   *
   * @return валидность
   */
  bool getValid() const;
  /**
   * @brief Сумму дальностей пикселей внутри линии
   *
   * @return дальность
   */
  int getDistance() const;

  /**
   * @brief Получить пиксель
   *
   * @param index индекс пикселя (1 или 2)
   * @return Структура пикселя
   */
  CorrectionPoint& operator[](int index);
  /**
   * @brief Получить пиксель
   *
   * @param index индекс пикселя (1 или 2)
   * @return Структура пикселя
   */
  const CorrectionPoint& operator[](int index) const;

 protected:
  CorrectionPoint p[2];
};
