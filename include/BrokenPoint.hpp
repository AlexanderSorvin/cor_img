#pragma once

#include "Coordinate.hpp"
#include "Line.hpp"

/**
 * @brief Структура битых пикселей
 **/
struct BrokenPoint {
  BrokenPoint() = default;

  /**
   * @brief Координаты в пикселях
   **/
  Coordinate point;
  /**
   * @brief Линии интерполяции
   **/
  Line lcp[2];

  /**
   * @brief Посчитать интенсивность, которая должна быть у битого пикселя
   **/
  uint8_t CalculateBrokenPoint() const;
};