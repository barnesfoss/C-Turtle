#include "CTurtle/font/BitmapFont.hpp"
#include "CTurtle/geometry/ivec2.hpp"
#include "CTurtle/types/Image.hpp"
#include <vector>
namespace cturtle {
BitmapFont::BitmapFont(const Image &img, int asciiOffs, int glyphWidth,
                       int glyphHeight, int glyphsX, int glyphsY)
    : asciiOffset(asciiOffs), glyphWidth(glyphWidth), glyphHeight(glyphHeight),
      glyphsX(glyphsX), glyphsY(glyphsY) {

  // fill the glyphs vector...
  const ivec2 glyphSz = {glyphWidth, glyphHeight};

  for (unsigned char c = static_cast<char>(asciiOffset); c < UINT8_MAX; c++) {
    const ivec2 min = getGlyphPosition(c);
    const ivec2 max = (min + glyphSz) - ivec2(1, 1);
    glyphs.push_back(img.get_crop(min.x, min.y, max.x, max.y));
  }
}

const Image &BitmapFont::getGlyphImage(unsigned char c) const {
  return glyphs.at(c - asciiOffset);
}

const Image &BitmapFont::operator[](unsigned char c) const {
  return getGlyphImage(c);
}

ivec2 BitmapFont::getGlyphPosition(unsigned char c) const {
  return {
      ((c - asciiOffset) % glyphsX) * glyphWidth,
      (static_cast<int>(std::floor(float(c - asciiOffset) / (float)glyphsX))) *
          glyphHeight};
}

ivec2 BitmapFont::getGlyphExtent() const { return {glyphWidth, glyphHeight}; }

int BitmapFont::getTotalGlyphs() const { return glyphsX * glyphsY; }

bool BitmapFont::isValid(char c) const {
  return glyphs.size() > (c - asciiOffset);
}

ivec2 BitmapFont::getGlyphAxes() const { return {glyphsX, glyphsY}; }

} // namespace cturtle
