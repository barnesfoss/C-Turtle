// Copyright 2021 Jesse W. Walker
//
// Licensed under the MIT License.
// See LICENSE for details.
#include "CTurtle/objects/Circle.hpp"
namespace cturtle {

Circle::Circle(int radius, int steps, const Color& fillColor, int outlineWidth,
               const Color& outlineColor)
    : radius(radius), steps(steps) {
    this->fillColor = fillColor;
    this->outlineWidth = outlineWidth;
    this->outlineColor = outlineColor;
}

void Circle::draw(const Transform& t, Image& imgRef) const {
    if (steps <= 0) return;  // no step check
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

    if (outlineWidth > 0) {  // draw outline using previously generated points.
        // LineLoop impl
        for (int i = 1; i < steps; i++) {
            drawLine(imgRef, passPts(i - 1, 0), passPts(i - 1, 1),
                     passPts(i, 0), passPts(i, 1), outlineColor, outlineWidth);
        }
        // draw last line between first and last
        drawLine(imgRef, passPts(steps - 1, 0), passPts(steps - 1, 1),
                 passPts(0, 0), passPts(0, 1), outlineColor, outlineWidth);
    }
}

AbstractDrawableObject* Circle::copy() const { return new Circle(*this); }

}  // namespace cturtle
