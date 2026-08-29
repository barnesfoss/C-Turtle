#pragma once
#include "AbstractDrawableObject.hpp"
namespace cturtle {
/**\brief The Line class holds two points and the functionality to draw a line
 *       between them on a specified canvas.*/
class Line : public AbstractDrawableObject {
public:
  /**The "From" point.
     Lines drawn with this object start here.*/
  Point pointA;
  /**The "To" point.
     Lines drawn with this object end here.*/
  Point pointB;

  /**The width of the line, in pixels.*/
  int width = 1;

  /**\brief Empty default constructor.*/
  Line() = default;

  /**\brief Value constructor.
   *        merely assigns value of pointA and pointB to respective A and B.
   *\param a The "From" point.
   *\param b The "To" point.*/
  Line(Point a, Point b, const Color &color, int width = 1)
      : pointA(a), pointB(b), width(width) {
    fillColor = color;
  }

  /**\brief Copy constructor.
   *        Merely assigns the "to" and "from" points.
   *\param other The other instance of a line from which to derive value.*/
  Line(const Line &other) = default;

  AbstractDrawableObject *copy() const override { return new Line(*this); }

  /**\brief Empty de-constructor.*/
  ~Line() override = default;

  void draw(const Transform &t, Image &imgRef) const override {
    const Point a = t(pointA);
    const Point b = t(pointB);
    drawLine(imgRef, a.x, a.y, b.x, b.y, fillColor, width);
  }
};
} // namespace cturtle
