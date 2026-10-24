// Copyright 2021 Jesse W. Walker
//
// Licensed under the MIT License.
// See LICENSE for details.
#pragma once
#include "CTurtle/font/AbstractFont.hpp"
#include "CTurtle/geometry/ivec2.hpp"
#include "CTurtle/types/Image.hpp"

#include <vector>

namespace cturtle {
/**
 * \brief The Bitmap Font represents monospaced font image files that covers a
 * range of lower ASCII. The default font, for example, covers 32-127 (e.g, char
 * 32 to char 127). This is a particularly naive implementation of bitmap fonts,
 * however, all basic properties required are here.
 */
class BitmapFont : public AbstractFont {
public:
  /**
   * Bitmap Font constructor.
   * @param asciiOffs
   * @param glyphWidth
   * @param glyphHeight
   * @param glyphsX
   * @param glyphsY
   */
  BitmapFont(
      const Image &img, int asciiOffs, int glyphWidth, int glyphHeight, int glyphsX, int glyphsY);

  const Image &getGlyphImage(unsigned char c) const override;

  const Image &operator[](unsigned char c) const override;

  ivec2 getGlyphPosition(unsigned char c) const override;

  ivec2 getGlyphExtent() const override;

  int getTotalGlyphs() const override;

  bool isValid(char c) const override;

  ivec2 getGlyphAxes() const override;

private:
  std::vector<Image> glyphs;
  int asciiOffset, glyphWidth, glyphHeight, glyphsX, glyphsY;
};
} // namespace cturtle
