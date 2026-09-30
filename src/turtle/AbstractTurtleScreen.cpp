#include "CTurtle/turtle/AbstractTurtleScreen.hpp"
#include "CTurtle/font.hpp"
namespace cturtle {
void AbstractTurtleScreen::clear() { clearscreen(); }
void AbstractTurtleScreen::reset() { resetscreen(); }
Image AbstractTurtleScreen::decodeDefaultFont() {
  Image img(DEFAULT_FONT_PIXELS_WIDTH, DEFAULT_FONT_PIXELS_HEIGHT);
  img.channels(0, 3); // force RGBA
  for (uint32_t pixId = 0; pixId < DEFAULT_FONT_PIXELS_LEN; pixId++) {
    const unsigned int decodeVal = DEFAULT_FONT_PIXELS[pixId];
    // 8 integers per row of pixels (8*32=256)
    const int pixY = pixId / 8;
    const int pixOffsX =
        (pixId % 8) * 32; // offset of every pixel for the current integer.

    for (int i = 0; i < 32; i++) { // for every bit in the unsigned integer...
      const int pixX =
          pixOffsX + (31 - i); // 31 due to number of bits in unsigned int...
      // get i'th pixel in the integer by bitmask and multiply
      const uint8_t pixel = ((decodeVal >> i) & 1) * 255;
      for (int c = 0; c < 4; c++)
        img(pixX, pixY, 0, c) = pixel;
    }
  }
  return img;
}
} // namespace cturtle
