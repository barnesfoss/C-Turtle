#include <string>
#ifndef CTURTLE_TYPES_ABSTRACTDISPLAY_HPP
#define CTURTLE_TYPES_ABSTRACTDISPLAY_HPP

namespace cturtle {
// Base class for a Display, based on the display provided by cimg and what functions we use from it
class AbstractDisplay {
public:
  virtual bool should_close() = 0;

  virtual void set_title(const std::string &title) = 0;

  virtual int width() const = 0;

  virtual int height() const = 0;

  virtual int window_width() const = 0;

  virtual int window_height() const = 0;

  virtual bool is_resized() = 0;

  virtual void resize(bool force_redraw = true) = 0;

  virtual bool is_closed() = 0;

  virtual void close() = 0;

  virtual int mouse_x() = 0;

  virtual int mouse_y() = 0;

  virtual unsigned int button() const = 0;

  virtual bool is_event() const = 0;

  virtual bool is_key(unsigned int key) const = 0;

  virtual void set_normalization(int amt) = 0;
};
} // namespace cturtle
#endif
