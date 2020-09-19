#include "ImageCorrector.hpp"

#include <iostream>
#include <limits>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

ImageCorrector::ImageCorrector(uint8_t intensity_percent)
    : intensity(intensity_percent * 256 / 100) {}

ImageCorrector::ImageCorrector(uint8_t intensity_percent,
                               std::size_t max_distance,
                               std::size_t distance_difference_threshold)
    : max_distance(max_distance),
      distance_difference_threshold(distance_difference_threshold),
      intensity(intensity_percent * 256 / 100) {}

std::shared_ptr<std::vector<std::array<float, 14>>> ImageCorrector::CheckImage(
    const std::string& image_path) {
  std::shared_ptr<std::vector<std::array<float, 14>>> result(
      new std::vector<std::array<float, 14>>());

  cv::Mat image = cv::imread(image_path, cv::IMREAD_GRAYSCALE);

  if (!image.data) {
    std::cout << "Error: the image wasn't correctly loaded." << std::endl;
    return result;
  }

  std::vector<BrokenPoint> listbpoint = FindBrokenPoint(image);
  result->reserve(listbpoint.size());

  for (auto& i : listbpoint) {
    std::array<float, 14> a = {
        convert_pixel_to_coord(i.point.coloumn, image.cols),
        convert_pixel_to_coord(i.point.row, image.rows),
        convert_pixel_to_coord(i.lcp[0][0].point.coloumn, image.cols),
        convert_pixel_to_coord(i.lcp[0][0].point.row, image.rows),
        i.lcp[0][0].weigth,
        convert_pixel_to_coord(i.lcp[0][1].point.coloumn, image.cols),
        convert_pixel_to_coord(i.lcp[0][1].point.row, image.rows),
        i.lcp[0][1].weigth,
        convert_pixel_to_coord(i.lcp[1][0].point.coloumn, image.cols),
        convert_pixel_to_coord(i.lcp[1][0].point.row, image.rows),
        i.lcp[1][0].weigth,
        convert_pixel_to_coord(i.lcp[1][1].point.coloumn, image.cols),
        convert_pixel_to_coord(i.lcp[1][1].point.row, image.rows),
        i.lcp[1][1].weigth};

    result->emplace_back(std::move(a));
  }

  return result;
}

void ImageCorrector::Print_Corrector(const std::string& image_path) {
  cv::Mat image = cv::imread(image_path, cv::IMREAD_GRAYSCALE);

  if (!image.data) {
    std::cout << "Error: the image wasn't correctly loaded." << std::endl;
    return;
  }

  std::vector<BrokenPoint> listbpoint = FindBrokenPoint(image);

  for (auto& i : listbpoint) {
    image.at<uchar>(i.point.row, i.point.coloumn) =
        static_cast<uchar>(i.CalculateBrokenPoint());
  }

  cv::imwrite("test.png", image);
  // cv::imshow("Image", image);
  // cv::waitKey();
}

float ImageCorrector::convert_pixel_to_coord(uint32_t index, uint32_t size) {
  return (index + 0.5f) * 2 / size - 1.f;
}

std::vector<BrokenPoint> ImageCorrector::FindBrokenPoint(const cv::Mat& image) {
  std::vector<BrokenPoint> result;
  result.reserve(10);

  for (int r = 0; r < image.rows; r++) {
    for (int c = 0; c < image.cols; c++) {
      if (image.at<uchar>(r, c) < intensity) continue;

      {
        BrokenPoint p;
        p.point.row = r;
        p.point.coloumn = c;

        p.lcp[0] = Line(
            FindCorrectPoint(p.point, image, Coordinate::Up, max_distance),
            FindCorrectPoint(p.point, image, -Coordinate::Up, max_distance));

        p.lcp[1] = Line(
            FindCorrectPoint(p.point, image, Coordinate::Left, max_distance),
            FindCorrectPoint(p.point, image, -Coordinate::Left, max_distance));

        if (p.lcp[0].getValid() && p.lcp[1].getValid()) {
          for (auto i = 0; i < 2; i++)
            for (auto j = 0; j < 2; j++) {
              p.lcp[i][j].weigth = p.lcp[i][j].weigth / 2;
            }
          result.emplace_back(std::move(p));
          continue;
        } else if (p.lcp[0].getValid() || p.lcp[1].getValid()) {
          result.emplace_back(std::move(p));
          continue;
        }
      }

      {
        BrokenPoint p;
        p.point.row = r;
        p.point.coloumn = c;

        p.lcp[0] =
            Line(FindCorrectPoint(p.point, image, Coordinate::Down_Right,
                                  max_distance),
                 FindCorrectPoint(p.point, image, -Coordinate::Down_Right,
                                  max_distance));

        p.lcp[1] = Line(FindCorrectPoint(p.point, image, Coordinate::Up_Right,
                                         max_distance),
                        FindCorrectPoint(p.point, image, -Coordinate::Up_Right,
                                         max_distance));

        if (p.lcp[0].getValid() && p.lcp[1].getValid()) {
          for (auto i = 0; i < 2; i++)
            for (auto j = 0; j < 2; j++) {
              p.lcp[i][j].weigth = p.lcp[i][j].weigth / 2;
            }
          result.emplace_back(std::move(p));
          continue;
        } else if (p.lcp[0].getValid() || p.lcp[1].getValid()) {
          result.emplace_back(std::move(p));
          continue;
        }
      }

      {
        BrokenPoint p;
        p.point.row = r;
        p.point.coloumn = c;

        p.lcp[0] = Line(
            FindCorrectPoint(p.point, image, Coordinate::Up, max_distance),
            FindCorrectPoint(p.point, image, -Coordinate::Up, max_distance));

        p.lcp[1] = Line(
            FindCorrectPoint(p.point, image, Coordinate::Left, max_distance),
            FindCorrectPoint(p.point, image, -Coordinate::Left, max_distance));

        int count_points = 0;
        for (auto i = 0; i < 2; i++)
          for (auto j = 0; j < 2; j++) {
            p.lcp[i][j].weigth = (p.lcp[i][j].valid) ? 1 : 0;
            if (p.lcp[i][j].valid) ++count_points;
          }

        for (auto i = 0; i < 2; i++)
          for (auto j = 0; j < 2; j++) {
            p.lcp[i][j].weigth = p.lcp[i][j].weigth / count_points;
          }
        result.emplace_back(std::move(p));
        continue;
      }
    }
  }
  return result;
}

CorrectionPoint ImageCorrector::FindCorrectPoint(Coordinate point,
                                                 const cv::Mat& image,
                                                 const Coordinate& where,
                                                 const int max_distance) {
  Coordinate size_image(image.rows, image.cols);
  point += where;
  CorrectionPoint result;
  result.distance = 1;
  result.valid = false;

  while (point.InImage(size_image) && result.distance <= max_distance) {
    uint8_t inten = image.at<uchar>(point.row, point.coloumn);
    if (inten < intensity) {
      result.point.row = point.row;
      result.point.coloumn = point.coloumn;
      result.intensity = inten;
      result.valid = true;
      return result;
    }
    point += where;
    result.distance += 1;
  }

  result.distance = std::numeric_limits<int>::max();
  return result;
}

std::pair<CorrectionPoint, CorrectionPoint> ImageCorrector::FindCorrectPair(
    const Coordinate& point, const cv::Mat& image, const Coordinate& where) {
  CorrectionPoint p1 = FindCorrectPoint(point, image, where);
  CorrectionPoint p2 = FindCorrectPoint(point, image, -where);

  if (std::abs(p1.distance - p2.distance) > distance_difference_threshold) {
    if (p1.distance > p2.distance) {
      p1.distance = std::numeric_limits<int>::max() - 1;
    } else {
      p2.distance = std::numeric_limits<int>::max() - 1;
    }
  }

  return std::make_pair(std::move(p1), std::move(p2));
}