// Copyright 2021 Jesse W. Walker
//
// Licensed under the MIT License.
// See LICENSE for details.
#pragma once
#ifdef CTURTLE_HEADLESS
#include <string>

#include "CTurtle/font.hpp"
#include "CTurtle/turtle/AbstractTurtleScreen.hpp"
#include "CTurtle/util/headless.hpp"
namespace cturtle {
std::string encodeFileBase64(const std::string& path);
class OfflineTurtleScreen : public AbstractTurtleScreen {
   public:
    OfflineTurtleScreen();

    ~OfflineTurtleScreen();

    void tracer(int countmax, unsigned int delayMS = 10);

    int window_width() const;

    int window_height() const;

    Color bgcolor() const;

    void bgcolor(const Color& c);

    virtual void redraw(bool invalidate = false);

    void mode(ScreenMode mode);

    ScreenMode mode() const;

    void clearscreen();

    void resetscreen();

    ivec2 screensize(Color& bg);  // code-smell from python->c++, considering
                                  // separation of functionality

    ivec2 screensize();

    void update(bool invalidateDraw = false, bool processInput = false);

    bool supports_live_animation() const;

    Image& getcanvas();

    bool isclosed();

    void delay(unsigned int ms);

    unsigned int delay() const;

    void bye();

    Transform screentransform() const;

    void add(Turtle& turtle);

    void remove(Turtle& turtle);

    std::list<SceneObject>& getScene();

    AbstractDrawableObject& shape(const std::string& name);

    /**
     * Returns a read-only reference to the bitmap font with the specified name.
     * For the case of OfflineTurtleScreen instances, this ALWAYS returns a
     * reference to the default font.
     * @param name to be given to the font. Irrelevant for the offline turtle
     * screen.
     * @return read-only BitmapFont reference to the default font.
     */
    const BitmapFont& font(const std::string& name) const;

   private:
    /*this can be a constant allocated buffer.*/
    uint8_t
        gifWriteBuffer[CTURTLE_HEADLESS_WIDTH * CTURTLE_HEADLESS_HEIGHT * 4];
    // allocate enough to hold width*height*4 (4 because RGBA).
    // this fits into uint32_t type quite nicely. (8+8+8+8 bits, r+g+b+a) = 32

    // This struct controls the writing of resulting GIFs.
    jo_gif_t gif;

    std::list<SceneObject> objects;
    std::list<Turtle*> turtles;

    bool isClosed = true;
    Image canvas;

    // The turtle composite image.
    // This image copies the canvas and has
    // turtles drawn to it to avoid redrawing a "busy" canvas.
    // Trace lines are also drawn on this when filling.
    Image turtleComposite;

    /**The total objects on screen the last time this screen was drawn.
     * Used to keep track of newer scene objects for a speed improvement.*/
    size_t lastTotalObjects = 0;

    /**The background color of this TurtleScreen.*/
    Color backgroundColor = Color("white");

    // OfflineTurtleScreen has no background image.

    /**The current screen mode.
     *\sa mode(m)*/
    ScreenMode curMode = SM_STANDARD;

    /**Redraw delay, in milliseconds.*/
    uint32_t delayMS = 10;

    /** These variables are used specifically in tracer settings.**/
    /**Redraw Counter.*/
    int redrawCounter = 0;
    /**Redraw counter max.*/
    int redrawCounterMax = 1;

    std::unique_ptr<BitmapFont> defaultFont = std::unique_ptr<BitmapFont>(
        new BitmapFont(decodeDefaultFont(), DEFAULT_FONT_ASCII_OFFSET,
                       DEFAULT_FONT_GLYPH_WIDTH, DEFAULT_FONT_GLYPH_HEIGHT,
                       DEFAULT_FONT_GLYPHS_X, DEFAULT_FONT_GLYPHS_Y));
};

typedef OfflineTurtleScreen TurtleScreen;

}  // namespace cturtle
#endif
