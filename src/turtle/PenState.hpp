#pragma once
#include "../geometry/Transform.hpp"
#include "../objects/AbstractDrawableObject.hpp"
#include "TurtleSpeed.hpp"
namespace cturtle {
/**\brief The Pen State structure Holds all pen attributes, which are grouped in
 * this way to allow stack-based undo for Turtle objects. Instances of this
 * object are self-contained, and has ownership of all objects and memory
 * referenced by itself.*/
struct PenState {
  /**The transform of the pen.
   * holds position, rotation, and scale of the turtle.*/
  Transform transform;
  /**The movement speed of the turtle, in range of 0...10*/
  float moveSpeed = TS_NORMAL;
  /**Whether or not the turtle's "tail" (or pen) is down.*/
  bool tracing = true;
  /**The angle mode. False for degrees, true for radians.*/
  bool angleMode = false;
  /**The width of the pen, in pixels.*/
  int penWidth = 1;
  /**A boolean indicating if we're trying to fill a shape.*/
  bool filling = false;
  /**The color of the pen.*/
  Color penColor = Color("black");
  /**The intended fill color.*/
  Color fillColor = Color("black");
  /**The total number of objects in the screen's object stack
   * prior to the addition of this state->*/
  size_t objectsBefore = 0;
  /**The turtle's cursor geometry. MUST ASSIGN BEFORE USE.*/
  std::unique_ptr<AbstractDrawableObject> cursor = nullptr;
  /**The current stamp ID.*/
  int curStamp = 0;
  /**A boolean indicating if this turtle is visible.*/
  bool visible = true;
  /**A float for cursor tilt (e.g, rotation appleid to the cursor itself)*/
  float cursorTilt = 0;

  PenState() = default;
  PenState(const PenState &copy) {
    transform = copy.transform;
    moveSpeed = copy.moveSpeed;
    tracing = copy.tracing;
    angleMode = copy.angleMode;
    penWidth = copy.penWidth;
    filling = copy.filling;
    penColor = copy.penColor;
    fillColor = copy.fillColor;
    cursor.reset(copy.cursor ? copy.cursor->copy() : nullptr);
    curStamp = copy.curStamp;
    visible = copy.visible;
    cursorTilt = copy.cursorTilt;
    objectsBefore = copy.objectsBefore;
  }

  PenState &operator=(const PenState &copy) {
    transform = copy.transform;
    moveSpeed = copy.moveSpeed;
    tracing = copy.tracing;
    angleMode = copy.angleMode;
    penWidth = copy.penWidth;
    filling = copy.filling;
    penColor = copy.penColor;
    fillColor = copy.fillColor;
    cursor.reset(copy.cursor ? copy.cursor->copy() : nullptr);
    curStamp = copy.curStamp;
    visible = copy.visible;
    cursorTilt = copy.cursorTilt;
    objectsBefore = copy.objectsBefore;
    return *this;
  }
};
} // namespace cturtle
