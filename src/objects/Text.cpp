// Copyright 2021 Jesse W. Walker
//
// Licensed under the MIT License.
// See LICENSE for details.
#include "CTurtle/objects/Text.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <list>
#include <sstream>
#include <string>
#include <utility>
namespace cturtle {
Text::Text(std::string text, const BitmapFont& font, const Color& color,
           float scale, TextAlign alignment)
    : text(std::move(text)), font(font), alignment(alignment), scale(scale) {
    fillColor = color;
}

AbstractDrawableObject* Text::copy() const { return new Text(*this); }

void Text::draw(const Transform& t, Image& imgRef) const {
    // keep track of the length of the longest line of text...
    int longestLine = 0;

    // First, split the text into lines.
    std::string temp;
    std::list<std::string> textLines;
    std::stringstream ss(text);
    while (std::getline(ss, temp, '\n')) {
        longestLine = std::max(longestLine, static_cast<int>(temp.size()));
        textLines.push_back(temp);
    }

    // From there we can get some basic metrics.
    const ivec2 glyphSz = font.getGlyphExtent();  // the size of a single glyph
    const int lines = textLines.size();  // the total number of lines of text
    const int strPixLen =
        glyphSz.x *
        longestLine;  // the length, in pixels, of the longest line of text

    // Create the temporary image.
    // we double the temp image size to get a proper final rotation.
    Image textImage(strPixLen * 2, (glyphSz.y * lines) * 2);
    textImage.channels(0, 3);  // force RGBA on temp image

    int line = 0;
    // blit each character into the temporary image

    auto lineIter = textLines.begin();
    while (lineIter != textLines.end()) {
        const std::string& lineText = *lineIter;
        int textSize = static_cast<int>(lineText.size());
        // lineText alignment with some relatively simple maths.
        int hOffset = 0;

        switch (alignment) {
            case TEXT_ALIGN_LEFT:
                break;  // left align left needs no horizontal offset...
            case TEXT_ALIGN_RIGHT:
                hOffset = strPixLen - (textSize * glyphSz.x);
                break;
            case TEXT_ALIGN_CENTER:
                hOffset = (strPixLen / 2) - ((textSize * glyphSz.x) / 2);
                break;
        }

        for (int i = 0; i < textSize; i++) {
            const char curChar = lineText[i];
            if (curChar == ' ' ||
                !font.isValid(
                    curChar))  // skip space or out-of-range characters...
                continue;

            const Image& tempGlyph = font[curChar];
            const ivec2 destPosition = {strPixLen + hOffset + (i * glyphSz.x),
                                        line * glyphSz.y};
            textImage.draw_image(destPosition.x, destPosition.y, tempGlyph);

            // Apply the fill color with a multiplication filter for the size of
            // each glyph. for each pixel in the previously written glyph,
            // multiply its color...
            for (int y = destPosition.y;
                 y < destPosition.y + tempGlyph.height(); y++)
                for (int x = destPosition.x;
                     x < destPosition.x + tempGlyph.width(); x++)
                    for (int c = 0; c < 3; c++)
                        textImage(x, y, c) *=
                            (static_cast<float>(fillColor.components[c]) /
                             static_cast<float>(UINT8_MAX));
        }

        lineIter++;
        line++;
    }

    // resize image according to scale
    textImage.resize(static_cast<int>(std::round(
                         static_cast<float>(textImage.width()) * scale)),
                     static_cast<int>(std::round(
                         static_cast<float>(textImage.height()) * scale)));

    // rotate the image with nearest-neighbor interpolation
    textImage.rotate(-toDegrees(t.getRotation()), 1, 0);

    const Point translation = t.getTranslation();
    // draw the image centered
    // rotating a doubly-sized image makes the origin of the rotation
    // essentially halfway through the image therefore, to draw at the proper
    // location, we need to center it relative to the transform location.
    imgRef.draw_image(translation.x - (textImage.width() / 2),
                      translation.y - (textImage.height() / 2), textImage,
                      textImage.get_shared_channel(3), 1, 255);
}

}  // namespace cturtle
