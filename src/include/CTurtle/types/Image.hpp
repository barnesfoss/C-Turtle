// Copyright 2021 Jesse W. Walker
//
// Licensed under the MIT License.
// See LICENSE for details.
#ifndef CTURTLE_TYPES_IMAGE_HPP
#define CTURTLE_TYPES_IMAGE_HPP
#include "CTurtle/types/DisplayCImg.hpp"

#include <cstdint>
#include <string>

namespace cimg_library {
template <typename T> struct CImg;
}

namespace cturtle {
using cimg_library::CImg;

class Image {
public:
  using value_type = uint8_t;

  Image();

  Image(const int size_x, const int size_y = 1, const int size_z = 1, const int size_c = 1);

  Image(const CImg<uint8_t> &img);

  Image(const Image &other);

  Image(Image &&other) noexcept;

  Image &operator=(const Image &other);

  Image &operator=(Image &&other) noexcept;

  ~Image();

  operator CImg<uint8_t> &();

  operator const CImg<uint8_t> &() const;

  int width() const;

  int height() const;

  int depth() const;

  int spectrum() const;

  bool is_empty() const;

  uint8_t &operator()(int x, int y = 0, int z = 0, int c = 0);

  const uint8_t &operator()(int x, int y = 0, int z = 0, int c = 0) const;

  Image &assign();

  Image &assign(int x, int y = 1, int z = 1, int c = 1);

  Image &assign(const Image &img);

  Image &assign(const CImg<uint8_t> &img);

  Image &assign(const Display disp);

  Image &fill(uint8_t value);

  Image get_crop(int x0, int y0, int x1, int y1) const;

  Image &resize(int x, int y);

  Image &resize(const CImg<uint8_t> &img);

  Image &resize(const Display &disp);

  Image &rotate(float angle, int interpolation = 1, int boundary_conditions = 0);

  Image &channels(int c0, int c1);

  Image get_shared_channel(int channel) const;

  Image &draw_line(int x0, int y0, int x1, int y1, const uint8_t *color, float opacity = 1.0f);

  Image &draw_circle(int x, int y, int radius, const uint8_t *color, float opacity = 1.0f);

  Image &draw_rectangle(int x0, int y0, int x1, int y1, const uint8_t *color, float opacity = 1.0f);

  Image &draw_polygon(const CImg<uint8_t> &points, const uint8_t *color, float opacity = 1.0f);

  Image &draw_image(int x, int y, const CImg<uint8_t> &img, float opacity = 1.0f);

  Image &draw_image(int x, int y, const Image &img, float opacity = 1.0f);

  Image &draw_image(
      int x, int y, const Image &img, const Image &mask, int channel, float opacity = 1.0f);

  Image &draw_triangle(int x0,
                       int y0,
                       int x1,
                       int y1,
                       int x2,
                       int y2,
                       const CImg<uint8_t> &texture,
                       int tx0,
                       int ty0,
                       int tx1,
                       int ty1,
                       int tx2,
                       int ty2,
                       float opacity = 1.0f,
                       float brightness = 1.0f);

  Image &save(const char *filename) const;

  Image &save(const std::string &filename) const;

private:
  CImg<uint8_t> *impl_;
};
} // namespace cturtle
#endif
