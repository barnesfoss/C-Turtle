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

template <typename T = uint8_t> class Image {
public:
  Image();

  Image(const int size_x, const int size_y = 1, const int size_z = 1, const int size_c = 1);

  Image(const CImg<T> &img);

  Image(const Image<T> &other);

  Image(Image<T> &&other) noexcept;

  Image<T> &operator=(const Image<T> &other);

  Image<T> &operator=(Image<T> &&other) noexcept;

  ~Image();

  operator CImg<T> &();

  operator const CImg<T> &() const;

  int width() const;

  int height() const;

  int depth() const;

  int spectrum() const;

  bool is_empty() const;

  T &operator()(int x, int y = 0, int z = 0, int c = 0);

  const T &operator()(int x, int y = 0, int z = 0, int c = 0) const;

  Image<T> &assign();

  Image<T> &assign(int x, int y = 1, int z = 1, int c = 1);

  Image<T> &assign(const Image<T> &img);

  Image<T> &assign(const CImg<T> &img);

  Image<T> &assign(const Display &disp);

  Image<T> &fill(T value);

  Image<T> get_crop(int x0, int y0, int x1, int y1) const;

  Image<T> &resize(int x, int y);

  Image<T> &resize(const CImg<T> &img);

  Image<T> &resize(const Display &disp);

  Image<T> &rotate(float angle, int interpolation = 1, int boundary_conditions = 0);

  Image<T> &channels(int c0, int c1);

  Image<T> get_shared_channel(int channel) const;

  Image<T> &draw_line(int x0, int y0, int x1, int y1, const T *color, float opacity = 1.0f);

  Image<T> &draw_circle(int x, int y, int radius, const T *color, float opacity = 1.0f);

  Image<T> &draw_rectangle(int x0, int y0, int x1, int y1, const T *color, float opacity = 1.0f);

  Image<T> &draw_polygon(const CImg<int> &points, const T *color, float opacity = 1.0f);

  Image<T> &draw_image(int x, int y, const CImg<T> &img, float opacity = 1.0f);

  Image<T> &draw_image(int x, int y, const Image<T> &img, float opacity = 1.0f);

  Image<T> &draw_image(
      int x, int y, const Image<T> &img, const Image<T> &mask, int channel, float opacity = 1.0f);

  Image<T> &draw_triangle(int x0,
                          int y0,
                          int x1,
                          int y1,
                          int x2,
                          int y2,
                          const CImg<T> &texture,
                          int tx0,
                          int ty0,
                          int tx1,
                          int ty1,
                          int tx2,
                          int ty2,
                          float opacity = 1.0f,
                          float brightness = 1.0f);

  Image<T> &save(const char *filename) const;

  Image<T> &save(const std::string &filename) const;

private:
  CImg<T> *impl_;
};
} // namespace cturtle
#endif
