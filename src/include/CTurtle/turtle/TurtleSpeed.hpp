#pragma once
namespace cturtle {
// SECTION: TURTLE & TURTLE SCREEN

/**\brief Describes the speed at which a Turtle moves and rotates.
 * \sa Turtle::getAnimMS()*/
enum TurtleSpeed {
  /**So fast, it disables animation.*/
  TS_FASTEST = 0,
  /**The fastest the turtle can go without disabling animations.*/
  TS_FAST = 10,
  /**The default, normal speed of a turtle.*/
  TS_NORMAL = 6,
  /**A slow speed.*/
  TS_SLOW = 3,
  /**The slowest a turtle can go.*/
  TS_SLOWEST = 1
};
} // namespace cturtle
