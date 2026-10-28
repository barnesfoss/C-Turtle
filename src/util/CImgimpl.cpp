#include "CImg.h"
#include "types/DisplayCImg.hpp"
#include "types/Image.hpp"
#include "util/io.hpp"

#include <cstdint>
#include <string>
#include <utility>

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

template <typename T> Image<T>::Image() : impl_(new CImg<T>()) {}

template <typename T>
Image<T>::Image(const int size_x, const int size_y, const int size_z, const int size_c)
    : impl_(new CImg<T>(size_x, size_y, size_z, size_c)) {}

template <typename T> Image<T>::Image(const CImg<T> &img) : impl_(new CImg<T>(img)) {}

template <typename T> Image<T>::Image(const Image<T> &other) : impl_(new CImg<T>(*other.impl_)) {}

template <typename T>
Image<T>::Image(Image<T> &&other) noexcept : impl_(std::exchange(other.impl_, nullptr)) {}

template <typename T> Image<T> &Image<T>::operator=(const Image<T> &other) {
  if (this != &other) {
    if (other.impl_ == nullptr) {
      delete impl_;
      impl_ = nullptr;
    } else if (impl_ == nullptr) {
      impl_ = new CImg<T>(*other.impl_);
    } else {
      *impl_ = *other.impl_;
    }
  }
  return *this;
}

template <typename T> Image<T> &Image<T>::operator=(Image<T> &&other) noexcept {
  if (this != &other) {
    delete impl_;
    impl_ = std::exchange(other.impl_, nullptr);
  }
  return *this;
}

template <typename T> Image<T>::~Image() {
  delete impl_;
}

template <typename T> Image<T>::operator CImg<T> &() {
  return *impl_;
}

template <typename T> Image<T>::operator const CImg<T> &() const {
  return *impl_;
}

template <typename T> T &Image<T>::operator()(int x, int y, int z, int c) {
  return (*impl_)(x, y, z, c);
}

template <typename T> const T &Image<T>::operator()(int x, int y, int z, int c) const {
  return (*impl_)(x, y, z, c);
}

template <typename T> int Image<T>::width() const {
  return impl_ ? impl_->width() : 0;
}

template <typename T> int Image<T>::height() const {
  return impl_ ? impl_->height() : 0;
}

template <typename T> int Image<T>::depth() const {
  return impl_ ? impl_->depth() : 0;
}

template <typename T> int Image<T>::spectrum() const {
  return impl_ ? impl_->spectrum() : 0;
}

template <typename T> bool Image<T>::is_empty() const {
  return impl_ == nullptr || impl_->is_empty();
}

template <typename T> Image<T> &Image<T>::assign() {
  if (impl_) {
    impl_->assign();
  }
  return *this;
}

template <typename T> Image<T> &Image<T>::assign(int x, int y, int z, int c) {
  if (!impl_) {
    impl_ = new CImg<T>();
  }
  impl_->assign(x, y, z, c);
  return *this;
}

template <typename T> Image<T> &Image<T>::assign(const Image<T> &img) {
  if (this != &img) {
    if (!img.impl_) {
      delete impl_;
      impl_ = nullptr;
    } else {
      if (!impl_) {
        impl_ = new CImg<T>(*img.impl_);
      } else {
        *impl_ = *img.impl_;
      }
    }
  }
  return *this;
}

template <typename T> Image<T> &Image<T>::assign(const CImg<T> &img) {
  if (!impl_) {
    impl_ = new CImg<T>(img);
  } else {
    impl_->assign(img);
  }
  return *this;
}

template <typename T> Image<T> &Image<T>::assign(const Display &disp) {
  if (!impl_) {
    impl_ = new CImg<T>();
  }
  impl_->assign(*disp.internal());
  return *this;
}

template <typename T> Image<T> &Image<T>::fill(T value) {
  if (impl_) {
    impl_->fill(value);
  }
  return *this;
}

template <typename T> Image<T> Image<T>::get_crop(int x0, int y0, int x1, int y1) const {
  return Image<T>(impl_->get_crop(x0, y0, x1, y1));
}

// Resizing

template <typename T> Image<T> &Image<T>::resize(int x, int y) {
  impl_->resize(x, y);
  return *this;
}

template <typename T> Image<T> &Image<T>::resize(const CImg<T> &img) {
  impl_->resize(img);
  return *this;
}

template <typename T> Image<T> &Image<T>::resize(const Display &disp) {
  impl_->resize(*disp.internal());
  return *this;
}

// Transformations

template <typename T>
Image<T> &Image<T>::rotate(float angle, int interpolation, int boundary_conditions) {
  impl_->rotate(angle, interpolation, boundary_conditions);
  return *this;
}

template <typename T> Image<T> &Image<T>::channels(int c0, int c1) {
  impl_->channels(c0, c1);
  return *this;
}

template <typename T> Image<T> Image<T>::get_shared_channel(int channel) const {
  return Image<T>(impl_->get_shared_channel(channel));
}

// Drawing

template <typename T>
Image<T> &Image<T>::draw_line(int x0, int y0, int x1, int y1, const T *color, float opacity) {
  impl_->draw_line(x0, y0, x1, y1, color, opacity);
  return *this;
}

template <typename T>
Image<T> &Image<T>::draw_circle(int x, int y, int radius, const T *color, float opacity) {
  impl_->draw_circle(x, y, radius, color, opacity);
  return *this;
}

template <typename T>
Image<T> &Image<T>::draw_rectangle(int x0, int y0, int x1, int y1, const T *color, float opacity) {
  impl_->draw_rectangle(x0, y0, x1, y1, color, opacity);
  return *this;
}

template <typename T>
Image<T> &Image<T>::draw_polygon(const CImg<int> &points, const T *color, float opacity) {
  impl_->draw_polygon(points, color, opacity);
  return *this;
}

template <typename T>
Image<T> &Image<T>::draw_image(int x, int y, const CImg<T> &img, float opacity) {
  impl_->draw_image(x, y, img, opacity);
  return *this;
}

template <typename T>
Image<T> &Image<T>::draw_image(int x, int y, const Image<T> &img, float opacity) {
  return draw_image(x, y, *img.impl_, opacity);
}

template <typename T>
Image<T> &Image<T>::draw_image(
    int x, int y, const Image<T> &img, const Image<T> &mask, int channel, float opacity) {
  impl_->draw_image(x, y, *img.impl_, *mask.impl_, channel, opacity);
  return *this;
}

template <typename T>
Image<T> &Image<T>::draw_triangle(int x0,
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
                                  float opacity,
                                  float brightness) {
  impl_->draw_triangle(
      x0, y0, x1, y1, x2, y2, texture, tx0, ty0, tx1, ty1, tx2, ty2, opacity, brightness);
  return *this;
}

// Saving

template <typename T> Image<T> &Image<T>::save(const char *filename) const {
  impl_->save(filename);
  return const_cast<Image<T> &>(*this);
}

template <typename T> Image<T> &Image<T>::save(const std::string &filename) const {
  return save(filename.c_str());
}

unsigned int toCImgKey(KeyboardKey key) {
  using namespace cimg_library::cimg;

  switch (key) {
  case KEY_ESC:
    return keyESC;
  case KEY_F1:
    return keyF1;
  case KEY_F2:
    return keyF2;
  case KEY_F3:
    return keyF3;
  case KEY_F4:
    return keyF4;
  case KEY_F5:
    return keyF5;
  case KEY_F6:
    return keyF6;
  case KEY_F7:
    return keyF7;
  case KEY_F8:
    return keyF8;
  case KEY_F9:
    return keyF9;
  case KEY_F10:
    return keyF10;
  case KEY_F11:
    return keyF11;
  case KEY_F12:
    return keyF12;
  case KEY_PAUSE:
    return keyPAUSE;
  case KEY_1:
    return key1;
  case KEY_2:
    return key2;
  case KEY_3:
    return key3;
  case KEY_4:
    return key4;
  case KEY_5:
    return key5;
  case KEY_6:
    return key6;
  case KEY_7:
    return key7;
  case KEY_8:
    return key8;
  case KEY_9:
    return key9;
  case KEY_0:
    return key0;
  case KEY_BACKSPACE:
    return keyBACKSPACE;
  case KEY_INSERT:
    return keyINSERT;
  case KEY_HOME:
    return keyHOME;
  case KEY_PAGEUP:
    return keyPAGEUP;
  case KEY_TAB:
    return keyTAB;
  case KEY_Q:
    return keyQ;
  case KEY_W:
    return keyW;
  case KEY_E:
    return keyE;
  case KEY_R:
    return keyR;
  case KEY_T:
    return keyT;
  case KEY_Y:
    return keyY;
  case KEY_U:
    return keyU;
  case KEY_I:
    return keyI;
  case KEY_O:
    return keyO;
  case KEY_P:
    return keyP;
  case KEY_DELETE:
    return keyDELETE;
  case KEY_END:
    return keyEND;
  case KEY_PAGEDOWN:
    return keyPAGEDOWN;
  case KEY_CAPSLOCK:
    return keyCAPSLOCK;
  case KEY_A:
    return keyA;
  case KEY_S:
    return keyS;
  case KEY_D:
    return keyD;
  case KEY_F:
    return keyF;
  case KEY_G:
    return keyG;
  case KEY_H:
    return keyH;
  case KEY_J:
    return keyJ;
  case KEY_K:
    return keyK;
  case KEY_L:
    return keyL;
  case KEY_ENTER:
    return keyENTER;
  case KEY_SHIFTLEFT:
    return keySHIFTLEFT;
  case KEY_Z:
    return keyZ;
  case KEY_X:
    return keyX;
  case KEY_C:
    return keyC;
  case KEY_V:
    return keyV;
  case KEY_B:
    return keyB;
  case KEY_N:
    return keyN;
  case KEY_M:
    return keyM;
  case KEY_SHIFTRIGHT:
    return keySHIFTRIGHT;
  case KEY_ARROWUP:
    return keyARROWUP;
  case KEY_CTRLLEFT:
    return keyCTRLLEFT;
  case KEY_APPLEFT:
    return keyAPPLEFT;
  case KEY_ALT:
    return keyALT;
  case KEY_SPACE:
    return keySPACE;
  case KEY_ALTGR:
    return keyALTGR;
  case KEY_APPRIGHT:
    return keyAPPRIGHT;
  case KEY_MENU:
    return keyMENU;
  case KEY_CTRLRIGHT:
    return keyCTRLRIGHT;
  case KEY_ARROWLEFT:
    return keyARROWLEFT;
  case KEY_ARROWDOWN:
    return keyARROWDOWN;
  case KEY_ARROWRIGHT:
    return keyARROWRIGHT;
  case KEY_PAD0:
    return keyPAD0;
  case KEY_PAD1:
    return keyPAD1;
  case KEY_PAD2:
    return keyPAD2;
  case KEY_PAD3:
    return keyPAD3;
  case KEY_PAD4:
    return keyPAD4;
  case KEY_PAD5:
    return keyPAD5;
  case KEY_PAD6:
    return keyPAD6;
  case KEY_PAD7:
    return keyPAD7;
  case KEY_PAD8:
    return keyPAD8;
  case KEY_PAD9:
    return keyPAD9;
  case KEY_PADADD:
    return keyPADADD;
  case KEY_PADSUB:
    return keyPADSUB;
  case KEY_PADMUL:
    return keyPADMUL;
  case KEY_PADDIV:
    return keyPADDIV;
  }

  return 0;
}

template class Image<uint8_t>;
template class Image<int>;
} // namespace cturtle
