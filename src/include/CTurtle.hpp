#pragma once
#define CTURTLE_VERSION_MAJOR "1"
#define CTURTLE_VERSION_MINOR "0"
#define CTURTLE_VERSION_PATCH "4"
#define CTURTLE_VERSION                                                        \
  "v" CTURTLE_VERSION_MAJOR "." CTURTLE_VERSION_MINOR "." CTURTLE_VERSION_PATCH

#include "CTurtle/font/TextAlign.hpp"
#include "CTurtle/objects/Line.hpp"
#include "CTurtle/turtle/AbstractTurtleScreen.hpp"
#ifdef CTURTLE_HEADLESS
#include "CTurtle/turtle/OfflineTurtleScreen.hpp"
#endif
#include "CTurtle/turtle/PenState.hpp"

namespace cturtle {
/**
 * \brief The Turtle Class
 * Symbolically represents a turtle that runs around a screen that has a
 * paint brush attached to its tail. The tail can be in two states; up and down.
 * As the turtle moves forwards, backwards, left, and right, it can draw
 * shapes and outlines, write text, and stamp itself onto whatever surface
 * it's walking/crawling on (In this case, it's walking on a TurtleScreen).
 *
 * \sa TurtleScreen
 */
class Turtle {
public:
  /**
   * \brief The turtle constructor. Turtles are attached to whatever screen they
   * are constructed with
   */
  explicit Turtle(AbstractTurtleScreen &scr);

  /**
   * \brief Turtles are not trivially copyable. The copy constructor is
   * explicitly disallowed.
   */
  Turtle(const Turtle &) = delete;

  /**
   * \brief Turtles are not trivially moved. The move constructor is explicitly
   * disallowed.
   */
  Turtle(Turtle &&mv) = delete;

  /**
   * \brief Turtles are not trivially moved. The copy operator is explicitly
   * disallowed.
   */
  Turtle &operator=(const Turtle &) = delete;

  /**
   * \brief Turtles are not trivially moved. The move operator is explicitly
   * disallowed.
   */
  Turtle &operator=(Turtle &&turtle) = delete;

  /**\brief Moves the turtle forward the specified number of pixels.
   * \param pixels total number of pixels to move.*/
  void forward(int pixels);

  /**\copydoc forward(int)*/
  void fd(int pixels);

  /**\brief Moves the turtle backward the specified number of pixels.*/
  void backward(int pixels);

  /**\copydoc backward(int)*/
  void bk(int pixels);

  /**\copydoc backward(int)*/
  void back(int pixels);

  /**\brief Rotates the turtle the specified number of units to the right.
   * The unit by which the input is specified is determined by the current
   * angle mode. The difference between Clockwise and Counterclockwise
   * is determined by the current screen's mode.
   * \sa degrees()
   * \sa radians()
   * \sa TurtleScreen::mode()*/
  void right(float amt);

  /**\copydoc right(float)*/
  void rt(float angle);

  /**\brief Rotates the turtle the specified number of units to the left.
   * The unit by which the input is specified is determined by the current
   * angle mode. The difference between Clockwise and Counterclockwise
   * is determined by the current screen's mode.
   * \sa degrees()
   * \sa radians()
   * \sa TurtleScreen::mode()*/
  void left(float amt);

  /**\copydoc left(float)*/
  void lt(float angle);

  /**\brief Sets the transform location of this turtle.*/
  void goTo(int x, int y);

  /**\brief Sets the transform location of this turtle.*/
  void goTo(const Point &pt);

  /**\copydoc goTo(int,int)*/
  void setpos(int x, int y);

  /**\copydoc goTo(int,int)*/
  void setpos(const Point &pt);

  /**\copydoc goTo(int,int)*/
  void setposition(int x, int y);

  /**\copydoc goTo(int,int)*/
  void setposition(const Point &pt);

  /**\brief Sets the X-axis transform location of this turtle.*/
  void setx(int x);

  /**\brief Sets the Y-axis transform location of this turtle.*/
  void sety(int y);

  /**
   * \brief Returns the current x coordinate location of this turtle.
   * \return x coordinate
   */
  int xcor() const;

  /**
   * \brief Returns the current y coordinate location of this turtle.
   * \return y coordinate
   */
  int ycor() const;

  /**
   * \brief Returns the current location of the turtle, as a Point.
   * \return the current location of the turtle, as a Point.
   */
  Point getpos() const;

  /**
   * \brief Adds a "naive" translation to the current turtle's transform.\
   * Does not take into account the rotation, or orientation, of the turtle.
   * \param x component of coordinate pair
   * \param y component of coordinate pair.
   */
  void shift(int x, int y);

  /**
   * @return a constant reference to the current state of this turtle.
   */
  const PenState &penstate() const;

  /**\brief Sets the rotation of this turtle.
   * The unit by which the input is specified is determined by the current
   * angle mode. The difference between Clockwise and Counterclockwise
   * is determined by the current screen's mode.
   * \sa degrees()
   * \sa radians()
   * \sa TurtleScreen::mode()*/
  void setheading(float amt);

  /**
   * Rotates the turtle to face the specified point.
   * @param x coordinate along the x axis to face
   * @param y coordinate along the y axis to face
   * \sa face(point)
   */
  void face(int x, int y);

  /**
   * Rotates the turtle to face the specified point.
   * @param pt point to face towards
   * \sa face(x, y)
   */
  void face(const Point &pt);

  /**
   * Returns the distance between this turtle and the given coordinate pair.
   * @param x X axis
   * @param y Y axis
   * @return distance between turtle position and coordinate pair.
   * \sa distance(point)
   */
  int distance(int x, int y);

  /**
   * Returns the distance between this turtle and the given point.
   * @param pt
   * @return
   * \sa distance(int, int)
   */
  int distance(const Point &pt);

  /**\copydoc setheading(float)*/
  void seth(float angle);

  /**
   * \brief Returns the angle between the line of the current turtle transform
   * to the given point.
   * @param x component of coordinate pair
   * @param y component of coordinate pair.
   * @return
   */
  float towards(int x, int y);

  /**
   * \brief Returns the angle between the line of the current turtle transform
   * to the given point.
   * @param pt
   * @return
   */
  float towards(const Point &pt);

  /**
   * \brief Returns the heading of the Turtle (e.g, its current rotation).
   * @return the heading of the Turtle (e.g, its current rotation)
   */
  float heading();

  /**\Brings the turtle back to its origin.
   * Depends on the current screen mode.
   * If the screen mode is set to "world", The turtle is turned to the right and
   * positive angles are counterclockwise.
   * Otherwise, if it is set to "logo", The turtle face upwards and positive
   * angles are clockwise.
   * \sa TurtleScreen::mode()*/
  void home();

  /**\brief Adds a circle to the screen.
   *\param radius The radius, in pixels, of the circle.
   *\param steps The "quality" of the circle. Higher is slow but looks better.
   * Use with low numbers for N-sided shapes.
   *\param color The color of the circle.*/
  void circle(int radius, int steps, const Color &color);

  /**\brief Adds a circle to the screen.
   * Default parameters are circle with a radius of 30 with 15 steps.
   *\param color The color of the circle.*/
  void circle(const Color &color);

  /**\brief Adds a dot to the screen.
   *\param The color of the dot.
   *\param size The size of the dot.
   */
  void dot(const Color &color, int size = 10);

  /**\brief Sets the "filling" state->
   * If the input is false but the prior state is true, a SceneObject
   * is put on the screen in the shape of the previously captured points.
   *\param state Whether or not the turtle is filling a polygon.*/
  void fill(bool val);

  /**
   * \brief Returns a boolean indicating if this turtle is currently filling a
   * shape.
   * \return a boolean indicating if this turtle is currently filling a shape.
   */
  bool filling() const;

  /**\brief Begins filling a polygon.
   *\sa fill(bool)*/
  void begin_fill();

  /**\brief Stops filling a polygon.
   *\sa fill(bool)*/
  void end_fill();

  /**\brief Sets the fill color of this turtle.
   *\param c The color with which to fill polygons.*/
  void fillcolor(const Color &c);

  /**\brief Returns the fill color of this turtle.
   *\return The current fill color.*/
  Color fillcolor();

  /**Writes the specified string to the screen.
   * Uses the current filling color.
   *\param text The text to write.
   *\sa fillcolor(color)*/
  void write(const std::string &text);

  /**Writes the specified string to the screen.
   * Uses the specified color.
   *\param text The text to write.
   *\param font The font name to use. Uses "default" font by default. Must be
   * registered to parent screen.
   *\param color The color to write the text in.
   *\param scale The scale to draw the text at. This is relative to the size of
   * the used font.
   *\param alignment The horizontal alignment of text. This is specifically
   * useful for multi-line strings.
   *\sa fillcolor(color)*/
  void write(const std::string &text, const std::string &font,
             const Color &color = {"white"}, float scale = 1.0f,
             TextAlign alignment = TEXT_ALIGN_LEFT);

  /**\brief Puts the current shape of this turtle on the screen
   *        with the current fill color and the outline of the shape.
   *\return The stamp ID of the put stamp.*/
  int stamp();

  /**\brief Removes the stamp with the specified ID.*/
  void clearstamp(int stampid);

  /**\brief Removes all stamps with an ID less than that which is specified.
   *        If the specified stampid is less than 0, it removes ALL stamps.*/
  void clearstamps(int stampid = -1);

  /**\brief Sets the shape of this turtle.
   *\param p The polygon to derive shape geometry from.*/
  void shape(const AbstractDrawableObject &p);

  /**\brief Sets the shape of this turtle from the specified shape name.
   *\param name The name of the shape to set.*/
  void shape(const std::string &name);

  /**\brief Returns the shape of this turtle.*/
  const AbstractDrawableObject &shape();

  /**\brief Undoes the previous action of this turtle.*/
  bool undo(bool try_redraw = true);

  /**\brief Set, or disable, the undo buffer.
   *\param size The size of the undo buffer.*/
  void setundobuffer(unsigned int size);

  /**\brief Returns the size of the undo stack.*/
  unsigned int undobufferentries();

  /**\brief Sets the speed of this turtle in range of 0 to 10.
   *\param The speed of the turtle, in range of 0 to 10.
   *\sa cturtle::TurtleSpeed*/
  void speed(float val);

  /**\brief Returns the speed of this turtle.*/
  float speed();

  /**\brief Applies a rotation to the turtle's cursor.*/
  void tilt(float amt);

  /**\brief Returns the rotation of the cursor. Not the heading,
   *        or the angle at which the forward function will move.*/
  float tilt() const;

  /**\brief Set whether or not the turtle is being shown.
   *\param state True when showing, false othewise.*/
  void setshowturtle(bool val);

  /**\brief Shows the turtle.
   *        Equivalent to calling setshowturtle(true).
   *\sa setshowturtle(bool)*/
  void showturtle();

  /**\brief Hides the turtle.
   *\sa setshowturtle(bool)*/
  void hideturtle();

  /**\brief Sets whether or not the pen is down.*/
  void setpenstate(bool down);

  /**\brief Brings the pen up.*/
  void penup();

  /**\brief Brings the pen down.*/
  void pendown();

  /**\brief Sets the pen color.
   *\param c The color used by the pen; the color of lines between movements.*/
  void pencolor(const Color &c);

  /**\brief Returns the pen color; the color of the lines between movements.
   *\return The color of the pen.*/
  Color pencolor() const;

  /**Sets the width of the pen line.
   *\param pixels The total width, in pixels, of the pen line.*/
  void width(int pixels);

  /**Returns the width of the pen line.
   *\return The width of the line, in pixels.*/
  int width() const;

  /**\brief Draws this turtle on the specified canvas with the specified
   * transform.
   *\param screenTransform The transform at which to draw the turtle objects.
   *\param canvas The canvas on which to draw this turtle.*/
  void draw(const Transform &screenTransform, Image &canvas);

  /**Sets this turtle to use angles measured in degrees.
   *\sa radians()*/
  void degrees();

  /**Sets this turtle to use angles measured in radians.
   *\sa degress()*/
  void radians();

  /**\brief Resets this turtle.
   * Moves this turtle home, resets all pen attributes,
   * and removes all previously added scene objects.*/
  void reset();

  /**\brief Sets this turtles screen.*/
  void setScreen(AbstractTurtleScreen *scr);

  /**\brief Empty virtual destructor.*/
  virtual ~Turtle();

protected:
  // a list of iterators that point to the parent screen's scene list.
  // this list is in-order as they are created by this instance.
  std::list<std::list<SceneObject>::iterator> objects;
  // the pen-state stack is, as its name might imply, the previous states
  // of the pen owned by this turtle.
  std::list<PenState> stateStack = {PenState()};
  std::list<Line> fillLines;

  // the current transform. This points to the topmost state's transform
  // on the pen state stack.
  Transform *transform = nullptr;
  // the current state. This points directly to the topmost state
  // on the pen state stack.
  PenState *state = nullptr;

  /* These variables are used to draw the "travel" line when
   * the turtle is traveling. (e.g, the line between where it's going
   * and where it's been)*/
  Point travelPoints[2];
  bool traveling = false;

  /*Undo stack size.*/
  unsigned int undoStackSize = 100;

  /*Accumulator for fill state*/
  Polygon fillAccum;

  /*Screen pointer. Assign before calling any other function!*/
  AbstractTurtleScreen *screen = nullptr;

  /*Pushes a copy of the pen's state on the stack.*/
  void pushState();

  /*Pops the top of the pen's state stack.*/
  bool popState();

  /**
   * \brief Internal function used to add geometry to the turtle screen.
   * \param t The transform of the geometry.
   * \param color The color of the geometry.
   * \param geom The geometry to add.
   * \return A boolean indicating if the geometry was added to the scene.
   */
  bool pushGeometry(const Transform &t, AbstractDrawableObject *geom);

  /**\brief Internal function used to add a stamp object to the turtle screen.
   *\param t The transform at which to draw the stamp.
   *\param color The color with which to draw the stamp.
   *\param geom The geometry of the stamp.*/
  bool pushStamp(const Transform &t, AbstractDrawableObject *geom);

  /**\brief Internal function used to add a text object to the turtle screen.
   *\param t The transform at which to draw the text.
   *\param color The color with which to draw the text.
   *\param font to use to draw the text.
   *\param scale to draw the text at.
   *\param text The string to draw.
   *\param alignment The alignment of the text. Particularly useful for
   * multi-line strings.*/
  bool pushText(const Transform &t, const Color &color, const BitmapFont &font,
                const std::string &text, float scale = 1.0f,
                TextAlign alignment = TEXT_ALIGN_LEFT);

  /**\brief Internal function used to add a trace line object to the turtle
   * screen. Trace lines do NOT push a state. Their state is encompassed by
   * movement, and these lines are only added when moving the turtle while the
   * pen is down.
   *\param a Point A
   *\param b Point B*/
  bool pushTraceLine(Point a, Point b);

  /**Returns the speed, of any applicable animation
    in milliseconds, based off of this turtle's speed setting.*/
  long int getAnimMS();

  /**Conditionally calls the parent screen's update function.*/
  void updateParent(bool invalidate = false, bool input = true);

  /**Performs an interpolation, with animation,
   * between the source transform and the destination transform.
   * May push a new fill vertex if filling and pushing state, and applies
   * appropriate lines if the pen is down. Generally manages all state related
   * to movement as a side effect.*/
  void travelBetween(Transform src, const Transform &dest, bool doPushState);

  /**Performs an interpolation, with animation,
   * between the current transform and the specified one.
   * Pushes a new fill vertex if filling, and applies appropriate
   * lines if the pen is down. Does push the state stack.*/
  void travelTo(const Transform &dest);

  /**Performs an interpolation, with animation,
   * between the current transformation and the previous one.
   * Will *not* push the state stack.
   * ENSURE STATE STACK IS BIG ENOUGH TO DO THIS BEFORE CALLING.*/
  void travelBack();

  /**Inheritors must assign screen pointer!*/
  Turtle() = default;
};
} // namespace cturtle
