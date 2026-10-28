// Copyright 2021 Jesse W. Walker
//
// Licensed under the MIT License.
// See LICENSE for details.
#include "turtle/HeadlessTurtleScreen.hpp"

extern "C" {
#include "getarg.h"
#include "gif_lib.h"
}
#include "turtle/Turtle.hpp"
#include "util/base64.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>

namespace cturtle {
/*Used to output Base-64 GIF and HTML source for HeadlessTurtleScreen.*/
std::string encodeFileBase64(const std::string &path) {
  std::ifstream file(path, std::ios::binary | std::ios::ate);
  std::streamsize size = file.tellg();
  file.seekg(0, std::ios::beg);

  if (!file.is_open()) {
    throw std::runtime_error("Failed to open file: " + path);
  }

  std::vector<unsigned char> buffer(size, 0);
  file.read(reinterpret_cast<char *>(buffer.data()), size);
  return base64::encode(buffer);
}

void HeadlessTurtleScreen::redraw(bool invalidate) {
  if (isclosed())
    return;
  int fromBack = 0;
  bool hasInvalidated = invalidate;

  // Handle resizes.

  if (lastTotalObjects <= objects.size()) {
    fromBack = static_cast<int>(objects.size() - lastTotalObjects);
  }

  if (hasInvalidated) {
    canvas.draw_rectangle(0, 0, canvas.width(), canvas.height(), backgroundColor.rgbPtr());
    redrawCounter = 0; // Forced redraw due to canvas invalidation.
  } else {
    if (redrawCounterMax == 0) {
      return;
    }

    redrawCounter++;

    if (redrawCounter >= redrawCounterMax) {
      redrawCounter = 0;
    } else {
      return;
    }
  }

  auto latestIter = !hasInvalidated ? std::prev(objects.end(), fromBack) : objects.begin();

  Transform screen = screentransform();
  while (latestIter != objects.end()) {
    SceneObject &object = *latestIter;
    const Transform t(screen.copyConcatenate(object.transform));

    object.geom->draw(t, canvas);

    latestIter++;
  }

  if (canvas.width() != turtleComposite.width() || canvas.height() != turtleComposite.height()) {
    turtleComposite.assign(canvas);
  } else {
    // This works off the assumption that drawImage is accelerated.
    // There might be a more efficient way to do this, however.
    turtleComposite.draw_image(0, 0, canvas);
  }

  for (Turtle *turt : turtles)
    turt->draw(screen, turtleComposite);

  lastTotalObjects = static_cast<int>(objects.size());

  /* The following code takes the place of swapping the display buffer for the
   * canvas, which is what the interactive mode does.*/

  // This copy is NOT efficient.
  // We should be able to take advantage of loop unrolling here
  for (size_t x = 0; x < width; x++) {
    for (size_t y = 0; y < height; y++) {
      uint8_t *pixel = (&gifWriteBuffer[(y * width + x) * 4]);

      pixel[0] = turtleComposite(x, y, 0);
      pixel[1] = turtleComposite(x, y, 1);
      pixel[2] = turtleComposite(x, y, 2);
      pixel[3] = 255;
    }
  }

  // Generate a color pallete for the frame using quantization
  const size_t pixelCount = width * height;

  std::vector<GifByteType> red(pixelCount);
  std::vector<GifByteType> green(pixelCount);
  std::vector<GifByteType> blue(pixelCount);
  std::vector<GifPixelType> indexed(pixelCount);

  // Write colors to the GifByteType vectors so we can quantize them using GifQuantizeBuffer
  for (size_t i = 0; i < pixelCount; ++i) {
    const uint8_t *pixel = &gifWriteBuffer[i * 4];
    red[i] = pixel[0];
    green[i] = pixel[1];
    blue[i] = pixel[2];
  }
  GifColorType palette[256];

  // Maybe add an argument for this in the future, need to ensure it's a power of two,
  // could possibly take an integer between 1-9 and to get a colorCount number
  int colorCount = 256;

  // Quantize image pixels into a 256 color color palette
  if (GifQuantizeBuffer(width,
                        height,
                        &colorCount,
                        red.data(),
                        green.data(),
                        blue.data(),
                        indexed.data(),
                        palette) == GIF_ERROR) {
    throw std::runtime_error("GifQuantizeBuffer failed");
  }

  // Calculate the mapSize, giflib requires this to be a power of 2
  int mapSize = 2;
  while (mapSize < colorCount) {
    mapSize *= 2;
  }

  ColorMapObject *localMap = GifMakeMapObject(mapSize, palette);
  if (!localMap) {
    throw std::runtime_error("GifMakeMapObject failed");
  }

  // GIF frames are measured in centiseconds, thus the /10 on the delayMS
  const int delayCS = delayMS / 10;

  // Write the Graphics extension for GIF frame delay
  // Label 21 F9
  // ArgSize 04
  // Bitflags 00
  // DelayTime delayLower, delayUpper
  // Transparent 0
  GifByteType ext[] = {
      0, static_cast<uint8_t>(delayCS & 0xFF), static_cast<uint8_t>((delayCS >> 8) & 0xFF), 0};
  if (EGifPutExtension(gif, GRAPHICS_EXT_FUNC_CODE, 4, ext) == GIF_ERROR) {
    GifFreeMapObject(localMap);
    throw std::runtime_error("Failed to write GIF extension");
  }

  if (EGifPutImageDesc(gif, 0, 0, width, height, false, localMap) == GIF_ERROR) {
    GifFreeMapObject(localMap);
    throw std::runtime_error("Failed to write GIF image descriptor");
  }

  GifFreeMapObject(localMap);

  for (size_t y = 0; y < height; ++y) {
    if (EGifPutLine(gif, indexed.data() + y * width, width) == GIF_ERROR) {
      throw std::runtime_error("Failed to write GIF pixels");
    }
  }
}

HeadlessTurtleScreen::HeadlessTurtleScreen(size_t width, size_t height, const std::string saveDir)
    : width(width), height(height), saveDir(saveDir.c_str()) {
  gifWriteBuffer = new uint8_t[width * height * 4];
  canvas.assign(width, height, 1, 3);
  canvas.fill(255);
  isClosed = false;

  // Make the initial gif object
  gif = EGifOpenFileName(saveDir.c_str(), false, &gifError);

  if (!gif) {
    std::cout << "EGifOpenFileName() failed - " << gifError << std::endl;
  }

  // Write a descriptor for the GIF w, h, resolution, bgcolor
  if (EGifPutScreenDesc(gif, width, height, 8, 0, nullptr) == GIF_ERROR) {
    throw std::runtime_error("EGifPutScreenDesc failed");
  }

  redraw(true);
}

HeadlessTurtleScreen::~HeadlessTurtleScreen() {
  delete gifWriteBuffer;
  bye();
}

void HeadlessTurtleScreen::tracer(int countmax, unsigned int delayMS) {
  redrawCounterMax = countmax;
  delay(delayMS);
  redraw();
}

void HeadlessTurtleScreen::update(bool invalidateDraw, bool processInput) {
  redraw(invalidateDraw);
  // processInput is ignored. HeadlessTurtleScreen does NOT support input.
}

int HeadlessTurtleScreen::window_width() const {
  return canvas.width();
}

int HeadlessTurtleScreen::window_height() const {
  return canvas.height();
}

Color HeadlessTurtleScreen::bgcolor() const {
  return backgroundColor;
}

void HeadlessTurtleScreen::bgcolor(const Color &c) {
  backgroundColor = c;
  redraw(true);
}

void HeadlessTurtleScreen::mode(ScreenMode mode) {
  // Resets & re-orients all turtles.

  curMode = mode;
  for (Turtle *t : turtles) {
    t->reset();
  }
}

ScreenMode HeadlessTurtleScreen::mode() const {
  return curMode;
}

void HeadlessTurtleScreen::clearscreen() {
  // 1) Delete all drawings and turtles
  // 2) White background

  for (Turtle *turtle : turtles) {
    turtle->setScreen(nullptr);
  }

  turtles.clear();
  backgroundColor = Color("white");
  curMode = SM_STANDARD;
}

void HeadlessTurtleScreen::resetscreen() {
  for (Turtle *turtle : turtles)
    turtle->reset();
}

ivec2 HeadlessTurtleScreen::screensize(Color &bg) {
  bg = backgroundColor;
  return {canvas.width(), canvas.height()};
};

// code-smell from python->c++, considering separation of functionality

ivec2 HeadlessTurtleScreen::screensize() {
  return {canvas.width(), canvas.height()};
}

Image<> &HeadlessTurtleScreen::getcanvas() {
  return canvas;
}

bool HeadlessTurtleScreen::isclosed() {
  return isClosed;
}

bool HeadlessTurtleScreen::supports_live_animation() const {
  return false;
}

void HeadlessTurtleScreen::delay(unsigned int ms) {
  delayMS = ms;
}

unsigned int HeadlessTurtleScreen::delay() const {
  return delayMS;
}

void HeadlessTurtleScreen::bye(bool printHtml) {
  if (isClosed)
    return;

  /*finish up drawing if redraw counter hasn't been met*/
  if (redrawCounter > 0 || redrawCounter >= redrawCounterMax) {
    tracer(1, delayMS);
  }

  // Close & Write the GIF to the output directory
  if (EGifCloseFile(gif, &gifError) == GIF_ERROR) {
    std::cerr << "Failed to close GIF: " << gifError << '\n';
  }

  if (printHtml) {
    /*print base-64 encoding + HTML source*/
    std::string imgCode = encodeFileBase64(saveDir);

    // See the following to understand why this was done:
    // https://github.com/ericsonga/APCSAReview/blob/master/_sources/TurtleGraphics/turtleBasics.rst
    // HTML can be captured for later output.
    std::cout << "<img src=\'data:image/gif;base64,";
    std::cout << imgCode;
    std::cout << "\'/>";
  }
  clearscreen();
  isClosed = true;
}

Transform HeadlessTurtleScreen::screentransform() const {
  return Transform().translate(canvas.width() / 2, canvas.height() / 2).scale(1, -1.0f);
}

void HeadlessTurtleScreen::add(Turtle &turtle) {
  turtles.push_back(&turtle);
}

void HeadlessTurtleScreen::remove(Turtle &turtle) {
  turtle.reset();
  turtle.setScreen(nullptr);
  turtles.remove(&turtle);
}

std::list<SceneObject> &HeadlessTurtleScreen::getScene() {
  return objects;
}

AbstractDrawableObject &HeadlessTurtleScreen::shape(const std::string &name) {
  return shapes[name];
}

/**
 * Returns a read-only reference to the bitmap font with the specified name.
 * For the case of HeadlessTurtleScreen instances, this ALWAYS returns a
 * reference to the default font.
 * @param name to be given to the font. Irrelevant for the offline turtle
 * screen.
 * @return read-only BitmapFont reference to the default font.
 */
const BitmapFont &HeadlessTurtleScreen::font(const std::string &name) const {
  return *defaultFont;
}
} // namespace cturtle
