#pragma once
#include "AbstractDrawableObject.hpp"
namespace cturtle {
/**\brief Turtles append Scene Objects to a list to keep
 *              track of what it has drawn (a history).
 * SceneObject holds a description of something that needs to be on the screen.
 * It's a general object which encompasses ALL things that can be on screen,
 * ranging from stamps, misc. geometry, and strings.*/
struct SceneObject {
  /**The unique pointer to the geometry of this object.
   * MUST BE NON-NULL IF THE OBJECT IS IN A TURTLE SCREEN'S SCENE.*/
  std::unique_ptr<AbstractDrawableObject> geom;

  /**The transform at which to draw this SceneObject.
   * Note that this is concatenated onto the ScreenTransform of
   * the drawing turtle's screen.*/
  Transform transform;

  /**A boolean indicating if this scene object is a stamp.*/
  bool stamp = false;
  /**The integer representing the stamp ID, if this is a stamp. Valid stampids >
   * -1*/
  int stampid = -1;

  /**Empty constructor.*/
  SceneObject() = default;

  /**General geometry constructor.
   *\param geom A dynamically allocated pointer to a Geometry object.
   *            Please note that, after this constructor call, the SceneObject
   *            controls the life of the given pointer. Do not delete it
   * yourself.
   *\param color The color to draw the geometry in.
   *\param t The transform at which to draw the geometry.
   *\param stampid The ID of the stamp this object is related to.*/
  SceneObject(AbstractDrawableObject *geom, const Transform &t,
              int stampid = -1)
      : geom(geom), transform(t), stamp(stampid > -1), stampid(stampid) {}
};

} // namespace cturtle
