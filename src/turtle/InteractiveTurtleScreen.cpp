// Copyright 2021 Jesse W. Walker
//
// Licensed under the MIT License.
// See LICENSE for details.
#ifndef CTURTLE_HEADLESS /*NOT DEFINED CTURTLE_HEADLESS*/
#include "CTurtle/turtle/InteractiveTurtleScreen.hpp"

#include <CTurtle.hpp>
#include <list>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

#include "CTurtle/font.hpp"
#include "CTurtle/util/io.hpp"
namespace cturtle {
InteractiveTurtleScreen::InteractiveTurtleScreen()
    : display(SCREEN_DEFAULT_WIDTH, SCREEN_DEFAULT_HEIGHT, SCREEN_DEFAULT_TITLE,
              0) {
    canvas.assign(display);
    initEventThread();
    redraw(true);
    fonts[DEFAULT_FONT] = std::unique_ptr<BitmapFont>(
        new BitmapFont(decodeDefaultFont(), DEFAULT_FONT_ASCII_OFFSET,
                       DEFAULT_FONT_GLYPH_WIDTH, DEFAULT_FONT_GLYPH_HEIGHT,
                       DEFAULT_FONT_GLYPHS_X, DEFAULT_FONT_GLYPHS_Y));
}
InteractiveTurtleScreen::InteractiveTurtleScreen(const std::string& title)
    : display(SCREEN_DEFAULT_WIDTH, SCREEN_DEFAULT_HEIGHT, title.c_str(), 0) {
    canvas.assign(display);
    initEventThread();
    redraw(true);

    fonts[DEFAULT_FONT] = std::unique_ptr<BitmapFont>(
        new BitmapFont(decodeDefaultFont(), DEFAULT_FONT_ASCII_OFFSET,
                       DEFAULT_FONT_GLYPH_WIDTH, DEFAULT_FONT_GLYPH_HEIGHT,
                       DEFAULT_FONT_GLYPHS_X, DEFAULT_FONT_GLYPHS_Y));
}

InteractiveTurtleScreen::InteractiveTurtleScreen(int width, int height,
                                                 const std::string& title)
    : display(width, height) {
    display.set_title(title.c_str());
    display.set_normalization(0);
    canvas.assign(display);
    initEventThread();
    redraw(true);

    fonts[DEFAULT_FONT] = std::unique_ptr<BitmapFont>(
        new BitmapFont(decodeDefaultFont(), DEFAULT_FONT_ASCII_OFFSET,
                       DEFAULT_FONT_GLYPH_WIDTH, DEFAULT_FONT_GLYPH_HEIGHT,
                       DEFAULT_FONT_GLYPHS_X, DEFAULT_FONT_GLYPHS_Y));
}

InteractiveTurtleScreen::~InteractiveTurtleScreen() { bye(); }

void InteractiveTurtleScreen::tracer(int countmax, unsigned int delayMS) {
    redrawCounterMax = countmax;
    delay(delayMS);
    redraw(false);
}

void InteractiveTurtleScreen::bgcolor(const Color& color) {
    backgroundColor = color;
    redraw(true);
}

Color InteractiveTurtleScreen::bgcolor() const { return backgroundColor; };

void InteractiveTurtleScreen::bgpic(const Image& img) {
    backgroundImage.assign(img);
    backgroundImage.resize(window_width(), window_height());
    redraw(true);
}

const Image& InteractiveTurtleScreen::bgpic() { return backgroundImage; }

bool InteractiveTurtleScreen::supports_live_animation() const { return true; }

void InteractiveTurtleScreen::mode(ScreenMode mode) {
    curMode = mode;
    for (Turtle* t : turtles) t->home();
}

ScreenMode InteractiveTurtleScreen::mode() const { return curMode; }

void InteractiveTurtleScreen::clearscreen() {
    // 1) Delete all drawings and turtles
    // 2) White background
    // 3) No background image
    // 4) No event bindings

    while (!turtles.empty()) remove(*turtles.front());

    turtles.clear();
    backgroundColor = Color("white");
    backgroundImage.assign();  // assign with no parameters is deleting whatever
                               // contents it may have.
    curMode = SM_STANDARD;

    // Gotta do binding alterations under the cache's mutex lock.
    eventCacheMutex.lock();
    timerBindings.clear();
    keyBindings[0].clear();
    keyBindings[1].clear();
    for (auto& mouseBinding : mouseBindings) mouseBinding.clear();
    eventCacheMutex.unlock();
}

void InteractiveTurtleScreen::resetscreen() {
    for (Turtle* turtle : turtles) turtle->reset();
}

ivec2 InteractiveTurtleScreen::screensize(Color& bg) {
    bg = backgroundColor;
    return {display.width(), display.height()};
}

ivec2 InteractiveTurtleScreen::screensize() {  // see line above comment about
                                               // code-smell
    return {display.width(), display.height()};
}

void InteractiveTurtleScreen::update(bool invalidateDraw, bool processInput) {
    /*Resize canvas when necessary.*/
    if (display.is_resized()) {
        display.resize();
        invalidateDraw = true;
    }
    redraw(invalidateDraw);

    if (processInput && !timerBindings.empty()) {
        // Call timer bindings first.
        uint64_t curTime = detail::epochTime();
        for (auto& timer : timerBindings) {
            auto& func = std::get<0>(timer);
            uint64_t reqTime = std::get<1>(timer);
            uint64_t& lastCalled = std::get<2>(timer);

            if (curTime >= lastCalled + reqTime) {
                lastCalled = curTime;
                func();
            }
        }
    }

    /**No events to process in the cache, or we're not processing it right
     * now.*/
    if (cachedEvents.empty() || !processInput) return;  // No events to process.

    // lock event cache to avoid race conditions
    eventCacheMutex.lock();

    for (InputEvent& event : cachedEvents) {
        if (event.type) {  // process keyboard event
            KeyFunc& keyFunc = *reinterpret_cast<KeyFunc*>(event.cbPointer);
            keyFunc();
        } else {  // process mouse event
            MouseFunc& mFunc = *reinterpret_cast<MouseFunc*>(event.cbPointer);
            mFunc(event.mX, event.mY);
        }
    }

    cachedEvents.clear();
    eventCacheMutex.unlock();
}

/**Sets the delay set between turtle commands.*/
void InteractiveTurtleScreen::delay(unsigned int ms) { delayMS = ms; }

/**Returns the delay set between screen swaps in milliseconds.*/
unsigned int InteractiveTurtleScreen::delay() const { return delayMS; }

/**Returns the width of the window, in pixels.*/
int InteractiveTurtleScreen::window_width() const {
    return display.window_width();
}

/**Returns the height of the window, in pixels.*/
int InteractiveTurtleScreen::window_height() const {
    return display.window_height();
}

void InteractiveTurtleScreen::save(const std::string& file) {
    Image screenshotImg;
    display.snapshot(screenshotImg);
    screenshotImg.save(file.c_str());
}

void InteractiveTurtleScreen::mainloop() {
    while (!display.is_closed()) {
        update(false, true);
        std::this_thread::yield();  // Yield repetitive loops on mainloop to
                                    // avoid high-cpu usage.
    }
}

void InteractiveTurtleScreen::bye() {
    if (redrawCounter > 0 || redrawCounter >= redrawCounterMax) {
        tracer(1, delayMS);
    }

    if (eventThread != nullptr) {
        killEventThread = true;
        eventThread->join();
        eventThread.reset(nullptr);
    }

    clearscreen();

    if (!display.is_closed()) display.close();
}

Image& InteractiveTurtleScreen::getcanvas() { return canvas; }

cimg_library::CImgDisplay& InteractiveTurtleScreen::internaldisplay() {
    return display;
}

bool InteractiveTurtleScreen::isclosed() {
    return internaldisplay().is_closed();
}

void InteractiveTurtleScreen::redraw(bool invalidate) {
    if (isclosed()) return;
    int fromBack = 0;
    bool hasInvalidated = invalidate;

    // Handle resizes.
    if (display.window_width() != canvas.width() ||
        display.window_height() != canvas.height()) {
        canvas.resize(display);
        hasInvalidated = true;
    }
    int objectSize = static_cast<int>(objects.size());
    if (lastTotalObjects <= objectSize) {
        fromBack = objects.size() - lastTotalObjects;
    }

    if (hasInvalidated) {
        if (!backgroundImage.is_empty()) {
            const int centerX =
                (canvas.width() / 2) - (backgroundImage.width() / 2);
            const int centerY =
                (canvas.height() / 2) - (backgroundImage.height() / 2);
            canvas.draw_image(centerX, centerY, backgroundImage);
        } else {
            canvas.draw_rectangle(0, 0, canvas.width(), canvas.height(),
                                  backgroundColor.rgbPtr());
        }

        redrawCounter = 0;  // Forced redraw due to canvas invalidation.
    } else {
        if (redrawCounterMax ==
            0)  // tracer settings may disable rendering for a short time...
            return;
        redrawCounter++;

        if (redrawCounter >= redrawCounterMax)
            redrawCounter = 0;
        else {
            return;
        }
    }

    // get the iterator pointing to the oldest scene object that hasn't been
    // drawn yet if the scene has been invalidated, the latest object is the
    // first one in the scene. otherwise,
    auto latestIter =
        !hasInvalidated ? std::prev(objects.end(), fromBack) : objects.begin();

    const Transform screen = screentransform();
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
    display.display(turtleComposite);
    detail::sleep(delayMS);
}

Transform InteractiveTurtleScreen::screentransform() const {
    // Scale negatively on Y axis to match
    // Python's coordinate system.
    // without this scaling, top left is 0,0
    // instead of the bottom left (which is 0,Y without the scaling)
    return Transform()
        .translate(canvas.width() / 2, canvas.height() / 2)
        .scale(1, -1.0f);
}

void InteractiveTurtleScreen::onkeypress(const KeyFunc& func, KeyboardKey key) {
    eventCacheMutex.lock();
    // determine if key list exists
    if (keyBindings[0].find(key) == keyBindings[0].end()) {
        keyBindings[0][key] = std::list<KeyFunc>();
    }
    // then push it to the end of the list
    keyBindings[0][key].push_back(func);
    eventCacheMutex.unlock();
}

/**\brief Adds an additional "on press" key binding for the specified key.
 *\param func The function to call when the specified key is released.
 *\param key The specified key.*/
void InteractiveTurtleScreen::onkeyrelease(const KeyFunc& func,
                                           KeyboardKey key) {
    eventCacheMutex.lock();
    // determine if key list exists, if not, make one
    if (keyBindings[1].find(key) == keyBindings[1].end()) {
        keyBindings[1][key] = std::list<KeyFunc>();
    }
    // then push it to the end of the list
    keyBindings[1][key].push_back(func);
    eventCacheMutex.unlock();
}

/**\brief Simulates a key "on press" event.
 *\param key The key to call "on press" bindings for.*/
void InteractiveTurtleScreen::presskey(KeyboardKey key) {
    if (keyBindings[0].find(key) == keyBindings[0].end()) return;
    for (const KeyFunc& func : keyBindings[0][key]) {
        func();
    }
}

/**\brief Simulates a key "on release" event.
 *\param key The key to call "on release" bindings for.*/
void InteractiveTurtleScreen::releasekey(KeyboardKey key) {
    if (keyBindings[1].find(key) == keyBindings[1].end()) return;
    for (KeyFunc& func : keyBindings[1][key]) {
        func();
    }
}

/**\brief Adds an additional "on click" mouse binding for the specified
 * button.
 *\param func The function to call when the specified button is clicked.
 *\param button The specified button.*/
void InteractiveTurtleScreen::onclick(const MouseFunc& func,
                                      MouseButton button) {
    eventCacheMutex.lock();
    mouseBindings[button].push_back(func);
    eventCacheMutex.unlock();
}

/**Calls all previously added mouse button call-backs.
 *\param x The X coordinate at which to press.
 *\param y The Y coordinate at which to press.
 *\param button The button to simulate being pressed.*/
void InteractiveTurtleScreen::click(int x, int y, MouseButton button) {
    eventCacheMutex.lock();
    for (MouseFunc& func : mouseBindings[button]) {
        func(x, y);
    }
    eventCacheMutex.unlock();
}

/**\copydoc click(int, int, MouseButton)*/
void InteractiveTurtleScreen::click(const Point& pt, MouseButton button) {
    click(pt.x, pt.y, button);
}

/**\brief Adds a timer function to be called every N milliseconds.
 *\param func The function to call when the timer has finished.
 *\param time The total number of milliseconds between calls.*/
void InteractiveTurtleScreen::ontimer(const TimerFunc& func,
                                      unsigned int time) {
    timerBindings.emplace_back(
        std::make_tuple(func, time, detail::epochTime()));
}

/**Binds the "bye" function to the onclick event for the left
 * mouse button.*/
void InteractiveTurtleScreen::exitonclick() {
    // Catch up visually before entering event loop, when necessary.
    if (redrawCounter > 0 || redrawCounter >= redrawCounterMax) {
        tracer(1, delayMS);
    }

    onclick([&](int x, int y) { display.close(); });
    mainloop();
}

/**Adds the specified turtle to this screen.*/
void InteractiveTurtleScreen::add(Turtle& turtle) {
    turtles.push_back(&turtle);
}

/**
 * @brief Removes the specified turtle from this screen.
 * @param turtle
 */
void InteractiveTurtleScreen::remove(Turtle& turtle) {
    turtle.reset();
    turtle.setScreen(nullptr);
    turtles.remove(&turtle);
}

/**Returns a reference to the list of scene objects.
 * This list is used to redraw the screen.*/
std::list<SceneObject>& InteractiveTurtleScreen::getScene() { return objects; }

/**
 * Returns the shape associated with the specified name.
 * @param name
 * @return
 */
AbstractDrawableObject& InteractiveTurtleScreen::shape(
    const std::string& name) {
    return shapes[name];
}

/**
 * Adds the specified bitmap font to the screen.
 * It can be referenced later by its given name.
 * @param name the name given to the font.
 * @param font to add to the screen.
 */
void InteractiveTurtleScreen::addfont(const std::string& name,
                                      const BitmapFont& font) {
    fonts[name] = std::unique_ptr<BitmapFont>(new BitmapFont(font));
}

/**
 * Returns a read-only reference to the bitmap font with the specified name.
 * @param name to be given to the font.
 * @return read-only BitmapFont reference.
 */
const BitmapFont& InteractiveTurtleScreen::font(const std::string& name) const {
    return *fonts.at(name);
}

void InteractiveTurtleScreen::initEventThread() {
    eventThread.reset(new std::thread([&]() {
        // Mouse button states, between updates.
        // Keeps track of release/press etc
        // states for all three mouse buttons for isDown.
        //*importantly, this allows us to avoid repeated events.
        bool mButtons[3] = {false, false, false};
        // Same thing for keys here.
        //(this is a list of keys marked as being in a "down" state)
        std::list<KeyboardKey> mKeys;

        while (!display.is_closed() && !killEventThread) {
            // Updates all input.
            if (!display.is_event()) {
                std::this_thread::yield();
                continue;
            }

            eventCacheMutex.lock();

            Transform mouseOffset = screentransform();
            Point mousePos = {
                static_cast<int>((static_cast<float>(display.mouse_x()) -
                                  mouseOffset.getTranslateX()) *
                                 mouseOffset.getScaleX()),
                static_cast<int>((static_cast<float>(display.mouse_y()) -
                                  mouseOffset.getTranslateY()) *
                                 mouseOffset.getScaleY())};

            // Update mouse button input.
            const unsigned int button = display.button();
            bool buttons[3] = {
                static_cast<bool>(button & 1),  // left
                static_cast<bool>(button & 2),  // right
                static_cast<bool>(button & 4)   // middle
            };

            for (int i = 0; i < 3; i++) {
                if (!(!mButtons[i] &&
                      buttons[i]))  // is this button state "down"?
                    continue;       // if not, skip its processing loop.

                for (MouseFunc& func : mouseBindings[i]) {
                    // append to the event cache.
                    InputEvent e;
                    e.type = false;
                    e.mX = mousePos.x;
                    e.mY = mousePos.y;
                    e.cbPointer = reinterpret_cast<void*>(&func);
                    cachedEvents.push_back(e);
                }
            }

            const auto& keys = NAMED_KEYS;

            // iterate through every key to determine its state,
            // then call the appropriate callbacks.
            for (const auto& keyPair : keys) {
                KeyboardKey key = keyPair.second;
                const bool lastDown =
                    std::find(mKeys.begin(), mKeys.end(), key) != mKeys.end();
                const bool curDown = display.is_key((unsigned int)key);

                int state = -1;
                if (!lastDown && curDown) {
                    // Key down.
                    state = 0;
                    mKeys.push_back(key);
                } else if (lastDown && !curDown) {
                    // Key up.
                    state = 1;
                    mKeys.remove(key);
                } else {
                    continue;  // skip on case where it was down and is down
                }

                try {
                    // will throw if no bindings available for key,
                    // and that's perfectly fine, so we just silently catch
                    auto& bindingList = keyBindings[state][key];
                    for (auto& cb : bindingList) {
                        cb();
                    }
                } catch (...) {
                }
            }

            mButtons[0] = buttons[0];
            mButtons[1] = buttons[1];
            mButtons[2] = buttons[2];
            eventCacheMutex.unlock();
        }
    }));
}

}  // namespace cturtle
#endif /*CTURTLE_HEADLESS*/
