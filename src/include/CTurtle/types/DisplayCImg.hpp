#include "CTurtle/types/AbstractDisplay.hpp"

#include <stdint.h>
#ifndef CTURTLE_TYPES_DISPLAYCIMG_HPP
#define CTURTLE_TYPES_DISPLAYCIMG_HPP

namespace cimg_library {
struct CImgDisplay;
template <typename T> struct CImg;
} // namespace cimg_library

namespace cturtle {
class Display : public AbstractDisplay {
public:
  Display(int x, int y, const std::string &name, int normalization);

  bool should_close() override;

  void set_title(const std::string &title) override;

  int width() const override;

  int height() const override;

  bool is_resized() override;

  void resize(bool force_redraw = true) override;

  bool is_closed() override;

  void close() override;

  int mouse_x() override;

  int mouse_y() override;

  unsigned int button() const override;

  bool is_event() const override;

  bool is_key(unsigned int key) const override;

  cimg_library::CImgDisplay *internal() const;

  void set_normalization(int amt) override;

  void display(cimg_library::CImg<uint8_t> &img);

  void snapshot(cimg_library::CImg<uint8_t> &img);

  int window_width() const override;

  int window_height() const override;

private:
  cimg_library::CImgDisplay *handle;
};
} // namespace cturtle
#endif
