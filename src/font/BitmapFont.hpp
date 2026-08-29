#pragma once
#include "../geometry/ivec2.hpp"
#include "../types/Image.hpp"
#include <vector>
namespace cturtle {
/**
 * \brief The Bitmap Font represents monospaced font image files that covers a
 * range of lower ASCII. The default font, for example, covers 32-127 (e.g, char
 * 32 to char 127). This is a particularly naive implementation of bitmap fonts,
 * however, all basic properties required are here.
 */
class BitmapFont {
public:
  /**
   * Bitmap Font constructor.
   * @param asciiOffs
   * @param glyphWidth
   * @param glyphHeight
   * @param glyphsX
   * @param glyphsY
   */
  BitmapFont(const Image &img, int asciiOffs, int glyphWidth, int glyphHeight,
             int glyphsX, int glyphsY)
      : asciiOffset(asciiOffs), glyphWidth(glyphWidth),
        glyphHeight(glyphHeight), glyphsX(glyphsX), glyphsY(glyphsY) {

    // fill the glyphs vector...
    const ivec2 glyphSz = {glyphWidth, glyphHeight};

    for (unsigned char c = static_cast<char>(asciiOffset); c < UINT8_MAX; c++) {
      const ivec2 min = getGlyphPosition(c);
      const ivec2 max = (min + glyphSz) - ivec2(1, 1);
      glyphs.push_back(img.get_crop(min.x, min.y, max.x, max.y));
    }
  }

  /**
   * Returns the appropriate image for the specified character.
   * \param c character to retrieve the associated image for.
   */
  const Image &getGlyphImage(unsigned char c) const {
    return glyphs.at(c - asciiOffset);
  }

  /**
   * Returns the appropriate image for the specified character.
   * \param c character to retrieve the associated image for.
   */
  inline const Image &operator[](unsigned char c) const {
    return getGlyphImage(c);
  }

  /**
   * \brief Returns the position of the specified character in the font image.
   * @param c character to get the position of
   * @return position of the character.
   */
  ivec2 getGlyphPosition(unsigned char c) const {
    return {((c - asciiOffset) % glyphsX) * glyphWidth,
            (static_cast<int>(
                std::floor(float(c - asciiOffset) / (float)glyphsX))) *
                glyphHeight};
  }

  /**
   * \brief Returns the size of a single character glyph, in pixels.
   * @return the width (x) and height (y) of the glyph, in pixels.
   */
  ivec2 getGlyphExtent() const { return {glyphWidth, glyphHeight}; }

  /**
   * @return the total number of valid glyphs in this bitmap font.
   */
  int getTotalGlyphs() const { return glyphsX * glyphsY; }

  /**
   * @return a boolean indicating if the specified character is valid within
   * this bitmap font.
   */
  bool isValid(char c) const { return glyphs.size() > (c - asciiOffset); }

  /**
   * \brief Returns the number of glyphs along each axis of the underlying
   * image.
   * @return the number of glyphs along each axis of the underlying image.
   */
  ivec2 getGlyphAxes() const { return {glyphsX, glyphsY}; }

private:
  std::vector<Image> glyphs;
  int asciiOffset, glyphWidth, glyphHeight, glyphsX, glyphsY;
};

} // namespace cturtle
