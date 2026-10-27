#include "CImg.h"
#include "types/AbstractDisplay.hpp"
#include "types/DisplayCImg.hpp"
#include "types/Image.hpp"
#include "util/io.hpp"

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

Image::Image() : impl_(new CImg<uint8_t>()) {}

Image::Image(const int size_x, const int size_y, const int size_z, const int size_c)
    : impl_(new CImg<uint8_t>(size_x, size_y, size_z, size_c)) {}

Image::Image(const CImg<uint8_t> &img) : impl_(new CImg<uint8_t>(img)) {}

Image::Image(const Image &other) : impl_(new CImg<uint8_t>(*other.impl_)) {}

Image::Image(Image &&other) noexcept : impl_(std::exchange(other.impl_, nullptr)) {}

Image &Image::operator=(const Image &other) {
  if (this != &other) {
    *impl_ = *other.impl_;
  }
  return *this;
}

Image &Image::operator=(Image &&other) noexcept {
  if (this != &other) {
    delete impl_;
    impl_ = std::exchange(other.impl_, nullptr);
  }
  return *this;
}

uint8_t &Image::operator()(int x, int y, int z, int c) {
  return (*impl_)(x, y, z, c);
};

const uint8_t &Image::operator()(int x, int y, int z, int c) const {
  return (*impl_)(x, y, z, c);
};

Image::~Image() {
  delete impl_;
}

Image::operator CImg<uint8_t> &() {
  return *impl_;
}

Image::operator const CImg<uint8_t> &() const {
  return *impl_;
}

int Image::width() const {
  return impl_->width();
}

int Image::height() const {
  return impl_->height();
}

int Image::depth() const {
  return impl_->depth();
}

int Image::spectrum() const {
  return impl_->spectrum();
}

bool Image::is_empty() const {
  return impl_->is_empty();
}

Image &Image::assign() {
  impl_->assign();
  return *this;
}

Image &Image::assign(int x, int y, int z, int c) {
  impl_->assign(x, y, z, c);
  return *this;
}

Image &Image::assign(const Image &img) {
  *impl_ = *img.impl_;
  return *this;
}

Image &Image::fill(uint8_t value) {
  impl_->fill(value);
  return *this;
}

Image &Image::assign(const Display &disp) {
  impl_->assign(*disp.internal());
  return *this;
}

Image Image::get_crop(int x0, int y0, int x1, int y1) const {
  return Image(impl_->get_crop(x0, y0, x1, y1));
}

Image &Image::resize(int x, int y) {
  impl_->resize(x, y);
  return *this;
}

Image &Image::resize(const CImg<uint8_t> &img) {
  impl_->resize(img);
  return *this;
}

Image &Image::resize(const Display &disp) {
  impl_->resize(*disp.internal());
  return *this;
}

Image &Image::rotate(float angle, int interpolation, int boundary_conditions) {
  impl_->rotate(angle, interpolation, boundary_conditions);
  return *this;
}

Image &Image::channels(int c0, int c1) {
  impl_->channels(c0, c1);
  return *this;
}

Image Image::get_shared_channel(int channel) const {
  return Image(impl_->get_shared_channel(channel));
}

Image &Image::draw_line(int x0, int y0, int x1, int y1, const uint8_t *color, float opacity) {
  impl_->draw_line(x0, y0, x1, y1, color, opacity);
  return *this;
}

Image &Image::draw_circle(int x, int y, int radius, const uint8_t *color, float opacity) {
  impl_->draw_circle(x, y, radius, color, opacity);
  return *this;
}

Image &Image::draw_rectangle(int x0, int y0, int x1, int y1, const uint8_t *color, float opacity) {
  impl_->draw_rectangle(x0, y0, x1, y1, color, opacity);
  return *this;
}

Image &Image::draw_polygon(const CImg<uint8_t> &points, const uint8_t *color, float opacity) {
  impl_->draw_polygon(points, color, opacity);
  return *this;
}

Image &Image::draw_image(int x, int y, const CImg<uint8_t> &img, float opacity) {
  impl_->draw_image(x, y, img, opacity);
  return *this;
}

Image &Image::draw_image(int x, int y, const Image &img, float opacity) {
  return draw_image(x, y, *img.impl_, opacity);
}

Image &Image::draw_image(
    int x, int y, const Image &img, const Image &mask, int channel, float opacity) {
  impl_->draw_image(x, y, *img.impl_, *mask.impl_, channel, opacity);

  return *this;
}

Image &Image::draw_triangle(int x0,
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
                            float opacity,
                            float brightness) {
  impl_->draw_triangle(
      x0, y0, x1, y1, x2, y2, texture, tx0, ty0, tx1, ty1, tx2, ty2, opacity, brightness);
  return *this;
}

Image &Image::save(const char *filename) const {
  impl_->save(filename);
  return const_cast<Image &>(*this);
}

Image &Image::save(const std::string &filename) const {
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
} // namespace cturtle
