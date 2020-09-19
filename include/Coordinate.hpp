#pragma once

/**
 * @brief Координаты пикселя
 */
struct Coordinate {
  Coordinate() = default;
  Coordinate(int row, int coloumn);

  /**
   * @brief Строка
   */
  int row;
  /**
   * @brief Стоблец
   * 
   */
  int coloumn;

  Coordinate& operator+=(const Coordinate& add);
  Coordinate operator-() const;

  /**
   * @brief Проверить, находится ли наш пиксель внутри изображения
   * 
   * @param size_image размеры изображения
   * @return нахождение
   */
  bool InImage(const Coordinate& size_image) const;

  static Coordinate Up;
  static Coordinate Left;

  static Coordinate Up_Right;
  static Coordinate Down_Right;
};