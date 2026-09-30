#pragma once
#include "CTurtle/font/BitmapFont.hpp"
#include "CTurtle/geometry/Transform.hpp"
#include "CTurtle/geometry/ivec2.hpp"
#include "CTurtle/objects/Polygon.hpp"
#include "CTurtle/objects/SceneObject.hpp"
#include "CTurtle/types/Color.hpp"
#include "CTurtle/types/Image.hpp"
#include "ScreenMode.hpp"
#include <list>
namespace cturtle {
class Turtle;
/**
 * \brief The AbstractTurtleScreen class is the abstract type for most turtle
 * functionality. It intentionally excludes all input/output functionality,
 * allowing for two intended derivates: an "interactive" screen, vs an "offline
 * rendering" screen. The Turtle class doesn't care which one it gets attached
 * to.
 */
class AbstractTurtleScreen {
public:
  virtual ~AbstractTurtleScreen() = default;

  /**
   * Sets the tracer setting for this window.
   */
  virtual void tracer(int countmax, unsigned int delayMS) = 0;

  /**
   * Returns the width of the window, in pixels.
   */
  virtual int window_width() const = 0;

  /**
   * Returns the height of the window, in pixels.
   */
  virtual int window_height() const = 0;

  /**
   * Returns the current background color.
   */
  virtual Color bgcolor() const = 0;

  /**
   * Sets the current background color.
   */
  virtual void bgcolor(const Color &c) = 0;

  /**
   * Sets the current screen mode.
   */
  virtual void mode(ScreenMode mode) = 0;

  /**
   * Returns the current screen mode.
   */
  virtual ScreenMode mode() const = 0;
  /**
   * Clears the screen.
   */
  virtual void clearscreen() = 0;

  /**Alias for clearscreen function
   *\sa clearscreen()*/
  void clear();

  /**Resets all turtles belonging to this screen to their original state.*/
  virtual void resetscreen() = 0;

  /**Resets all turtles belonging to this screen to their original state.*/
  void reset();

  /**
   * @return a boolean indicating if this turtle screen supports live animation.
   * "Live animation" is regarded as the frames of animation that encompass
   * movement over space.
   */
  virtual bool supports_live_animation() const = 0;

  virtual ivec2 screensize(Color &bg) = 0;
  // code-smell from python->c++, considering separation of functionality

  virtual ivec2 screensize() = 0;
  virtual void update(bool invalidateDraw, bool processInput) = 0;
  virtual void delay(unsigned int ms) = 0;
  virtual unsigned int delay() const = 0;

  /**
   * Closes this turtle screen.
   */
  virtual void bye() = 0;

  virtual Image &getcanvas() = 0;

  virtual bool isclosed() = 0;

  virtual void redraw(bool invalidate) = 0;

  /**
   * @brief Calculates and returns the root-level screen transformation.
   */
  virtual Transform screentransform() const = 0;

  /**
   * @brief Adds the specified turtle to this screen.
   * The turtle cannot belong to other screens, as
   * that would break ownership responsibility.
   */
  virtual void add(Turtle &turtle) = 0;

  /**
   * @brief Removes the specified turtle from this screen.
   * @param turtle
   */
  virtual void remove(Turtle &turtle) = 0;

  /**
   * @brief Returns a read-write reference to the list of scene objects
   * currently residing on this screen.
   * @return the list of scene objects currently residing on this screen.
   */
  virtual std::list<SceneObject> &getScene() = 0;

  /**
   * @brief Returns a read-write reference to the registered shape with the
   * specified name.
   * @param name of the shape
   * @return read-write reference to the associated shape
   */
  virtual AbstractDrawableObject &shape(const std::string &name) = 0;

  /**
   * @brief Returns a read-only reference to a previously loaded bitmap font.
   * @return a previously loaded font by its specified name.
   */
  virtual const BitmapFont &font(const std::string &name) const = 0;

protected:
  /**
   * Decodes the default font image from memory. The font is encoded
   * as 1 bit per pixel (on/off) for simplicity, and is relatively
   * easily decoded through bit-shifting.
   *
   * The loading of this was delegated to the AbstractTurtleScreen class
   * simply because all derived classes should have an idea of their
   * own internal states, however they will ALL have these managed states,
   * and thus ALL derived classes will need to call this function at some point
   * while performing default initialization.
   * @return the decoded default font image.
   */
  static Image decodeDefaultFont();

  /*The default shapes that screens initialize with.*/
  std::unordered_map<std::string, Polygon> shapes = {
      // counterclockwise coordinates.
      {"triangle", Polygon{{0, 0}, {-5, 5}, {5, 5}}},
      {"square", Polygon{{-5, -5}, {-5, 5}, {5, 5}, {5, -5}}},
      {"indented triangle",
       Polygon{// CCW
               {0, 0},
               {-5, 10},
               {0, 8},
               {5, 10}}},
      {"arrow",
       Polygon{{0, 0}, {-5, 5}, {-3, 5}, {-3, 10}, {3, 10}, {3, 5}, {5, 5}}}};

  // Abstract class. Private constructor only allows
  // for derivative classes to be instantiated.
  AbstractTurtleScreen() = default;
};

} // namespace cturtle
