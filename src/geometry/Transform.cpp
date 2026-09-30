#include "CTurtle/geometry/Transform.hpp"
#include "CTurtle/geometry/ivec2.hpp"
#include "CTurtle/types/Image.hpp"
#include <math.h>
namespace cturtle {

Transform::Transform() : value() { identity(); }

Transform::Transform(const Transform &other) = default;

Transform::Transform(const ivec2 &point, float rotation) : value() {
  identity();
  setTranslation(point.x, point.y);
  rotate(rotation);
}

Transform &Transform::identity() {
  value.fill(0.0f);
  at(0, 0) = at(1, 1) = 1.0f;
  rotation = 0;
  return *this;
}

bool Transform::operator==(const Transform &other) const {
  bool eq = true;
  for (int i = 0; i < 9; i++) {
    if (value[i] != other.value[i]) {
      eq = false;
      break;
    }
  }
  return eq;
}

float Transform::getScaleX() const { return at(0, 0); }

float Transform::getScaleY() const { return at(1, 1); }

float Transform::getTranslateX() const { return at(0, 2); }

float Transform::getTranslateY() const { return at(1, 2); }

float Transform::getRotation() const { return rotation; }

Transform &Transform::forward(float distance) {
  at(0, 2) += std::cos(rotation) * distance; // x component
  at(1, 2) += std::sin(rotation) * distance; // y component
  return *this;
}

Transform &Transform::backward(float distance) { return forward(-distance); }

Transform &Transform::setTranslation(int x, int y) {
  at(0, 2) = static_cast<float>(x);
  at(1, 2) = static_cast<float>(y);
  return *this;
}

Point Transform::getTranslation() const {
  return {(int)std::round(at(0, 2)), (int)std::round(at(1, 2))};
}

Transform &Transform::setTranslationX(int x) {
  at(0, 2) = static_cast<float>(x);
  return *this;
}

Transform &Transform::setTranslationY(int y) {
  at(1, 2) = static_cast<float>(y);
  return *this;
}

Transform &Transform::translate(int x, int y) {
  at(0, 2) +=
      static_cast<float>(x) * at(0, 0) + static_cast<float>(y) * at(0, 1);
  at(1, 2) +=
      static_cast<float>(x) * at(1, 0) + static_cast<float>(y) * at(1, 1);
  return *this;
}

Transform &Transform::rotate(float theta) {
  // 6.28319 is a full rotation in radians. (360 degrees)
  constexpr float fullcircle = 6.28319f;

  // Much smarter solution than recursive spinning.
  // Takes the modulus between what would have been the pre-fix result
  // and a full circle, and subtracts the original rotation.
  // This gives pretty accurate rotations rather quickly.
  // No recursive spinning required! :)
  const float origResult = rotation + theta;
  if (origResult > fullcircle || origResult < 0)
    theta = std::fmod(origResult, fullcircle) - rotation;

  const float c = std::cos(theta);
  const float s = std::sin(theta);

  const float new00 = at(0, 0) * c + at(0, 1) * s;
  const float new01 = at(0, 0) * -s + at(0, 1) * c;
  const float new10 = at(1, 0) * c + at(1, 1) * s;
  const float new11 = at(1, 0) * -s + at(1, 1) * c;

  at(0, 0) = new00; // x
  at(0, 1) = new01; // y
  at(1, 0) = new10; // rotX
  at(1, 1) = new11; // rotY

  rotation += theta;

  return *this;
}

Transform &Transform::setRotation(float val) {
  if (val == rotation)
    return *this;
  if (rotation != 0.0f)
    rotate(-rotation);
  rotate(val);
  return *this;
}

Transform &Transform::rotateAround(int x, int y, float theta) {
  translate(x, y);
  rotate(theta);
  translate(-x, -y);
  return *this;
}

Transform &Transform::scale(float sx, float sy) {
  at(0, 0) *= sx;
  at(0, 1) *= sy;
  at(1, 0) *= sx;
  at(1, 1) *= sy;
  return *this;
}

Transform &Transform::concatenate(const Transform &t) {
  const float new00 = at(0, 0) * t.at(0, 0) + at(0, 1) * t.at(1, 0);
  const float new01 = at(0, 0) * t.at(0, 1) + at(0, 1) * t.at(1, 1);
  const float new02 = at(0, 0) * t.at(0, 2) + at(0, 1) * t.at(1, 2) + at(0, 2);
  const float new10 = at(1, 0) * t.at(0, 0) + at(1, 1) * t.at(1, 0);
  const float new11 = at(1, 0) * t.at(0, 1) + at(1, 1) * t.at(1, 1);
  const float new12 = at(1, 0) * t.at(0, 2) + at(1, 1) * t.at(1, 2) + at(1, 2);

  at(0, 0) = new00;
  at(0, 1) = new01;
  at(0, 2) = new02;
  at(1, 0) = new10;
  at(1, 1) = new11;
  at(1, 2) = new12;
  rotation += t.rotation;
  return *this;
}

Transform Transform::copyConcatenate(const Transform &t) const {
  Transform copy;
  copy.assign(*this);
  copy.concatenate(t);
  return copy;
}

Transform Transform::lerp(const Transform &t, float progress) const {
  if (progress <= 0)
    return *this;
  else if (progress >= 1)
    return t;
  Transform result;
  for (int i = 0; i < 9; i++) {
    result.value[i] = (progress * (t.value[i] - value[i])) + value[i];
  }
  return result;
}

void Transform::assign(const Transform &t) {
  value = t.value;
  rotation = t.rotation;
}

Point Transform::transform(Point in, Point *dst) const {
  Point temp;
  Point *dstPtr = (dst == nullptr) ? &temp : dst;

  dstPtr->x =
      static_cast<int>(at(0, 0) * (static_cast<float>(in.x)) +
                       at(0, 1) * (static_cast<float>(in.y)) + at(0, 2));
  dstPtr->y =
      static_cast<int>(at(1, 0) * (static_cast<float>(in.x)) +
                       at(1, 1) * (static_cast<float>(in.y)) + at(1, 2));

  return *dstPtr;
}

template <typename ITER_T>
void Transform::transformSet(ITER_T cur, ITER_T end) const {
  while (cur != end) {
    transform(&(*cur), &(*cur));
    cur++;
  }
}

Point Transform::operator()(Point in) const { return transform(in); }

float &Transform::at(int row, int col) { return value[row * 3 + col]; }

float Transform::at(int row, int col) const { return value[row * 3 + col]; }

void drawLine(Image &imgRef, int x1, int y1, int x2, int y2, const Color &c,
              int width) {
  if (x1 == x2 && y1 == y2)
    return;
  else if (width == 1) {
    // Just use the built-in bresenham line function
    // to draw line with widths of 1.
    imgRef.draw_line(x1, y1, x2, y2, c.rgbPtr());
    return;
  }

  const int radius = width / 2; // integer division, be careful here...
  cimg_library::CImg<int> lineGeom(4, 2);

  // convert line (p1, p2) to polygon (p1,p2,p3,p4)... huzzah, O(1)
  // implementation! start with two transforms (one for each coordinate pair),
  // rotated to face towards one-another, with an added 90-degree rotation
  // (1.571~ ish radians).

  Transform transforms[2] = {
      {{x1, y1},
       std::atan2(static_cast<float>(y2 - y1), static_cast<float>(x2 - x1)) +
           1.57079633f},
      {{x2, y2},
       std::atan2(static_cast<float>(y1 - y2), static_cast<float>(x1 - x2)) +
           1.57079633f}};
  Point temp[2];

  for (int i = 0; i < 2; i++) { // for both of the transforms...
    Transform &trans = transforms[i];

    // move it forward and back, getting the adjacent corners of the polygon
    // line
    trans.forward(static_cast<float>(radius));
    temp[0] = trans.getTranslation();

    trans.backward(static_cast<float>(radius * 2));
    temp[1] = trans.getTranslation();

    // then, using a loop, copy our temporary points to the point image.
    // the first transform (pt a) are indices 0, 1
    // the second transform (pt b) are indices 2, 3
    // this ensures proper cw/ccw vertex ordering.
    for (int j = 0; j < 2; j++) {
      lineGeom((i * 2) + j, 0) = temp[j][0];
      lineGeom((i * 2) + j, 1) = temp[j][1];
    }
  }

  // draw the rounded caps and the fill polygon
  imgRef.draw_circle(x1, y1, radius, c.rgbPtr()); // circle 1
  imgRef.draw_polygon(lineGeom, c.rgbPtr());      // line fill
  imgRef.draw_circle(x2, y2, radius, c.rgbPtr()); // circle 2
}

} // namespace cturtle
