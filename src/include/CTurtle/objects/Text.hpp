#pragma once
#include "AbstractDrawableObject.hpp"
#include "CTurtle/font/BitmapFont.hpp"
#include "CTurtle/font/TextAlign.hpp"

namespace cturtle {
/**\brief The Text class represents a basic string that is drawn on the screen.
 */
class Text : public AbstractDrawableObject {
public:
  /** The text to draw.*/
  const std::string text;
  const BitmapFont &font;
  TextAlign alignment;
  float scale;

  Text(std::string text, const BitmapFont &font, const Color &color,
       float scale = 1.0f, TextAlign alignment = TEXT_ALIGN_LEFT);

  Text(const Text &copy) = default;

  AbstractDrawableObject *copy() const override;

  void draw(const Transform &t, Image &imgRef) const override;

  ~Text() override = default;
};
} // namespace cturtle
