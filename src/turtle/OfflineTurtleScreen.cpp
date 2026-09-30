// Copyright 2021 Jesse W. Walker
//
// Licensed under the MIT License.
// See LICENSE for details.
#ifdef CTURTLE_HEADLESS
#include "CTurtle/turtle/OfflineTurtleScreen.hpp"

#include <fstream>
#include <iostream>

#include "CTurtle.hpp"
#include "CTurtle/util/base64.hpp"
#include "CTurtle/util/headless.hpp"
// Automatic linking when operating under MSVC
// If linking errors occur when compiling on Non-MSVC,
// Make sure you link X11 and PThread when using Unix-Like environments, when
// NOT using headless mode.
#ifndef CTURTLE_MSVC_NO_AUTOLINK
#ifdef _MSC_VER
/*Automatically link to the necessary windows libraries while under MSVC.*/
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "gdi32.lib")
#endif
#endif

// MSVC 2017 doesn't seem to like defining M_PI. We define it ourselves
// when compiling under VisualC++.
#ifdef _MSC_VER
#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif
// Disable MSVC warnings for CImg. Irrelevant to project.
#include <CodeAnalysis/Warnings.h>
#pragma warning(push, 0)
#pragma warning(disable : ALL_CODE_ANALYSIS_WARNINGS)
#include "CImg.h"
#pragma warning(pop)
#endif

namespace cturtle {
/*Used to output Base-64 GIF and HTML source for OfflineTurtleScreen.*/
std::string encodeFileBase64(const std::string& path) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<unsigned char> buffer(size, 0);
    file.read(reinterpret_cast<char*>(buffer.data()), size);
    return base64::encode(buffer);
}

void OfflineTurtleScreen::redraw(bool invalidate) {
    if (isclosed()) return;
    int fromBack = 0;
    bool hasInvalidated = invalidate;

    // Handle resizes.

    if (lastTotalObjects <= objects.size()) {
        fromBack = static_cast<int>(objects.size() - lastTotalObjects);
    }

    if (hasInvalidated) {
        canvas.draw_rectangle(0, 0, canvas.width(), canvas.height(),
                              backgroundColor.rgbPtr());
        redrawCounter = 0;  // Forced redraw due to canvas invalidation.
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

    auto latestIter =
        !hasInvalidated ? std::prev(objects.end(), fromBack) : objects.begin();

    Transform screen = screentransform();
    while (latestIter != objects.end()) {
        SceneObject& object = *latestIter;
        const Transform t(screen.copyConcatenate(object.transform));

        object.geom->draw(t, canvas);

        latestIter++;
    }

    if (canvas.width() != turtleComposite.width() ||
        canvas.height() != turtleComposite.height()) {
        turtleComposite.assign(canvas);
    } else {
        // This works off the assumption that drawImage is accelerated.
        // There might be a more efficient way to do this, however.
        turtleComposite.draw_image(0, 0, canvas);
    }

    for (Turtle* turt : turtles) turt->draw(screen, turtleComposite);

    lastTotalObjects = static_cast<int>(objects.size());

    /* The following code takes the place of swapping the display buffer for the
     * canvas, which is what the interactive mode does.*/

    // This copy is NOT efficient.
    // We should be able to take advantage of loop unrolling here
    for (int x = 0; x < CTURTLE_HEADLESS_WIDTH; x++) {
        for (int y = 0; y < CTURTLE_HEADLESS_HEIGHT; y++) {
            uint8_t* pixel =
                (&gifWriteBuffer[(y * CTURTLE_HEADLESS_WIDTH + x) * 4]);

            pixel[0] = turtleComposite(x, y, 0);
            pixel[1] = turtleComposite(x, y, 1);
            pixel[2] = turtleComposite(x, y, 2);
            pixel[3] = 255;
        }
    }

    // GIF frames are measured in centiseconds, thus the /10 on the delayMS...
    jo_gif_frame(&gif, gifWriteBuffer, delayMS / 10, true);
}

OfflineTurtleScreen::OfflineTurtleScreen() {
    const int width = CTURTLE_HEADLESS_WIDTH;
    const int height = CTURTLE_HEADLESS_HEIGHT;
    canvas.assign(width, height, 1, 3);
    canvas.fill(255);
    isClosed = false;
    gif = jo_gif_start(CTURTLE_HEADLESS_SAVEDIR, width, height, 1, 31);
    redraw(true);
}

OfflineTurtleScreen::~OfflineTurtleScreen() { bye(); }

void OfflineTurtleScreen::tracer(int countmax, unsigned int delayMS) {
    redrawCounterMax = countmax;
    delay(delayMS);
    redraw();
}

void OfflineTurtleScreen::update(bool invalidateDraw, bool processInput) {
    redraw(invalidateDraw);
    // processInput is ignored. OfflineTurtleScreen does NOT support input.
}

int OfflineTurtleScreen::window_width() const { return canvas.width(); }

int OfflineTurtleScreen::window_height() const { return canvas.height(); }

Color OfflineTurtleScreen::bgcolor() const { return backgroundColor; }

void OfflineTurtleScreen::bgcolor(const Color& c) {
    backgroundColor = c;
    redraw(true);
}

void OfflineTurtleScreen::mode(ScreenMode mode) {
    // Resets & re-orients all turtles.

    curMode = mode;
    for (Turtle* t : turtles) {
        t->reset();
    }
}

ScreenMode OfflineTurtleScreen::mode() const { return curMode; }

void OfflineTurtleScreen::clearscreen() {
    // 1) Delete all drawings and turtles
    // 2) White background

    for (Turtle* turtle : turtles) {
        turtle->setScreen(nullptr);
    }

    turtles.clear();
    backgroundColor = Color("white");
    curMode = SM_STANDARD;
}

void OfflineTurtleScreen::resetscreen() {
    for (Turtle* turtle : turtles) turtle->reset();
}

ivec2 OfflineTurtleScreen::screensize(Color& bg) {
    bg = backgroundColor;
    return {canvas.width(), canvas.height()};
};
// code-smell from python->c++, considering separation of functionality

ivec2 OfflineTurtleScreen::screensize() {
    return {canvas.width(), canvas.height()};
}

Image& OfflineTurtleScreen::getcanvas() { return canvas; }

bool OfflineTurtleScreen::isclosed() { return isClosed; }

bool OfflineTurtleScreen::supports_live_animation() const { return false; }

void OfflineTurtleScreen::delay(unsigned int ms) { delayMS = ms; }

unsigned int OfflineTurtleScreen::delay() const { return delayMS; }

void OfflineTurtleScreen::bye() {
    if (isClosed) return;

    /*finish up drawing if redraw counter hasn't been met*/
    if (redrawCounter > 0 || redrawCounter >= redrawCounterMax) {
        tracer(1, delayMS);
    }

    jo_gif_end(&gif);

#ifndef CTURTLE_HEADLESS_NO_HTML
    /*print base-64 encoding + HTML source*/
    std::string imgCode = encodeFileBase64(CTURTLE_HEADLESS_SAVEDIR);

    // See the following to understand why this was done:
    // https://github.com/ericsonga/APCSAReview/blob/master/_sources/TurtleGraphics/turtleBasics.rst
    // HTML can be captured for later output.
    std::cout << "<img src=\'data:image/gif;base64,";
    std::cout << imgCode;
    std::cout << "\'/>";
#endif

    clearscreen();
    isClosed = true;
}
Transform OfflineTurtleScreen::screentransform() const {
    return Transform()
        .translate(canvas.width() / 2, canvas.height() / 2)
        .scale(1, -1.0f);
}

void OfflineTurtleScreen::add(Turtle& turtle) { turtles.push_back(&turtle); }

void OfflineTurtleScreen::remove(Turtle& turtle) {
    turtle.reset();
    turtle.setScreen(nullptr);
    turtles.remove(&turtle);
}

std::list<SceneObject>& OfflineTurtleScreen::getScene() { return objects; }

AbstractDrawableObject& OfflineTurtleScreen::shape(const std::string& name) {
    return shapes[name];
}

/**
 * Returns a read-only reference to the bitmap font with the specified name.
 * For the case of OfflineTurtleScreen instances, this ALWAYS returns a
 * reference to the default font.
 * @param name to be given to the font. Irrelevant for the offline turtle
 * screen.
 * @return read-only BitmapFont reference to the default font.
 */
const BitmapFont& OfflineTurtleScreen::font(const std::string& name) const {
    return *defaultFont;
}

}  // namespace cturtle
#endif
