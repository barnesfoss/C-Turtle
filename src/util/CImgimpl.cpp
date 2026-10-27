#include "CImg.h"
#include "types/AbstractDisplay.hpp"
#include "types/DisplayCImg.hpp"

namespace cturtle {
Display::Display(int x, int y, const std::string &name, int normalization) {
  handle = new cimg_library::CImgDisplay(x, y, name.c_str(), normalization);
}

void Display::set_title(const std::string &name) {
  handle->set_title(name.c_str());
}

int Display::width() const {
  return handle->width();
}

int Display::height() const {
  return handle->height();
}

bool Display::is_resized() {
  return handle->is_resized();
}

void Display::resize(bool force_redraw) {
  handle->resize(force_redraw);
}

bool Display::is_closed() {
  return handle->is_closed();
}

void Display::close() {
  handle->close();
}

int Display::mouse_x() {
  return handle->mouse_x();
}

int Display::mouse_y() {
  return handle->mouse_y();
}

unsigned int Display::button() const {
  return handle->button();
}

bool Display::is_event() const {
  return handle->is_event();
}

bool Display::is_key(unsigned int key) const {
  return handle->is_key(key);
}

void Display::set_normalization(int amt) {
  handle->set_normalization(amt);
}

void Display::display(cimg_library::CImg<uint8_t> &img) {
  handle->display(img);
}

void Display::snapshot(cimg_library::CImg<uint8_t> &img) {
  handle->snapshot(img);
}

int Display::window_width() const {
  return handle->window_width();
}

int Display::window_height() const {
  return handle->window_height();
}

cimg_library::CImgDisplay *Display::internal() const {
  return handle;
}

bool Display::should_close() {
  return handle->is_closed();
}
} // namespace cturtle
