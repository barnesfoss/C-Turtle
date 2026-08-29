// MIT License
//
// Copyright (c) 2021 Jesse W. Walker
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

/**
    :::::::: ::::::::::: :::    ::: ::::::::: ::::::::::: :::        ::::::::::
   :+:    :+:    :+:     :+:    :+: :+:    :+:    :+:     :+:        :+:
   +:+           +:+     +:+    +:+ +:+    +:+    +:+     +:+        +:+
   +#+           +#+     +#+    +:+ +#++:++#:     +#+     +#+        +#++:++#
   +#+           +#+     +#+    +#+ +#+    +#+    +#+     +#+        +#+
   #+#    #+#    #+#     #+#    #+# #+#    #+#    #+#     #+#        #+#
    ########     ###      ########  ###    ###    ###     ########## ##########
   =================================v1.0.5====================================>

   GitHub: https://github.com/walkerje/C-Turtle
   Documentation: https://bitshiftmountain.com/projects/cturtle/docs
**/
#pragma once
#define CTURTLE_VERSION_MAJOR "1"
#define CTURTLE_VERSION_MINOR "0"
#define CTURTLE_VERSION_PATCH "4"
#define CTURTLE_VERSION                                                        \
  "v" CTURTLE_VERSION_MAJOR "." CTURTLE_VERSION_MINOR "." CTURTLE_VERSION_PATCH
#include "font/TextAlign.hpp"
#include "objects/Circle.hpp"
#include "objects/Line.hpp"
#include "objects/Text.hpp"
#include "turtle/AbstractTurtleScreen.hpp"
#include "turtle/PenState.hpp"
#include "util/io.hpp"
#include <cmath>
#include <cstdint>
#include <mutex>
#include <string>
#include <thread>

#ifdef CTURTLE_HEADLESS
#include "util/headless.hpp"
#endif
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
  explicit Turtle(AbstractTurtleScreen &scr) {
    screen = &scr;
    screen->add(*this);
    reset();
  }

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
  void forward(int pixels) {
    if (screen == nullptr)
      return;
    travelTo(Transform(*transform).forward(static_cast<float>(pixels)));
  }

  /**\copydoc forward(int)*/
  inline void fd(int pixels) { forward(pixels); }

  /**\brief Moves the turtle backward the specified number of pixels.*/
  void backward(int pixels) {
    if (screen == nullptr)
      return;
    travelTo(Transform(*transform).backward(static_cast<float>(pixels)));
  }

  /**\copydoc backward(int)*/
  inline void bk(int pixels) { backward(pixels); }

  /**\copydoc backward(int)*/
  inline void back(int pixels) { backward(pixels); }

  /**\brief Rotates the turtle the specified number of units to the right.
   * The unit by which the input is specified is determined by the current
   * angle mode. The difference between Clockwise and Counterclockwise
   * is determined by the current screen's mode.
   * \sa degrees()
   * \sa radians()
   * \sa TurtleScreen::mode()*/
  void right(float amt) {
    amt = state->angleMode ? -amt : -toRadians(amt);
    // Flip angle orientation based on screen mode.
    travelTo(Transform(*transform).rotate(amt));
  }

  /**\copydoc right(float)*/
  inline void rt(float angle) { right(angle); }

  /**\brief Rotates the turtle the specified number of units to the left.
   * The unit by which the input is specified is determined by the current
   * angle mode. The difference between Clockwise and Counterclockwise
   * is determined by the current screen's mode.
   * \sa degrees()
   * \sa radians()
   * \sa TurtleScreen::mode()*/
  void left(float amt) {
    amt = state->angleMode ? amt : toRadians(amt);
    // Flip angle orientation based on screen mode.
    travelTo(Transform(*transform).rotate(amt));
  }

  /**\copydoc left(float)*/
  inline void lt(float angle) { left(angle); }

  /**\brief Sets the transform location of this turtle.*/
  void goTo(int x, int y) {
    travelTo(Transform(*transform).setTranslation(x, y));
  }

  /**\brief Sets the transform location of this turtle.*/
  inline void goTo(const Point &pt) { goTo(pt.x, pt.y); }

  /**\copydoc goTo(int,int)*/
  inline void setpos(int x, int y) { goTo(x, y); }

  /**\copydoc goTo(int,int)*/
  inline void setpos(const Point &pt) { goTo(pt.x, pt.y); }

  /**\copydoc goTo(int,int)*/
  inline void setposition(int x, int y) { goTo(x, y); }

  /**\copydoc goTo(int,int)*/
  inline void setposition(const Point &pt) { goTo(pt.x, pt.y); }

  /**\brief Sets the X-axis transform location of this turtle.*/
  void setx(int x) { travelTo(Transform(*transform).setTranslationX(x)); }

  /**\brief Sets the Y-axis transform location of this turtle.*/
  void sety(int y) { travelTo(Transform(*transform).setTranslationY(y)); }

  /**
   * \brief Returns the current x coordinate location of this turtle.
   * \return x coordinate
   */
  int xcor() const { return static_cast<int>(transform->getTranslateX()); }

  /**
   * \brief Returns the current y coordinate location of this turtle.
   * \return y coordinate
   */
  int ycor() const { return static_cast<int>(transform->getTranslateY()); }

  /**
   * \brief Returns the current location of the turtle, as a Point.
   * \return the current location of the turtle, as a Point.
   */
  Point getpos() const { return transform->getTranslation(); }

  /**
   * \brief Adds a "naive" translation to the current turtle's transform.\
   * Does not take into account the rotation, or orientation, of the turtle.
   * \param x component of coordinate pair
   * \param y component of coordinate pair.
   */
  inline void shift(int x, int y) { goTo(getpos() + Point(x, y)); }

  /**
   * @return a constant reference to the current state of this turtle.
   */
  const PenState &penstate() const { return *state; }

  /**\brief Sets the rotation of this turtle.
   * The unit by which the input is specified is determined by the current
   * angle mode. The difference between Clockwise and Counterclockwise
   * is determined by the current screen's mode.
   * \sa degrees()
   * \sa radians()
   * \sa TurtleScreen::mode()*/
  void setheading(float amt) {
    // Swap to correct unit if necessary.
    amt = state->angleMode ? amt : toRadians(amt);
    // Flip angle orientation based on screen mode.
    amt =
        (screen != nullptr) ? screen->mode() == SM_STANDARD ? amt : -amt : amt;
    travelTo(Transform(*transform).setRotation(amt));
  }

  /**
   * Rotates the turtle to face the specified point.
   * @param x coordinate along the x axis to face
   * @param y coordinate along the y axis to face
   * \sa face(point)
   */
  inline void face(int x, int y) { setheading(towards(x, y) - heading()); }

  /**
   * Rotates the turtle to face the specified point.
   * @param pt point to face towards
   * \sa face(x, y)
   */
  inline void face(const Point &pt) { setheading(towards(pt) - heading()); }

  /**
   * Returns the distance between this turtle and the given coordinate pair.
   * @param x X axis
   * @param y Y axis
   * @return distance between turtle position and coordinate pair.
   * \sa distance(point)
   */
  int distance(int x, int y) {
    return cturtle::distance(transform->getTranslation(), {x, y});
  }

  /**
   * Returns the distance between this turtle and the given point.
   * @param pt
   * @return
   * \sa distance(int, int)
   */
  int distance(const Point &pt) {
    return cturtle::distance(transform->getTranslation(), pt);
  }

  /**\copydoc setheading(float)*/
  inline void seth(float angle) { setheading(angle); }

  /**
   * \brief Returns the angle between the line of the current turtle transform
   * to the given point.
   * @param x component of coordinate pair
   * @param y component of coordinate pair.
   * @return
   */
  float towards(int x, int y) {
    float amt = std::atan2(static_cast<float>(y) - transform->getTranslateY(),
                           static_cast<float>(x) - transform->getTranslateX());

    // 6.28319 is a full rotation in radians...
    if (toDegrees(amt) < 0)
      amt = 6.28319f + amt;

    // convert to degrees if necessary.
    amt = state->angleMode ? amt : toDegrees(amt);
    return amt + heading();
  }

  /**
   * \brief Returns the angle between the line of the current turtle transform
   * to the given point.
   * @param pt
   * @return
   */
  inline float towards(const Point &pt) { return towards(pt.x, pt.y); }

  /**
   * \brief Returns the heading of the Turtle (e.g, its current rotation).
   * @return the heading of the Turtle (e.g, its current rotation)
   */
  inline float heading() {
    return state->angleMode ? transform->getRotation()
                            : toDegrees(transform->getRotation());
  }

  /**\Brings the turtle back to its origin.
   * Depends on the current screen mode.
   * If the screen mode is set to "world", The turtle is turned to the right and
   * positive angles are counterclockwise.
   * Otherwise, if it is set to "logo", The turtle face upwards and positive
   * angles are clockwise.
   * \sa TurtleScreen::mode()*/
  void home() {
    travelTo(Transform()); // set transform to identity, more-or-less...
  }

  /**\brief Adds a circle to the screen.
   *\param radius The radius, in pixels, of the circle.
   *\param steps The "quality" of the circle. Higher is slow but looks better.
   * Use with low numbers for N-sided shapes.
   *\param color The color of the circle.*/
  void circle(int radius, int steps, const Color &color) {
    pushGeometry(*transform, new Circle(radius, steps, color));
    updateParent(false, true);
  }

  /**\brief Adds a circle to the screen.
   * Default parameters are circle with a radius of 30 with 15 steps.
   *\param color The color of the circle.*/
  inline void circle(const Color &color) { circle(30, 15, color); }

  /**\brief Adds a dot to the screen.
   *\param The color of the dot.
   *\param size The size of the dot.
   */
  void dot(const Color &color, int size = 10) { circle(size / 2, 4, color); }

  /**\brief Sets the "filling" state->
   * If the input is false but the prior state is true, a SceneObject
   * is put on the screen in the shape of the previously captured points.
   *\param state Whether or not the turtle is filling a polygon.*/
  void fill(bool val) {
    if (state->filling && !val) {
      // Add the fill polygon
      screen->getScene().emplace_back(
          new Polygon(fillAccum.points, state->fillColor), Transform());
      objects.push_back(std::prev(screen->getScene().end(), 1));

      // Add all trace lines created when tracing out the fill polygon.
      if (!fillLines.empty()) {
        // for each line we've created when having the pen down, and have been
        // tracing a shape
        for (Line &lineInfo : fillLines) {
          screen->getScene().emplace_back(lineInfo.copy(), Transform());
          objects.push_back(std::prev(screen->getScene().end(), 1));
        }
        fillLines.clear();
      }

      fillAccum.points.clear();
      updateParent(false, false);
    }
    state->filling = val;
  }

  /**
   * \brief Returns a boolean indicating if this turtle is currently filling a
   * shape.
   * \return a boolean indicating if this turtle is currently filling a shape.
   */
  inline bool filling() const { return penstate().filling; }

  /**\brief Begins filling a polygon.
   *\sa fill(bool)*/
  inline void begin_fill() { fill(true); }

  /**\brief Stops filling a polygon.
   *\sa fill(bool)*/
  inline void end_fill() { fill(false); }

  /**\brief Sets the fill color of this turtle.
   *\param c The color with which to fill polygons.*/
  void fillcolor(const Color &c) {
    pushState();
    state->fillColor = c;
    updateParent(false, false);
  }

  /**\brief Returns the fill color of this turtle.
   *\return The current fill color.*/
  Color fillcolor() { return state->fillColor; }

  /**Writes the specified string to the screen.
   * Uses the current filling color.
   *\param text The text to write.
   *\sa fillcolor(color)*/
  void write(const std::string &text) {
    if (text.empty())
      return;
    pushText(*transform, state->fillColor, screen->font(DEFAULT_FONT), text,
             1.0f);
    updateParent(false, false);
  }

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
             TextAlign alignment = TEXT_ALIGN_LEFT) {
    if (text.empty())
      return;
    pushText(*transform, color, screen->font(font), text, scale, alignment);
    updateParent(false, false);
  }

  /**\brief Puts the current shape of this turtle on the screen
   *        with the current fill color and the outline of the shape.
   *\return The stamp ID of the put stamp.*/
  int stamp() {
    pushStamp(*transform, state->cursor->copy());
    return state->curStamp;
  }

  /**\brief Removes the stamp with the specified ID.*/
  void clearstamp(int stampid) {
    auto iter = objects.begin(); // iterator which holds an iterator to the
                                 // screen's scene list.

    while (iter != objects.end()) {
      auto &objIter = *iter;
      if (objIter->stamp && objIter->stampid == stampid) {
        break;
      }
      iter++;
    }

    if (iter != objects.end()) {
      objects.erase(iter);

      if (screen != nullptr) {
        screen->getScene().erase(*iter);
      }
    }

    updateParent(true, false);
  }

  /**\brief Removes all stamps with an ID less than that which is specified.
   *        If the specified stampid is less than 0, it removes ALL stamps.*/
  void clearstamps(int stampid = -1) {
    typedef decltype(objects.begin()) iter_t;

    std::list<iter_t> removals;

    auto iter = objects.begin();
    while (iter != objects.end()) {
      auto &objIter = *iter;
      if (stampid < 0 ? objIter->stamp
                      : (objIter->stamp && objIter->stampid <= stampid)) {
        removals.push_back(iter);
      }
      iter++;
    }

    for (auto &iter : removals) {
      screen->getScene().erase(*iter);
      objects.erase(iter);
    }

    updateParent(true, false);
  }

  /**\brief Sets the shape of this turtle.
   *\param p The polygon to derive shape geometry from.*/
  void shape(const AbstractDrawableObject &p) {
    pushState();
    state->cursor.reset(p.copy());
    updateParent(false, false);
  }

  /**\brief Sets the shape of this turtle from the specified shape name.
   *\param name The name of the shape to set.*/
  void shape(const std::string &name) {
    pushState();
    state->cursor.reset((screen->shape(name).copy()));
    updateParent(false, false);
  }

  /**\brief Returns the shape of this turtle.*/
  const AbstractDrawableObject &shape() { return *state->cursor; }

  /**\brief Undoes the previous action of this turtle.*/
  bool undo(bool try_redraw = true) {
    // total objects on the state stack prior to
    const unsigned long int totalBefore = state->objectsBefore;

    if (stateStack.size() >= 2)
      travelBack(); // Travel back if stack size >= 2

    // If we can't pop the state, break early.
    if (!popState()) {
      return false;
    }

    auto begin = std::prev(objects.end(), (totalBefore - state->objectsBefore));
    auto iter = begin;

    while (iter != objects.end()) {
      screen->getScene().erase(*iter);
      iter++;
    }

    objects.erase(begin, objects.end());

    // Will invalidate the whole screen due to object removal, but we allow the
    // option to not.
    updateParent(try_redraw, false);
    return true;
  }

  /**\brief Set, or disable, the undo buffer.
   *\param size The size of the undo buffer.*/
  void setundobuffer(unsigned int size) {
    if (size < 1) // clamp lower bound to 1
      size = 1;

    undoStackSize = size;
    while (stateStack.size() > size) {
      stateStack.pop_front();
    }
  }

  /**\brief Returns the size of the undo stack.*/
  unsigned int undobufferentries() {
    return static_cast<unsigned int>(stateStack.size());
  }

  /**\brief Sets the speed of this turtle in range of 0 to 10.
   *\param The speed of the turtle, in range of 0 to 10.
   *\sa cturtle::TurtleSpeed*/
  void speed(float val) {
    pushState();
    state->moveSpeed = val;
  }

  /**\brief Returns the speed of this turtle.*/
  float speed() { return state->moveSpeed; }

  /**\brief Applies a rotation to the turtle's cursor.*/
  void tilt(float amt) {
    amt = state->angleMode ? amt : toRadians(amt);
    // Flip angle orientation based on screen mode.
    amt = screen->mode() == SM_STANDARD ? amt : -amt;
    pushState();
    state->cursorTilt += amt;
    updateParent(false, false);
  }

  /**\brief Returns the rotation of the cursor. Not the heading,
   *        or the angle at which the forward function will move.*/
  float tilt() const {
    return state->angleMode ? state->cursorTilt : toDegrees(state->cursorTilt);
  }

  /**\brief Set whether or not the turtle is being shown.
   *\param state True when showing, false othewise.*/
  void setshowturtle(bool val) {
    pushState();
    state->visible = val;
    updateParent(false, false);
  }

  /**\brief Shows the turtle.
   *        Equivalent to calling setshowturtle(true).
   *\sa setshowturtle(bool)*/
  inline void showturtle() { setshowturtle(true); }

  /**\brief Hides the turtle.
   *\sa setshowturtle(bool)*/
  inline void hideturtle() { setshowturtle(false); }

  /**\brief Sets whether or not the pen is down.*/
  void setpenstate(bool down) {
    pushState();
    state->tracing = down;
  }

  /**\brief Brings the pen up.*/
  inline void penup() { setpenstate(false); }

  /**\brief Brings the pen down.*/
  inline void pendown() { setpenstate(true); }

  /**\brief Sets the pen color.
   *\param c The color used by the pen; the color of lines between movements.*/
  void pencolor(const Color &c) {
    pushState();
    state->penColor = c;
    updateParent(false, false);
  }

  /**\brief Returns the pen color; the color of the lines between movements.
   *\return The color of the pen.*/
  Color pencolor() const { return state->penColor; }

  /**Sets the width of the pen line.
   *\param pixels The total width, in pixels, of the pen line.*/
  void width(int pixels) {
    pushState();
    state->penWidth = pixels;
  }

  /**Returns the width of the pen line.
   *\return The width of the line, in pixels.*/
  int width() const { return state->penWidth; }

  /**\brief Draws this turtle on the specified canvas with the specified
   * transform.
   *\param screenTransform The transform at which to draw the turtle objects.
   *\param canvas The canvas on which to draw this turtle.*/
  void draw(const Transform &screenTransform, Image &canvas) {
    if (this->screen == nullptr)
      return;

    if (!state->visible)
      return;

    // Draw all lines queued during filling a shape.
    // This is only populated when the turtle moves between a beginfill
    // and endfill while the pen is down.
    for (const Line &line : fillLines)
      line.draw(screenTransform, canvas);

    if (traveling && state->tracing) {
      // Draw the "Travel-Line" when in the middle of the travelTo func
      travelPoints[0] = screenTransform(travelPoints[0]);
      travelPoints[1] = screenTransform(travelPoints[1]);
      drawLine(canvas, travelPoints[0].x, travelPoints[0].y, travelPoints[1].x,
               travelPoints[1].y, state->penColor, state->penWidth);
    }

    // Add the extra rotate to start cursor facing right :)
    const float cursorRot =
        this->screen->mode() == SM_STANDARD ? 1.5708f : -3.1416f;
    Transform cursorTransform = screenTransform.copyConcatenate(*transform)
                                    .rotate(cursorRot + state->cursorTilt);
    state->cursor->fillColor = state->fillColor;
    state->cursor->outlineWidth = 1;
    state->cursor->outlineColor = state->penColor;
    state->cursor->draw(cursorTransform, canvas);
  }

  /**Sets this turtle to use angles measured in degrees.
   *\sa radians()*/
  void degrees() {
    pushState();
    state->angleMode = false;
  }

  /**Sets this turtle to use angles measured in radians.
   *\sa degress()*/
  inline void radians() {
    pushState();
    state->angleMode = true;
  }

  /**\brief Resets this turtle.
   * Moves this turtle home, resets all pen attributes,
   * and removes all previously added scene objects.*/
  void reset() {
    // Reset objects, transforms, trace lines, state, etc.

    // Note to self, clearing the list, appending a new transform,
    // then reassigning the transform reference just didn't want to work.
    // I have no idea why. Therefore, we're resetting it in the same
    // manner we initially construct it.
    stateStack = {PenState()};
    state = &stateStack.back();

    transform = &state->transform;
    const auto numItems = objects.size();

    if (screen != nullptr) {
      // Re-assign cursor on reset, derived from parent screen.
      state->cursor.reset(screen->shape("indented triangle").copy());
      // Erase all objects
      while (!objects.empty()) {
        screen->getScene().erase(objects.front());
        objects.pop_front();
      }

      // Alter cursor tilt and default transform
      // when operating under SM_LOGO mode.
      // This is to bring it up-to-par with Python's
      // implementation of screen modes.
      if (screen->mode() == SM_LOGO) {
        state->cursorTilt = (-1.5708f);
        transform->rotate(1.5708f);
      }
    }

    updateParent(numItems > 0, false);
  }

  /**\brief Sets this turtles screen.*/
  void setScreen(AbstractTurtleScreen *scr) { screen = scr; }

  /**\brief Empty virtual destructor.*/
  virtual ~Turtle() {
    // remove itself from its parent screen...
    if (screen != nullptr)
      screen->remove(*this);
  }

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
  void pushState() {
    if (stateStack.size() + 1 > undoStackSize)
      stateStack.pop_front();

    stateStack.push_back(
        stateStack.back()); // Push a copy of the back-most pen state.
    state = &stateStack.back();
    transform = &state->transform;
    state->objectsBefore = objects.size();
  }

  /*Pops the top of the pen's state stack.*/
  bool popState() {
    if (stateStack.size() == 1)
      return false;
    stateStack.pop_back();
    state = &stateStack.back();
    transform = &state->transform;
    return true;
  }

  /**
   * \brief Internal function used to add geometry to the turtle screen.
   * \param t The transform of the geometry.
   * \param color The color of the geometry.
   * \param geom The geometry to add.
   * \return A boolean indicating if the geometry was added to the scene.
   */
  bool pushGeometry(const Transform &t, AbstractDrawableObject *geom) {
    if (screen != nullptr) {
      pushState();
      screen->getScene().emplace_back(geom, t);
      objects.push_back(std::prev(screen->getScene().end()));
      return true;
    }
    return false;
  }

  /**\brief Internal function used to add a stamp object to the turtle screen.
   *\param t The transform at which to draw the stamp.
   *\param color The color with which to draw the stamp.
   *\param geom The geometry of the stamp.*/
  bool pushStamp(const Transform &t, AbstractDrawableObject *geom) {
    if (screen != nullptr) {
      pushState();
      const float cursorRot =
          this->screen->mode() == SM_STANDARD ? 1.5708f : -3.1416f;

      Transform trans(t);
      trans.rotate(cursorRot + state->cursorTilt);

      geom->outlineWidth = 1;
      geom->outlineColor = state->penColor;

      screen->getScene().emplace_back(geom, trans, state->curStamp++);
      SceneObject &obj = screen->getScene().back();

      objects.push_back(std::prev(screen->getScene().end()));
      return true;
    }
    return false;
  }

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
                TextAlign alignment = TEXT_ALIGN_LEFT) {
    if (screen != nullptr) {
      pushState();
      screen->getScene().emplace_back(
          new Text(text, font, color, scale, alignment), t);
      objects.push_back(std::prev(screen->getScene().end()));
      return true;
    }
    return false;
  }

  /**\brief Internal function used to add a trace line object to the turtle
   * screen. Trace lines do NOT push a state. Their state is encompassed by
   * movement, and these lines are only added when moving the turtle while the
   * pen is down.
   *\param a Point A
   *\param b Point B*/
  bool pushTraceLine(Point a, Point b) {
    if (screen != nullptr) {
      screen->getScene().emplace_back(
          new Line(a, b, state->penColor, state->penWidth), Transform());
      objects.push_back(std::prev(screen->getScene().end()));
      // Trace lines do NOT push a state->
      // Their state is encompassed by movement,
      // and these lines are only added when moving the turtle
      // while the pen is down.
      return true;
    }
    return false;
  }

  /**Returns the speed, of any applicable animation
    in milliseconds, based off of this turtle's speed setting.*/
  long int getAnimMS() {
    if (screen == nullptr)
      return 0;

    // 300 is the "scale" animations adhere to.
    // The longest animation is 300 milliseconds, shortest is 0.
    // This was an arbitrary choice, trying to match the speed of the Python
    // implementation.
    if (!screen->supports_live_animation() || state->moveSpeed < 0)
      return 0; // no animation means no time spent animating...
    return long((state->moveSpeed / 10.0f) * 300); //<----
  }

  /**Conditionally calls the parent screen's update function.*/
  void updateParent(bool invalidate = false, bool input = true) {
    if (screen != nullptr)
      screen->update(invalidate, input);
  }

  /**Performs an interpolation, with animation,
   * between the source transform and the destination transform.
   * May push a new fill vertex if filling and pushing state, and applies
   * appropriate lines if the pen is down. Generally manages all state related
   * to movement as a side effect.*/
  void travelBetween(Transform src, const Transform &dest, bool doPushState) {
    if (dest == src)
      return;

    // Set the "traveling" state for screen drawing. Indicates when to draw
    // travel lines (e.g, when pen is down).
    traveling = true;

    const auto duration = static_cast<float>(getAnimMS());
    if ((screen ? !screen->isclosed() : false) &&
        duration > 0) { // no point in animating with no screen
      const unsigned long startTime = detail::epochTime();

      float progress = 0;
      while (progress < 1.0f) {
        const unsigned long curTime = detail::epochTime();

        transform->assign(src.lerp(dest, progress));
        travelPoints[0] = src.getTranslation();
        travelPoints[1] = transform->getTranslation();

        updateParent(false, false);

        progress = (static_cast<float>(curTime - startTime) / duration);
      }
    }

    if (doPushState) {
      if (state->tracing && !state->filling) {
        pushTraceLine(src.getTranslation(), dest.getTranslation());
      } else if (state->filling) {
        fillAccum.points.push_back(dest.getTranslation());
        if (state->tracing) {
          fillLines.emplace_back(src.getTranslation(), dest.getTranslation(),
                                 state->penColor, state->penWidth);
        }
      }

      transform->assign(src);
      pushState();
    }

    transform->assign(dest);
    traveling = false;
    updateParent(false, false);
  }

  /**Performs an interpolation, with animation,
   * between the current transform and the specified one.
   * Pushes a new fill vertex if filling, and applies appropriate
   * lines if the pen is down. Does push the state stack.*/
  void travelTo(const Transform &dest) {
    travelBetween(*transform, dest, true);
  }

  /**Performs an interpolation, with animation,
   * between the current transformation and the previous one.
   * Will *not* push the state stack.
   * ENSURE STATE STACK IS BIG ENOUGH TO DO THIS BEFORE CALLING.*/
  void travelBack() {
    travelBetween(*transform, std::prev(stateStack.end(), 2)->transform, false);
  }

  /**Inheritors must assign screen pointer!*/
  Turtle() = default;
};

#ifdef CTURTLE_HEADLESS
/*Used to output Base-64 GIF and HTML source for OfflineTurtleScreen.*/
inline std::string encodeFileBase64(const std::string &path) {
  std::ifstream file(path, std::ios::binary | std::ios::ate);
  std::streamsize size = file.tellg();
  file.seekg(0, std::ios::beg);

  std::vector<unsigned char> buffer(size, 0);
  file.read((char *)buffer.data(), size);
  return base64::encode(buffer);
}

class OfflineTurtleScreen : public AbstractTurtleScreen {
public:
  OfflineTurtleScreen() {
    const int width = CTURTLE_HEADLESS_WIDTH;
    const int height = CTURTLE_HEADLESS_HEIGHT;
    canvas.assign(width, height, 1, 3);
    canvas.fill(255);
    isClosed = false;
    gif = jo_gif_start(CTURTLE_HEADLESS_SAVEDIR, width, height, 1, 31);
    redraw(true);
  }

  ~OfflineTurtleScreen() { bye(); }

  void tracer(int countmax, unsigned int delayMS = 10) {
    redrawCounterMax = countmax;
    delay(delayMS);
    redraw();
  }

  int window_width() const { return canvas.width(); }

  int window_height() const { return canvas.height(); }

  Color bgcolor() const { return backgroundColor; }

  void bgcolor(const Color &c) {
    backgroundColor = c;
    redraw(true);
  }

  void mode(ScreenMode mode) {
    // Resets & re-orients all turtles.

    curMode = mode;
    for (Turtle *t : turtles) {
      t->reset();
    }
  }

  ScreenMode mode() const { return curMode; }

  void clearscreen() {
    // 1) Delete all drawings and turtles
    // 2) White background

    for (Turtle *turtle : turtles) {
      turtle->setScreen(nullptr);
    }

    turtles.clear();
    backgroundColor = Color("white");
    curMode = SM_STANDARD;
  }

  void resetscreen() {
    for (Turtle *turtle : turtles)
      turtle->reset();
  }

  ivec2 screensize(Color &bg) {
    bg = backgroundColor;
    return {canvas.width(), canvas.height()};
  };
  // code-smell from python->c++, considering separation of functionality

  ivec2 screensize() { return {canvas.width(), canvas.height()}; }

  void update(bool invalidateDraw = false, bool processInput = false) {
    redraw(invalidateDraw);
    // processInput is ignored. OfflineTurtleScreen does NOT support input.
  }

  void delay(unsigned int ms) { delayMS = ms; }

  unsigned int delay() const { return delayMS; }

  void bye() {
    if (isClosed)
      return;

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

  Image &getcanvas() { return canvas; }

  bool isclosed() { return isClosed; }

  bool supports_live_animation() const { return false; }

  virtual void redraw(bool invalidate = false) {
    if (isclosed())
      return;
    int fromBack = 0;
    bool hasInvalidated = invalidate;

    // Handle resizes.

    if (lastTotalObjects <= objects.size()) {
      fromBack = static_cast<int>(objects.size() - lastTotalObjects);
    }

    if (hasInvalidated) {
      canvas.draw_rectangle(0, 0, canvas.width(), canvas.height(),
                            backgroundColor.rgbPtr());
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

    auto latestIter =
        !hasInvalidated ? std::prev(objects.end(), fromBack) : objects.begin();

    Transform screen = screentransform();
    while (latestIter != objects.end()) {
      SceneObject &object = *latestIter;
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

    for (Turtle *turt : turtles)
      turt->draw(screen, turtleComposite);

    lastTotalObjects = static_cast<int>(objects.size());

    /* The following code takes the place of swapping the display buffer for the
     * canvas, which is what the interactive mode does.*/

    // This copy is NOT efficient.
    // We should be able to take advantage of loop unrolling here
    for (int x = 0; x < CTURTLE_HEADLESS_WIDTH; x++) {
      for (int y = 0; y < CTURTLE_HEADLESS_HEIGHT; y++) {
        uint8_t *pixel =
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

  Transform screentransform() const {
    return Transform()
        .translate(canvas.width() / 2, canvas.height() / 2)
        .scale(1, -1.0f);
  }

  void add(Turtle &turtle) { turtles.push_back(&turtle); }

  void remove(Turtle &turtle) {
    turtle.reset();
    turtle.setScreen(nullptr);
    turtles.remove(&turtle);
  }

  std::list<SceneObject> &getScene() { return objects; }

  AbstractDrawableObject &shape(const std::string &name) {
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
  const BitmapFont &font(const std::string &name) const { return *defaultFont; }

private:
  /*this can be a constant allocated buffer.*/
  uint8_t gifWriteBuffer[CTURTLE_HEADLESS_WIDTH * CTURTLE_HEADLESS_HEIGHT * 4];
  // allocate enough to hold width*height*4 (4 because RGBA).
  // this fits into uint32_t type quite nicely. (8+8+8+8 bits, r+g+b+a) = 32

  // This struct controls the writing of resulting GIFs.
  jo_gif_t gif;

  std::list<SceneObject> objects;
  std::list<Turtle *> turtles;

  bool isClosed = true;
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

  // OfflineTurtleScreen has no background image.

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

  std::unique_ptr<BitmapFont> defaultFont = std::unique_ptr<BitmapFont>(
      new BitmapFont(decodeDefaultFont(), DEFAULT_FONT_ASCII_OFFSET,
                     DEFAULT_FONT_GLYPH_WIDTH, DEFAULT_FONT_GLYPH_HEIGHT,
                     DEFAULT_FONT_GLYPHS_X, DEFAULT_FONT_GLYPHS_Y));
};

typedef OfflineTurtleScreen TurtleScreen;
#else  /*NOT DEFINED CTURTLE_HEADLESS*/
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
  InteractiveTurtleScreen()
      : display(SCREEN_DEFAULT_WIDTH, SCREEN_DEFAULT_HEIGHT,
                SCREEN_DEFAULT_TITLE, 0) {
    canvas.assign(display);
    initEventThread();
    redraw(true);
    fonts[DEFAULT_FONT] = std::unique_ptr<BitmapFont>(
        new BitmapFont(decodeDefaultFont(), DEFAULT_FONT_ASCII_OFFSET,
                       DEFAULT_FONT_GLYPH_WIDTH, DEFAULT_FONT_GLYPH_HEIGHT,
                       DEFAULT_FONT_GLYPHS_X, DEFAULT_FONT_GLYPHS_Y));
  }

  /**Title constructor.
   * Assigns an 800 x 600 pixel display with a specified title.
   *\param title The title to assign the display with.*/
  explicit InteractiveTurtleScreen(const std::string &title)
      : display(SCREEN_DEFAULT_WIDTH, SCREEN_DEFAULT_HEIGHT, title.c_str(), 0) {
    canvas.assign(display);
    initEventThread();
    redraw(true);

    fonts[DEFAULT_FONT] = std::unique_ptr<BitmapFont>(
        new BitmapFont(decodeDefaultFont(), DEFAULT_FONT_ASCII_OFFSET,
                       DEFAULT_FONT_GLYPH_WIDTH, DEFAULT_FONT_GLYPH_HEIGHT,
                       DEFAULT_FONT_GLYPHS_X, DEFAULT_FONT_GLYPHS_Y));
  }

  /**Width, height, and title constructor.
   * Assigns the display with the specified dimensions, in pixels, and
   * assigns the display the specified title.
   *\param width The width of the display, in pixels.
   *\param height The height of the display, in pixels.
   *\param title The title of the display.*/
  InteractiveTurtleScreen(int width, int height,
                          const std::string &title = SCREEN_DEFAULT_TITLE)
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

  /**Destructor. Calls "bye" function.*/
  ~InteractiveTurtleScreen() { bye(); }

  /**Sets an internal variable that dictates how many frames
   * are skipped between screen updates; higher numbers will
   * speed up complex turtle drawings. Setting it to ZERO will
   * COMPLETELY disable animation until this value changes.
   *\param countmax The value of the aforementioned variable.
   *\param delayMS This value is sent to function "delay".*/
  void tracer(int countmax, unsigned int delayMS) override {
    redrawCounterMax = countmax;
    delay(delayMS);
    redraw(false);
  }

  /**Sets the background color of the screen.
   * Please note that, if there is a background image, this color is not
   * applied until it is removed.
   *\param color The background color.
   *\sa bgpic(image)*/
  void bgcolor(const Color &color) override {
    backgroundColor = color;
    redraw(true);
  }

  /**Returns the background color of the screen.
   *\return The background color of the screen.*/
  Color bgcolor() const override { return backgroundColor; }

  /**\brief Sets the background image of the display.
   * Sets the background image. Please note that the background image
   * takes precedence over background color.
   *\param img The background image.*/
  void bgpic(const Image &img) {
    backgroundImage.assign(img);
    backgroundImage.resize(window_width(), window_height());
    redraw(true);
  }

  /**Returns a const reference to the background image.*/
  const Image &bgpic() { return backgroundImage; }

  bool supports_live_animation() const override { return true; }

  /**Sets the screen mode of this screen.
   * Screen mode influences the initial heading added Turtles have,
   * as well as the direction of rotations.
   * This function brings ALL attached turtles to the home/default location.
   *\param mode The screen mode.
   */
  void mode(ScreenMode mode) override {
    curMode = mode;
    for (Turtle *t : turtles)
      t->home();
  }

  /**Returns the screen mode of this screen.*/
  ScreenMode mode() const override { return curMode; }

  /**\brief Clears this screen.
   * Deletes all drawings and turtles,
   * Resets the background to plain white,
   * Clears all event bindings,
   */
  void clearscreen() override {
    // 1) Delete all drawings and turtles
    // 2) White background
    // 3) No background image
    // 4) No event bindings

    while (!turtles.empty())
      remove(*turtles.front());

    turtles.clear();
    backgroundColor = Color("white");
    backgroundImage.assign(); // assign with no parameters is deleting whatever
                              // contents it may have.
    curMode = SM_STANDARD;

    // Gotta do binding alterations under the cache's mutex lock.
    eventCacheMutex.lock();
    timerBindings.clear();
    keyBindings[0].clear();
    keyBindings[1].clear();
    for (auto &mouseBinding : mouseBindings)
      mouseBinding.clear();
    eventCacheMutex.unlock();
  }

  /**Resets all turtles belonging to this screen to their original state->*/
  void resetscreen() override {
    for (Turtle *turtle : turtles)
      turtle->reset();
  }

  /**Returns the size of this screen, in pixels.
    Also returns the background color of the screen,
    by assigning the input reference.*/ //code-smell from python->c++, considering separation of functionality
  inline ivec2 screensize(Color &bg) override {
    bg = backgroundColor;
    return {display.width(), display.height()};
  }

  /**Returns the size of the screen, in pixels.*/
  inline ivec2 screensize() override { // see line above comment about
                                       // code-smell
    return {display.width(), display.height()};
  }

  /**Updates the screen's graphics and input.
   *\param invalidateDraw Completely redraws the scene if true.
   *                      If false, only draws the newest geometry.
   *\param processInput A boolean indicating to process input.*/
  void update(bool invalidateDraw, bool processInput) override {
    /*Resize canvas when necessary.*/
    if (display.is_resized()) {
      display.resize();
      invalidateDraw = true;
    }
    redraw(invalidateDraw);

    if (processInput && !timerBindings.empty()) {
      // Call timer bindings first.
      uint64_t curTime = detail::epochTime();
      for (auto &timer : timerBindings) {
        auto &func = std::get<0>(timer);
        uint64_t reqTime = std::get<1>(timer);
        uint64_t &lastCalled = std::get<2>(timer);

        if (curTime >= lastCalled + reqTime) {
          lastCalled = curTime;
          func();
        }
      }
    }

    /**No events to process in the cache, or we're not processing it right
     * now.*/
    if (cachedEvents.empty() || !processInput)
      return; // No events to process.

    // lock event cache to avoid race conditions
    eventCacheMutex.lock();

    for (InputEvent &event : cachedEvents) {
      if (event.type) { // process keyboard event
        KeyFunc &keyFunc = *reinterpret_cast<KeyFunc *>(event.cbPointer);
        keyFunc();
      } else { // process mouse event
        MouseFunc &mFunc = *reinterpret_cast<MouseFunc *>(event.cbPointer);
        mFunc(event.mX, event.mY);
      }
    }

    cachedEvents.clear();
    eventCacheMutex.unlock();
  }

  /**Sets the delay set between turtle commands.*/
  void delay(unsigned int ms) override { delayMS = ms; }

  /**Returns the delay set between screen swaps in milliseconds.*/
  unsigned int delay() const override { return delayMS; }

  /**Returns the width of the window, in pixels.*/
  int window_width() const override { return display.window_width(); }

  /**Returns the height of the window, in pixels.*/
  int window_height() const override { return display.window_height(); }

  /**Saves the display as a file, the format of which is dependent
    on the file extension given in the specified file path string.*/
  void save(const std::string &file) {
    Image screenshotImg;
    display.snapshot(screenshotImg);
    screenshotImg.save(file.c_str());
  }

  /**Enters a loop, lasting until the display has been closed,
   * which updates the screen. This is useful for programs which
   * rely heavily on user input, as events are still called like normal.*/
  void mainloop() {
    while (!display.is_closed()) {
      update(false, true);
      std::this_thread::yield(); // Yield repetitive loops on mainloop to avoid
                                 // high-cpu usage.
    }
  }

  /**Resets and closes this display.*/
  void bye() override {
    if (redrawCounter > 0 || redrawCounter >= redrawCounterMax) {
      tracer(1, delayMS);
    }

    if (eventThread != nullptr) {
      killEventThread = true;
      eventThread->join();
      eventThread.reset(nullptr);
    }

    clearscreen();

    if (!display.is_closed())
      display.close();
  }

  /**Returns the canvas image used by this screen.*/
  Image &getcanvas() override { return canvas; }

  /**Returns the internal CImg display.*/
  cimg_library::CImgDisplay &internaldisplay() { return display; }

  /**Returns a boolean indicating if the
    screen has been closed.*/
  inline bool isclosed() override { return internaldisplay().is_closed(); }

  /**Draws all geometry from all child turtles and swaps this display.*/
  void redraw(bool invalidate) override {
    if (isclosed())
      return;
    int fromBack = 0;
    bool hasInvalidated = invalidate;

    // Handle resizes.
    if (display.window_width() != canvas.width() ||
        display.window_height() != canvas.height()) {
      canvas.resize(display);
      hasInvalidated = true;
    }

    if (lastTotalObjects <= objects.size()) {
      fromBack = static_cast<int>(objects.size() - lastTotalObjects);
    }

    if (hasInvalidated) {
      if (!backgroundImage.is_empty()) {
        const int centerX =
            (canvas.width() / 2) - (backgroundImage.width() / 2);
        const int centerY =
            (canvas.height() / 2) - (backgroundImage.height() / 2);
        canvas.draw_image(centerX, centerY, backgroundImage);
      } else
        canvas.draw_rectangle(0, 0, canvas.width(), canvas.height(),
                              backgroundColor.rgbPtr());

      redrawCounter = 0; // Forced redraw due to canvas invalidation.
    } else {
      if (redrawCounterMax ==
          0) // tracer settings may disable rendering for a short time...
        return;
      redrawCounter++;

      if (redrawCounter >= redrawCounterMax)
        redrawCounter = 0;
      else
        return;
    }

    // get the iterator pointing to the oldest scene object that hasn't been
    // drawn yet if the scene has been invalidated, the latest object is the
    // first one in the scene. otherwise,
    auto latestIter =
        !hasInvalidated ? std::prev(objects.end(), fromBack) : objects.begin();

    const Transform screen = screentransform();
    while (latestIter != objects.end()) {
      SceneObject &object = *latestIter;
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

    for (Turtle *turt : turtles)
      turt->draw(screen, turtleComposite);

    lastTotalObjects = static_cast<int>(objects.size());
    display.display(turtleComposite);
    detail::sleep(delayMS);
  }

  /**Returns the screen-level Transform
    of this screen. This is what puts the origin
    at the center of the screen rather than at
    at the top left, for example.*/
  Transform screentransform() const override {
    // Scale negatively on Y axis to match
    // Python's coordinate system.
    // without this scaling, top left is 0,0
    // instead of the bottom left (which is 0,Y without the scaling)
    return Transform()
        .translate(canvas.width() / 2, canvas.height() / 2)
        .scale(1, -1.0f);
  }

  /**\brief Adds an additional "on press" key binding for the specified key.
   *\param func The function to call when the specified key is pressed.
   *\param key The specified key.*/
  void onkeypress(const KeyFunc &func, KeyboardKey key) {
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
  virtual void onkeyrelease(const KeyFunc &func, KeyboardKey key) {
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
  void presskey(KeyboardKey key) {
    if (keyBindings[0].find(key) == keyBindings[0].end())
      return;
    for (const KeyFunc &func : keyBindings[0][key]) {
      func();
    }
  }

  /**\brief Simulates a key "on release" event.
   *\param key The key to call "on release" bindings for.*/
  void releasekey(KeyboardKey key) {
    if (keyBindings[1].find(key) == keyBindings[1].end())
      return;
    for (KeyFunc &func : keyBindings[1][key]) {
      func();
    }
  }

  /**\brief Adds an additional "on click" mouse binding for the specified
   * button.
   *\param func The function to call when the specified button is clicked.
   *\param button The specified button.*/
  void onclick(const MouseFunc &func, MouseButton button = MOUSEB_LEFT) {
    eventCacheMutex.lock();
    mouseBindings[button].push_back(func);
    eventCacheMutex.unlock();
  }

  /**Calls all previously added mouse button call-backs.
   *\param x The X coordinate at which to press.
   *\param y The Y coordinate at which to press.
   *\param button The button to simulate being pressed.*/
  void click(int x, int y, MouseButton button) {
    eventCacheMutex.lock();
    for (MouseFunc &func : mouseBindings[button]) {
      func(x, y);
    }
    eventCacheMutex.unlock();
  }

  /**\copydoc click(int, int, MouseButton)*/
  inline void click(const Point &pt, MouseButton button) {
    click(pt.x, pt.y, button);
  }

  /**\brief Adds a timer function to be called every N milliseconds.
   *\param func The function to call when the timer has finished.
   *\param time The total number of milliseconds between calls.*/
  void ontimer(const TimerFunc &func, unsigned int time) {
    timerBindings.emplace_back(
        std::make_tuple(func, time, detail::epochTime()));
  }

  /**Binds the "bye" function to the onclick event for the left
   * mouse button.*/
  void exitonclick() {
    // Catch up visually before entering event loop, when necessary.
    if (redrawCounter > 0 || redrawCounter >= redrawCounterMax) {
      tracer(1, delayMS);
    }

    onclick([&](int x, int y) { display.close(); });
    mainloop();
  }

  /**Adds the specified turtle to this screen.*/
  void add(Turtle &turtle) override { turtles.push_back(&turtle); }

  /**
   * @brief Removes the specified turtle from this screen.
   * @param turtle
   */
  void remove(Turtle &turtle) override {
    turtle.reset();
    turtle.setScreen(nullptr);
    turtles.remove(&turtle);
  }

  /**Returns a reference to the list of scene objects.
   * This list is used to redraw the screen.*/
  std::list<SceneObject> &getScene() override { return objects; }

  /**
   * Returns the shape associated with the specified name.
   * @param name
   * @return
   */
  AbstractDrawableObject &shape(const std::string &name) override {
    return shapes[name];
  }

  /**
   * Adds the specified bitmap font to the screen.
   * It can be referenced later by its given name.
   * @param name the name given to the font.
   * @param font to add to the screen.
   */
  void addfont(const std::string &name, const BitmapFont &font) {
    fonts[name] = std::unique_ptr<BitmapFont>(new BitmapFont(font));
  }

  /**
   * Returns a read-only reference to the bitmap font with the specified name.
   * @param name to be given to the font.
   * @return read-only BitmapFont reference.
   */
  const BitmapFont &font(const std::string &name) const override {
    return *fonts.at(name);
  }

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
  void initEventThread() {
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
            static_cast<bool>(button & 1), // left
            static_cast<bool>(button & 2), // right
            static_cast<bool>(button & 4)  // middle
        };

        for (int i = 0; i < 3; i++) {
          if (!(!mButtons[i] && buttons[i])) // is this button state "down"?
            continue; // if not, skip its processing loop.

          for (MouseFunc &func : mouseBindings[i]) {
            // append to the event cache.
            InputEvent e;
            e.type = false;
            e.mX = mousePos.x;
            e.mY = mousePos.y;
            e.cbPointer = reinterpret_cast<void *>(&func);
            cachedEvents.push_back(e);
          }
        }

        const auto &keys = NAMED_KEYS;

        // iterate through every key to determine its state,
        // then call the appropriate callbacks.
        for (const auto &keyPair : keys) {
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
          } else
            continue; // skip on case where it was down and is down

          try {
            // will throw if no bindings available for key,
            // and that's perfectly fine, so we just silently catch
            auto &bindingList = keyBindings[state][key];
            for (auto &cb : bindingList) {
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

  /**The scene list.*/
  std::list<SceneObject> objects;

  /**The list of attached turtles.*/
  std::list<Turtle *> turtles;

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
  std::unordered_map<KeyboardKey, std::list<KeyFunc>> keyBindings[2] = {{}, {}};
  // similar, mouseb_left mouseb_middle mouseb_right bindings.
  std::list<MouseFunc> mouseBindings[3] = {{}, {}, {}};
  // timer bindings, one function per originating time and delta.
  std::list<std::tuple<TimerFunc, uint64_t, uint64_t>> timerBindings;

  // map of fonts. only "default" is initially populated.
  std::unordered_map<std::string, std::unique_ptr<BitmapFont>> fonts;
};

typedef InteractiveTurtleScreen TurtleScreen;
#endif /*CTURTLE_HEADLESS*/

} // namespace cturtle
