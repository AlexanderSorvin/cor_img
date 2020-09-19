#include "Coordinate.hpp"

Coordinate::Coordinate(int row, int coloumn) : row(row), coloumn(coloumn) {}

bool Coordinate::InImage(const Coordinate& size_image) const {
  return row < size_image.row && row >= 0 && coloumn < size_image.coloumn &&
         coloumn >= 0;
}

Coordinate& Coordinate::operator+=(const Coordinate& add) {
  row += add.row;
  coloumn += add.coloumn;

  return *this;
}

Coordinate Coordinate::operator-() const {
  Coordinate result;

  result.row = -this->row;
  result.coloumn = -this->coloumn;

  return result;
}

Coordinate Coordinate::Up(1, 0);
Coordinate Coordinate::Left(0, -1);

Coordinate Coordinate::Up_Right(1, 1);
Coordinate Coordinate::Down_Right(-1, 1);