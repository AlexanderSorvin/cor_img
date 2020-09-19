#include "BrokenPoint.hpp"

#include <cmath>

uint8_t BrokenPoint::CalculateBrokenPoint() const {
  double result = 0.;
  for (auto i = 0; i < 2; i++)
    for (auto j = 0; j < 2; j++) {
      result += lcp[i][j].weigth * lcp[i][j].intensity;
    }

  return static_cast<uint8_t>(round(result));
}