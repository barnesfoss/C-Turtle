#include "CTurtle/objects/Polygon.hpp"
namespace cturtle {
Polygon::Polygon(const std::initializer_list<Point> &init) : points(init) {
  this->outlineWidth = outlineWidth;
  this->outlineColor = outlineColor;
  this->fillColor = fillColor;
}

Polygon::Polygon(std::vector<Point> copy, const Color &fillColor,
                 int outlineWidth, const Color &outlineColor)
    : points(std::move(copy)) {
  this->outlineWidth = outlineWidth;
  this->outlineColor = outlineColor;
  this->fillColor = fillColor;
}

AbstractDrawableObject *Polygon::copy() const { return new Polygon(*this); }

void Polygon::draw(const Transform &t, Image &imgRef) const {
  if (points.empty())
    return;
  /*CImg requires all polygons to be passed in as an instance of
    the image object. Therefore, we can specify an "int" image with
    a width of 2 (x,y) and height of the total number of
    elements in the point vector.*/
  cimg_library::CImg<int> passPts(static_cast<int>(points.size()), 2);

  for (size_t i = 0; i < points.size(); i++) {
    const Point pt = t(points[i]);
    passPts(i, 0) = pt.x;
    passPts(i, 1) = pt.y;
  }

  imgRef.draw_polygon(passPts, fillColor.rgbPtr());

  if (outlineWidth > 0) { // draw outline using previously generated points.
    // LineLoop impl
    for (size_t i = 1; i < points.size(); i++) {
      drawLine(imgRef, passPts(i - 1, 0), passPts(i - 1, 1), passPts(i, 0),
               passPts(i, 1), outlineColor, outlineWidth);
    }
    // draw last line between first and last
    drawLine(imgRef, passPts(int(points.size()) - 1, 0),
             passPts(int(points.size()) - 1, 1), passPts(0, 0), passPts(0, 1),
             outlineColor, outlineWidth);
  }
}

} // namespace cturtle
