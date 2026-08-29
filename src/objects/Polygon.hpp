#pragma once
#include "AbstractDrawableObject.hpp"
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
  Polygon(const std::initializer_list<Point> &init) : points(init) {
    this->outlineWidth = outlineWidth;
    this->outlineColor = outlineColor;
    this->fillColor = fillColor;
  }

  /**\brief A copy constructor for another vector of points.
   *\param copy A vector from which to derive points.*/
  Polygon(std::vector<Point> copy, const Color &fillColor, int outlineWidth = 0,
          const Color &outlineColor = Color())
      : points(std::move(copy)) {
    this->outlineWidth = outlineWidth;
    this->outlineColor = outlineColor;
    this->fillColor = fillColor;
  }

  /**\brief A copy constructor for another polygon.
   *\param other Another polygon from which to derive points.*/
  Polygon(const Polygon &other) = default;

  /**
   * Returns a copy of this polygon allocated with the new keyword.
   * Must be deleted at the responsibility of the invoker.
   */
  AbstractDrawableObject *copy() const override { return new Polygon(*this); }

  /**\brief Empty de-constructor.*/
  ~Polygon() override = default;

  void draw(const Transform &t, Image &imgRef) const override {
    if (points.empty())
      return;
    /*CImg requires all polygons to be passed in as an instance of
      the image object. Therefore, we can specify an "int" image with
      a width of 2 (x,y) and height of the total number of
      elements in the point vector.*/
    cimg_library::CImg<int> passPts(static_cast<int>(points.size()), 2);

    for (int i = 0; i < points.size(); i++) {
      const Point pt = t(points[i]);
      passPts(i, 0) = pt.x;
      passPts(i, 1) = pt.y;
    }

    imgRef.draw_polygon(passPts, fillColor.rgbPtr());

    if (outlineWidth > 0) { // draw outline using previously generated points.
      // LineLoop impl
      for (int i = 1; i < points.size(); i++) {
        drawLine(imgRef, passPts(i - 1, 0), passPts(i - 1, 1), passPts(i, 0),
                 passPts(i, 1), outlineColor, outlineWidth);
      }
      // draw last line between first and last
      drawLine(imgRef, passPts(int(points.size()) - 1, 0),
               passPts(int(points.size()) - 1, 1), passPts(0, 0), passPts(0, 1),
               outlineColor, outlineWidth);
    }
  }
};
} // namespace cturtle
