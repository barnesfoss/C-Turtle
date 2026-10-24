#pragma once
#include "CTurtle/geometry/ivec2.hpp"
#include "CTurtle/types/Image.hpp"

namespace cturtle {
class AbstractFont {
public:
  /**
   * Returns the appropriate image for the specified character.
   * \param c character to retrieve the associated image for.
   */
  virtual const Image &getGlyphImage(unsigned char c) const = 0;

  /**
   * Returns the appropriate image for the specified character.
   * \param c character to retrieve the associated image for.
   */
  virtual const Image &operator[](unsigned char c) const = 0;

  /**
   * \brief Returns the position of the specified character in the font image.
   * @param c character to get the position of
   * @return position of the character.
   */
  virtual ivec2 getGlyphPosition(unsigned char c) const = 0;

  /**
   * \brief Returns the size of a single character glyph, in pixels.
   * @return the width (x) and height (y) of the glyph, in pixels.
   */
  virtual ivec2 getGlyphExtent() const = 0;

  /**
   * @return the total number of valid glyphs in this bitmap font.
   */
  virtual int getTotalGlyphs() const = 0;

  /**
   * @return a boolean indicating if the specified character is valid within
   * this bitmap font.
   */
  virtual bool isValid(char c) const = 0;

  /**
   * \brief Returns the number of glyphs along each axis of the underlying
   * image.
   * @return the number of glyphs along each axis of the underlying image.
   */
  virtual ivec2 getGlyphAxes() const = 0;
};
} // namespace cturtle
