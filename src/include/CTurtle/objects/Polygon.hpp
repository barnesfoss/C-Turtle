#pragma once
#include "AbstractDrawableObject.hpp"
#include <vector>
namespace cturtle {
/**\brief The polygon class merely holds a vector of points and a function
 *        to draw this series to an image.
 * Please note that the contained series of points must be in either
 * clockwise(CW) or counterclockwise(CCW) order!*/
class Polygon : public AbstractDrawableObject {
public:
  std::vector<Point> points;

  /**\brief Empty default constructor.*/
  Polygon() = default;

  /**\brief   Initializer list instructor which assigns the points
   *          to the contents of the specified initializer list.
   *\param The initializer list from where points are retrieved.*/
  Polygon(const std::initializer_list<Point> &init);

  /**\brief A copy constructor for another vector of points.
   *\param copy A vector from which to derive points.*/
  Polygon(std::vector<Point> copy, const Color &fillColor, int outlineWidth = 0,
          const Color &outlineColor = Color());

  /**\brief A copy constructor for another polygon.
   *\param other Another polygon from which to derive points.*/
  Polygon(const Polygon &other) = default;

  /**
   * Returns a copy of this polygon allocated with the new keyword.
   * Must be deleted at the responsibility of the invoker.
   */
  AbstractDrawableObject *copy() const override;

  /**\brief Empty de-constructor.*/
  ~Polygon() override = default;

  void draw(const Transform &t, Image &imgRef) const override;
};
} // namespace cturtle
