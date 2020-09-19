#include <iostream>

#include "ImageCorrector.hpp"

int main(int argc, char** argv) {
  std::string image_path = "image.png";

  ImageCorrector icor;
  icor.Print_Corrector(image_path);

  auto result = icor.CheckImage(image_path);

  for (auto i : *result) {
    std::cout << "{";
    for (auto j : i) {
      std::cout << j << " ";
    }
    std::cout << "}" << std::endl;
  }

  return 0;
}