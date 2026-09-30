#include "CTurtle/objects/Line.hpp"
namespace cturtle {
Line::Line(Point a, Point b, const Color &color, int width)
    : pointA(a), pointB(b), width(width) {
  fillColor = color;
}

void Line::draw(const Transform &t, Image &imgRef) const {
  const Point a = t(pointA);
  const Point b = t(pointB);
  drawLine(imgRef, a.x, a.y, b.x, b.y, fillColor, width);
}

} // namespace cturtle
