// Copyright 2021 Jesse W. Walker
//
// Licensed under the MIT License.
// See LICENSE for details.
#pragma once
#ifndef CTURTLE_HEADLESS
#include <mutex>
#include <thread>

#include "CTurtle.hpp"
#include "CTurtle/util/io.hpp"
namespace cturtle {
constexpr int SCREEN_DEFAULT_WIDTH = 800;
constexpr int SCREEN_DEFAULT_HEIGHT = 600;
constexpr char SCREEN_DEFAULT_TITLE[] = "CTurtle " CTURTLE_VERSION;
/**
 * \brief The InteractiveTurtleScreen class holds and maintains facilities in
 * relation to displaying \ turtles and consuming input events from users
 * through callbacks. This includes holding the actual data for a given scene
 * after being populated by Turtle. It layers draw calls in the order they are
 * called, independent of whatever Turtle object creates it.
 * \sa Turtle
 */
class InteractiveTurtleScreen : public AbstractTurtleScreen {
   public:
    /**Empty constructor.
     * Assigns an 800 x 600 pixel display with a title of "CTurtle".*/
    InteractiveTurtleScreen();

    /**Title constructor.
     * Assigns an 800 x 600 pixel display with a specified title.
     *\param title The title to assign the display with.*/
    explicit InteractiveTurtleScreen(const std::string& title);

    /**Width, height, and title constructor.
     * Assigns the display with the specified dimensions, in pixels, and
     * assigns the display the specified title.
     *\param width The width of the display, in pixels.
     *\param height The height of the display, in pixels.
     *\param title The title of the display.*/
    InteractiveTurtleScreen(int width, int height,
                            const std::string& title = SCREEN_DEFAULT_TITLE);

    /**Destructor. Calls "bye" function.*/
    ~InteractiveTurtleScreen();

    /**Sets an internal variable that dictates how many frames
     * are skipped between screen updates; higher numbers will
     * speed up complex turtle drawings. Setting it to ZERO will
     * COMPLETELY disable animation until this value changes.
     *\param countmax The value of the aforementioned variable.
     *\param delayMS This value is sent to function "delay".*/
    void tracer(int countmax, unsigned int delayMS) override;

    /**Sets the background color of the screen.
     * Please note that, if there is a background image, this color is not
     * applied until it is removed.
     *\param color The background color.
     *\sa bgpic(image)*/
    void bgcolor(const Color& color) override;

    /**Returns the background color of the screen.
     *\return The background color of the screen.*/
    Color bgcolor() const override;

    /**\brief Sets the background image of the display.
     * Sets the background image. Please note that the background image
     * takes precedence over background color.
     *\param img The background image.*/
    void bgpic(const Image& img);

    /**Returns a const reference to the background image.*/
    const Image& bgpic();

    bool supports_live_animation() const override;

    /**Sets the screen mode of this screen.
     * Screen mode influences the initial heading added Turtles have,
     * as well as the direction of rotations.
     * This function brings ALL attached turtles to the home/default location.
     *\param mode The screen mode.
     */
    void mode(ScreenMode mode) override;

    /**Returns the screen mode of this screen.*/
    ScreenMode mode() const override;

    /**\brief Clears this screen.
     * Deletes all drawings and turtles,
     * Resets the background to plain white,
     * Clears all event bindings,
     */
    void clearscreen() override;

    /**Resets all turtles belonging to this screen to their original state->*/
    void resetscreen() override;

    /**Returns the size of this screen, in pixels.
      Also returns the background color of the screen,
      by assigning the input reference.*/ //code-smell from python->c++, considering separation of functionality
    ivec2 screensize(Color& bg) override;

    /**Returns the size of the screen, in pixels.*/
    ivec2 screensize() override;

    /**Updates the screen's graphics and input.
     *\param invalidateDraw Completely redraws the scene if true.
     *                      If false, only draws the newest geometry.
     *\param processInput A boolean indicating to process input.*/
    void update(bool invalidateDraw, bool processInput) override;

    /**Sets the delay set between turtle commands.*/
    void delay(unsigned int ms) override;

    /**Returns the delay set between screen swaps in milliseconds.*/
    unsigned int delay() const override;

    /**Returns the width of the window, in pixels.*/
    int window_width() const override;

    /**Returns the height of the window, in pixels.*/
    int window_height() const override;

    /**Saves the display as a file, the format of which is dependent
      on the file extension given in the specified file path string.*/
    void save(const std::string& file);

    /**Enters a loop, lasting until the display has been closed,
     * which updates the screen. This is useful for programs which
     * rely heavily on user input, as events are still called like normal.*/
    void mainloop();

    /**Resets and closes this display.*/
    void bye() override;

    /**Returns the canvas image used by this screen.*/
    Image& getcanvas() override;

    /**Returns the internal CImg display.*/
    cimg_library::CImgDisplay& internaldisplay();

    /**Returns a boolean indicating if the
      screen has been closed.*/
    bool isclosed() override;

    /**Draws all geometry from all child turtles and swaps this display.*/
    void redraw(bool invalidate) override;

    /**Returns the screen-level Transform
      of this screen. This is what puts the origin
      at the center of the screen rather than at
      at the top left, for example.*/
    Transform screentransform() const override;

    /**\brief Adds an additional "on press" key binding for the specified key.
     *\param func The function to call when the specified key is pressed.
     *\param key The specified key.*/
    void onkeypress(const KeyFunc& func, KeyboardKey key);

    /**\brief Adds an additional "on press" key binding for the specified key.
     *\param func The function to call when the specified key is released.
     *\param key The specified key.*/
    virtual void onkeyrelease(const KeyFunc& func, KeyboardKey key);

    /**\brief Simulates a key "on press" event.
     *\param key The key to call "on press" bindings for.*/
    void presskey(KeyboardKey key);

    /**\brief Simulates a key "on release" event.
     *\param key The key to call "on release" bindings for.*/
    void releasekey(KeyboardKey key);

    /**\brief Adds an additional "on click" mouse binding for the specified
     * button.
     *\param func The function to call when the specified button is clicked.
     *\param button The specified button.*/
    void onclick(const MouseFunc& func, MouseButton button = MOUSEB_LEFT);

    /**Calls all previously added mouse button call-backs.
     *\param x The X coordinate at which to press.
     *\param y The Y coordinate at which to press.
     *\param button The button to simulate being pressed.*/
    void click(int x, int y, MouseButton button);

    /**\copydoc click(int, int, MouseButton)*/
    void click(const Point& pt, MouseButton button);

    /**\brief Adds a timer function to be called every N milliseconds.
     *\param func The function to call when the timer has finished.
     *\param time The total number of milliseconds between calls.*/
    void ontimer(const TimerFunc& func, unsigned int time);

    /**Binds the "bye" function to the onclick event for the left
     * mouse button.*/
    void exitonclick();

    /**Adds the specified turtle to this screen.*/
    void add(Turtle& turtle) override;

    /**
     * @brief Removes the specified turtle from this screen.
     * @param turtle
     */
    void remove(Turtle& turtle) override;

    /**Returns a reference to the list of scene objects.
     * This list is used to redraw the screen.*/
    std::list<SceneObject>& getScene() override;

    /**
     * Returns the shape associated with the specified name.
     * @param name
     * @return
     */
    AbstractDrawableObject& shape(const std::string& name) override;

    /**
     * Adds the specified bitmap font to the screen.
     * It can be referenced later by its given name.
     * @param name the name given to the font.
     * @param font to add to the screen.
     */
    void addfont(const std::string& name, const BitmapFont& font);

    /**
     * Returns a read-only reference to the bitmap font with the specified name.
     * @param name to be given to the font.
     * @return read-only BitmapFont reference.
     */
    const BitmapFont& font(const std::string& name) const override;

   protected:
    /**The underlying display mechanism for a TurtleScreen.*/
    cimg_library::CImgDisplay display;

    /**The canvas onto which scene objects are drawn to.*/
    Image canvas;

    // The turtle composite image.
    // This image copies the canvas and has
    // turtles drawn to it to avoid redrawing a "busy" canvas.
    // Trace lines are also drawn on this when filling.
    Image turtleComposite;

    /**The total objects on screen the last time this screen was drawn.
     * Used to keep track of newer scene objects for a speed improvement.*/
    int lastTotalObjects = 0;

    /**The background color of this TurtleScreen.*/
    Color backgroundColor = Color("white");
    /**The background image of this TurtleScreen.
     * When not empty, this image takes precedence over
     * the background color when drawing.**/
    Image backgroundImage;
    /**The current screen mode.
     *\sa mode(m)*/
    ScreenMode curMode = SM_STANDARD;

    /**Redraw delay, in milliseconds.*/
    long int delayMS = 10;

    /** These variables are used specifically in tracer settings.**/
    /**Redraw Counter.*/
    int redrawCounter = 0;
    /**Redraw counter max.*/
    int redrawCounterMax = 1;

    /**Initializes the underlying event thread.
     * This thread is cleanly managed and destroyed
     * when its owning object is destroyed.
     * The thread just populates the cachedEvents list,
     * so that events may be processed in the main thread.*/
    void initEventThread();

    /**The scene list.*/
    std::list<SceneObject> objects;

    /**The list of attached turtles.*/
    std::list<Turtle*> turtles;

    /**A unique pointer to the event thread.
     *\sa initEventThread()*/
    std::unique_ptr<std::thread> eventThread;
    /**A list of cached events. Filled by event thread,
     * processed and emptied by main thread.*/
    std::list<InputEvent> cachedEvents;
    /**A boolean indicating whether or not to kill the event thread.*/
    bool killEventThread = false;
    /**The mutex which controls synchronization between the main
     * thread and the event thread.*/
    std::mutex eventCacheMutex;

    // this is an array. 0 for keyDown bindings, 1 for keyUp bindings.
    std::unordered_map<KeyboardKey, std::list<KeyFunc>> keyBindings[2] = {{},
                                                                          {}};
    // similar, mouseb_left mouseb_middle mouseb_right bindings.
    std::list<MouseFunc> mouseBindings[3] = {{}, {}, {}};
    // timer bindings, one function per originating time and delta.
    std::list<std::tuple<TimerFunc, uint64_t, uint64_t>> timerBindings;

    // map of fonts. only "default" is initially populated.
    std::unordered_map<std::string, std::unique_ptr<BitmapFont>> fonts;
};

typedef InteractiveTurtleScreen TurtleScreen;

}  // namespace cturtle
#endif
