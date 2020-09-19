#pragma once

#include <array>
#include <memory>
#include <opencv2/imgproc.hpp>
#include <vector>

#include "BrokenPoint.hpp"
#include "Coordinate.hpp"
#include "CorrectionPoint.hpp"

/**
 * @brief Класс корректор изображения
 *
 */
class ImageCorrector {
 public:
  ImageCorrector() = default;
  ImageCorrector(uint8_t intensity_percent);
  ImageCorrector(uint8_t intensity_percent, std::size_t max_distance,
                 std::size_t distance_difference_threshold);

  ~ImageCorrector() = default;

  /**
   * @brief Функция получения вектора битых пикселей с коррекцией
   *
   * @param image_path путь до картинки
   * @return std::shared_ptr<std::vector<std::array<float, 14>>>
   *
   * @warning При типе std::shared_ptr<std::vector<float[14]>>
   * parenthesized initializer in array new [-fpermissive]
   */
  std::shared_ptr<std::vector<std::array<float, 14>>> CheckImage(
      const std::string& image_path);

  /**
   * @brief Вывести скорректированное изображение
   *
   * @param image_path путь до картинки
   */
  void Print_Corrector(const std::string& image_path);

 protected:
  std::size_t max_distance = 5;
  std::size_t distance_difference_threshold = 2;
  std::uint8_t intensity = 128;

  float convert_pixel_to_coord(uint32_t index, uint32_t size);
  std::shared_ptr<std::vector<float[14]>> find_pixel();
  std::vector<BrokenPoint> FindBrokenPoint(const cv::Mat& image);

  CorrectionPoint FindCorrectPoint(
      Coordinate point, const cv::Mat& image, const Coordinate& where,
      const int max_distance = std::numeric_limits<int>::max());

  std::pair<CorrectionPoint, CorrectionPoint> FindCorrectPair(
      const Coordinate& point, const cv::Mat& image, const Coordinate& where);

  void CalcWeigthPoint();
};