#pragma once
#include "../color.hpp"
#include "../geometry/Transform.hpp"
namespace cturtle {
/**\brief AbstractDrawableObject is a base class, intended to be
 *        inherited from by all drawable objects.
 * This class just contains a simple virtual drawing function,
 * intended to be inherited from and to overload the draw function.
 * This allows for the storage of drawable geometry/etc and attributes in a
 * generic fashion.*/
class AbstractDrawableObject {
public:
  /**The internal fill color of the circle.*/
  Color fillColor;

  /**The outline color of the circle.*/
  Color outlineColor;

  /**The width of the outline of the circle, in pixels.*/
  int outlineWidth = 0;

  /**\brief Empty-- virtual-- default de-constructor.*/
  virtual ~AbstractDrawableObject() = default;

  /**\brief Returns a pointer to a copy of this drawable object, allocated with
   * NEW. Result must be deleted at the responsibility of the invoker.*/
  virtual AbstractDrawableObject *copy() const = 0;

  /**\brief This function is intended to draw all applicable geometry
   *        in this object to the specified image, with the specified transform,
   *        with the specified color.
   * This function is intended to be overloaded by child classes to draw
   * applicable geometry to an image, acting as a canvas.
   * \param t The transform at which to draw the geometry.
   * \param imgRef The canvas on which to draw.
   * \param c The color with to draw the geometry.*/
  virtual void draw(const Transform &t, Image &imgRef) const = 0;

protected:
  /**\brief Empty default constructor.*/
  AbstractDrawableObject() = default;
};

} // namespace cturtle
