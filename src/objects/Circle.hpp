#pragma once
#include "AbstractDrawableObject.hpp"
namespace cturtle {
/**\brief The Circle class holds a radius and total number of steps, used
 *        to generate and draw a circles geometry.*/
class Circle : public AbstractDrawableObject {
public:
  /**Radius, in pixels, of the geometry generated in the draw function.*/
  int radius = 10;
  /**Total number of steps, or vertices, generated in the draw function.
   * The higher this number is, the more "high-quality" it can be considered.*/
  int steps = 10;

  /**\brief Empty constructor.*/
  Circle() = default;

  /**\brief Radius and step assignment constructor.
   *\param radius The radius, in pixels, of this circle.
   *\param steps The number of vertices used by this circle.*/
  Circle(int radius, int steps, const Color &fillColor, int outlineWidth = 0,
         const Color &outlineColor = Color())
      : radius(radius), steps(steps) {
    this->fillColor = fillColor;
    this->outlineWidth = outlineWidth;
    this->outlineColor = outlineColor;
  }

  /**\brief Copy constructor.
   *\param other Another instance of a circle from which to derive value.*/
  Circle(const Circle &other) = default;

  AbstractDrawableObject *copy() const override { return new Circle(*this); }

  void draw(const Transform &t, Image &imgRef) const override {
    if (steps <= 0)
      return; // no step check
    cimg_library::CImg<int> passPts(steps, 2);

    for (int i = 0; i < steps; i++) {
      Point p;
      p.x = int(radius * std::cos(i * (2 * M_PI) / steps));
      p.y = int(radius * std::sin(i * (2 * M_PI) / steps));
      Point tPoint = t(p);
      passPts(i, 0) = tPoint.x;
      passPts(i, 1) = tPoint.y;
    }

    imgRef.draw_polygon(passPts, fillColor.rgbPtr());

    if (outlineWidth > 0) { // draw outline using previously generated points.
      // LineLoop impl
      for (int i = 1; i < steps; i++) {
        drawLine(imgRef, passPts(i - 1, 0), passPts(i - 1, 1), passPts(i, 0),
                 passPts(i, 1), outlineColor, outlineWidth);
      }
      // draw last line between first and last
      drawLine(imgRef, passPts(steps - 1, 0), passPts(steps - 1, 1),
               passPts(0, 0), passPts(0, 1), outlineColor, outlineWidth);
    }
  }
};

} // namespace cturtle
