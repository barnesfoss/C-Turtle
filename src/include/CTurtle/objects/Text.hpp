// Copyright 2021 Jesse W. Walker
//
// Licensed under the MIT License.
// See LICENSE for details.
#ifndef CTURTLE_OBJECTS_TEXT_HPP
#define CTURTLE_OBJECTS_TEXT_HPP
#include <string>

#include "AbstractDrawableObject.hpp"
#include "CTurtle/font/BitmapFont.hpp"
#include "CTurtle/font/TextAlign.hpp"
#include "types/Color.hpp"

namespace cturtle {
class BitmapFont;

/**\brief The Text class represents a basic string that is drawn on the screen.
 */
class Text : public AbstractDrawableObject {
public:
  /** The text to draw.*/
  const std::string text;
  const BitmapFont &font;
  TextAlign alignment;
  float scale;

  Text(std::string text,
       const BitmapFont &font,
       const Color &color,
       float scale = 1.0f,
       TextAlign alignment = TEXT_ALIGN_LEFT);

  Text(const Text &copy) = default;

  AbstractDrawableObject *copy() const override;

  void draw(const Transform &t, Image<> &imgRef) const override;

  ~Text() override = default;
};
} // namespace cturtle
#endif
