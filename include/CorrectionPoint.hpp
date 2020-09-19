#pragma once

#include "Coordinate.hpp"
#include <cstdint>

/**
 * @brief Структура пикселя, участвующего в коррекции
 */
struct CorrectionPoint {
  /**
   * @brief Координаты пикселя
   */
  Coordinate point;
  /**
   * @brief Коррекционный вес
   */
  float weigth;
  /**
   * @brief Дальность от пикселя, который необходимо скоректировать
   */
  int distance;
  /**
   * @brief Интенсивность
   * 
   */
  uint8_t intensity;
  /**
   * @brief Проверка на существование такого пикселя
   * 
   */
  bool valid;
};