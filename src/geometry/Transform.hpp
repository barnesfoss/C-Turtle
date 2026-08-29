#pragma once
#include "../color.hpp"
#include "../types/Image.hpp"
#include "ivec2.hpp"
#include <array>
#include <math.h>
namespace cturtle {
/**\brief The Transform class provides a myriad of functions to
 *        simply transform points.
 * This class it the backbone of almost all cartesian plane math in CTurtle.
 * An adapted 3x3 matrix of the following link:
 * http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
 */
class Transform {
public:
  /**Constructs an empty transform.
   * Initializes, by default, as an identity transform.*/
  Transform() : value() { identity(); }

  /**\brief Copy constructor.
   *\param other The other transform from which to derive value.*/
  Transform(const Transform &other) = default;

  /**\brief Point and rotattypesconstructor.
   * Initializes a transform with the specified rotation, a translation matching
   * the specified point.
   * \param point The translation of this newly constructed transform.
   * \param rotation The rotation of this newly constructed transform.
   */
  Transform(const ivec2 &point, float rotation) : value() {
    identity();
    setTranslation(point.x, point.y);
    rotate(rotation);
  }

  /**\brief Sets this transform to an identity.
   * When you concatenate an identity transform onto another object,
   * The resulting point is the same as it would have been pre-concatenation.
   * Such is the point of an identity transform, and is why Transforms
   * are initialized to have this value.
   *\return A reference to this transform. (e.g, *this)*/
  Transform &identity() {
    value.fill(0.0f);
    at(0, 0) = at(1, 1) = 1.0f;
    rotation = 0;
    return *this;
  }

  /**\brief Returns a boolean indicating if this transform
   *        is equivalent in value to the one specified.*/
  bool operator==(const Transform &other) const {
    bool eq = true;
    for (int i = 0; i < 9; i++) {
      if (value[i] != other.value[i]) {
        eq = false;
        break;
      }
    }
    return eq;
  }

  /**\brief Returns the X scale of this transform.
   *\return Returns the X scale of this transform.*/
  float getScaleX() const { return at(0, 0); }

  /**\brief Returns the Y scale of this transform.
   *\return Returns the Y scale of this transform.*/
  float getScaleY() const { return at(1, 1); }

  /**\brief Returns the X translation of this transform.
   *\return Returns the X translation of this transform.*/
  float getTranslateX() const { return at(0, 2); }

  /**\brief Returns the Y translation of this transform.
   *\return Returns the Y translation of this transform.*/
  float getTranslateY() const { return at(1, 2); }

  /**\brief Returns rotation of this transform, in radians.
   *\return The rotation of this transform, in radians.*/
  float getRotation() const { return rotation; }

  /**Moves this transform "forward" according to its rotation.*/
  Transform &forward(float distance) {
    at(0, 2) += std::cos(rotation) * distance; // x component
    at(1, 2) += std::sin(rotation) * distance; // y component
    return *this;
  }

  /*Backwards inline function.
    Just negates the input of a forward function call.*/
  inline Transform &backward(float distance) { return forward(-distance); }

  /**\brief Sets the translation of this transform.
   *\param x The number of units, or pixels, to transform on the X axis.
   *\param y The number of units, or pixels, to transform on the Y axis.
   *\return A reference to this transform. (e.g, *this)*/
  Transform &setTranslation(int x, int y) {
    at(0, 2) = static_cast<float>(x);
    at(1, 2) = static_cast<float>(y);
    return *this;
  }

  /**\brief Returns the translation of this transform as a point.
   *\return The point which represents the transform.*/
  Point getTranslation() const {
    return {(int)std::round(at(0, 2)), (int)std::round(at(1, 2))};
  }

  /**\brief Sets the X axis translation of this transform.
   *\param x The number of units, or pixels, to transform on the X axis.
   *\return A reference to this transform. (e.g, *this)*/
  Transform &setTranslationX(int x) {
    at(0, 2) = static_cast<float>(x);
    return *this;
  }

  /**\brief Set the Y axis translation of this transform.
   *\param y The number of units, or pixels, to transform on the Y axis.
   *\return A reference to this transform. (e.g, *this)*/
  Transform &setTranslationY(int y) {
    at(1, 2) = static_cast<float>(y);
    return *this;
  }

  /**\brief Translates this transform.
   *\param x The number of units, or pixels, to transform on the X axis.
   *\param y The number of units, or pixels, to transform on the Y axis.
   *\return A reference to this transform. (e.g, *this)*/
  Transform &translate(int x, int y) {
    at(0, 2) +=
        static_cast<float>(x) * at(0, 0) + static_cast<float>(y) * at(0, 1);
    at(1, 2) +=
        static_cast<float>(x) * at(1, 0) + static_cast<float>(y) * at(1, 1);
    return *this;
  }

  /**\brief Rotates this transform.
   *\param theta The angle at which to rotate, in radians
   *\return A reference to this transform. (e.g, *this)*/
  Transform &rotate(float theta) {
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

  /**\brief Sets the rotation of this transform.
   *\param val The angle at which to rotate, in radians.
   *\return A reference to this transform. (e.g, *this)*/
  Transform &setRotation(float val) {
    if (val == rotation)
      return *this;
    if (rotation != 0.0f)
      rotate(-rotation);
    rotate(val);
    return *this;
  }

  /**\brief Rotates this transform around a specified point.
   *\param x The X coordinate to rotate around.
   *\param y The Y coordinate to rotate around.
   *\param theta The angle at which to rotate, in radians
   *\return A reference to this transform. (e.g, *this)*/
  Transform &rotateAround(int x, int y, float theta) {
    translate(x, y);
    rotate(theta);
    translate(-x, -y);
    return *this;
  }

  /**\brief Applies a scale transformation to this transform.
   *\param sx The X axis scale factor.
   *\param sy The Y axis scale factor.*/
  Transform &scale(float sx, float sy) {
    at(0, 0) *= sx;
    at(0, 1) *= sy;
    at(1, 0) *= sx;
    at(1, 1) *= sy;
    return *this;
  }

  /**\brief Concatenates this Transform with another.
   *\param t The other Transform to concatenate with.
   *\return A reference to this transform. (e.g, *this)*/
  Transform &concatenate(const Transform &t) {
    const float new00 = at(0, 0) * t.at(0, 0) + at(0, 1) * t.at(1, 0);
    const float new01 = at(0, 0) * t.at(0, 1) + at(0, 1) * t.at(1, 1);
    const float new02 =
        at(0, 0) * t.at(0, 2) + at(0, 1) * t.at(1, 2) + at(0, 2);
    const float new10 = at(1, 0) * t.at(0, 0) + at(1, 1) * t.at(1, 0);
    const float new11 = at(1, 0) * t.at(0, 1) + at(1, 1) * t.at(1, 1);
    const float new12 =
        at(1, 0) * t.at(0, 2) + at(1, 1) * t.at(1, 2) + at(1, 2);

    at(0, 0) = new00;
    at(0, 1) = new01;
    at(0, 2) = new02;
    at(1, 0) = new10;
    at(1, 1) = new11;
    at(1, 2) = new12;
    rotation += t.rotation;
    return *this;
  }

  /**\brief Creates a copy of this transform, concatenates the input, and
   * returns it.
   *\param t The input to concatenate onto the copy of this transform.
   *\return Returns the concatenated copy of this transform.*/
  Transform copyConcatenate(const Transform &t) const {
    Transform copy;
    copy.assign(*this);
    copy.concatenate(t);
    return copy;
  }

  /**\brief Interpolates between this and the specified transform.
   *        Progress is a float in range of 0 to 1.
   *\param t The destination transform.
   *\param progress A progress float in range of 0 to 1.
   *\return The resulting interpolated transform.*/
  Transform lerp(const Transform &t, float progress) const {
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

  /**\brief Assigns the value of this transform to that of another.
   *\param t The other transform to derive value from.*/
  void assign(const Transform &t) {
    value = t.value;
    rotation = t.rotation;
  }

  /**\brief Transforms a point according to this transform.
   *\param in The input point.
   *\param dst The destination pointer to store the value. Can be same as
   * input..
   *\return Returns the translated point.
   *\return Also assigns the value of dst pointer to the result.*/
  Point transform(Point in, Point *dst = nullptr) const {
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

  /**\brief Transforms a set of points given a begin and end iterator.
   *\param cur The beginning iterator of a set.
   *\param end The ending iterator of a set.*/
  template <typename ITER_T> void transformSet(ITER_T cur, ITER_T end) const {
    while (cur != end) {
      transform(&(*cur), &(*cur));
      cur++;
    }
  }

  /*Operator overload to transform a single point, for convenience.*/

  /**\brief Operator overload to transform a single point.
   *\param in The point to transform.*/
  inline Point operator()(Point in) const { return transform(in); }

protected:
  /**The underlying matrix type.
   * It's defined simply as an array of 9 floats.
   * Retrieved from coordinate pairs using (x*3+y) as indices.*/
  typedef std::array<float, 9> mat_t;

  /**The value of this transform.*/
  mat_t value;

  /**The rotation of this transform, in radians.*/
  float rotation = 0;

  /**\brief Returns a reference to the float the specified coordinate.
   *\param row The specified row from which to get a component.
   *\param col The specified column from which to get a component.*/
  inline float &at(int row, int col) { return value[row * 3 + col]; }

  /**\brief Returns a copy of the float at the specified coordinate.
   *\param row The specified row from which to get a component.
   *\param col The specified column from which to get a component.*/
  float at(int row, int col) const { return value[row * 3 + col]; }
};

/**\brief Converts degrees to radians.
 * A generic toRadians function. Performs
 * the following: val*(PI/180.0)
 * \param val The value to convert from degress to radians.
 * \return A value of the same type as val, converted to radians.*/
template <typename T> inline T toRadians(T val) {
  return T(val * (M_PI / 180.0));
}

/**\brief Converts radians to degrees.
 * A generic toDegrees function. Performs
 * the following: val*(180.0/PI)
 * \param val The value to convert from radians to degrees.
 * \return A value of the same type as val, converted to degrees.*/
template <typename T> inline T toDegrees(T val) {
  return std::round(T(val * (180.0 / M_PI)));
}

/**\brief Draws a rounded line of variable thickness on the specified image.
 *\param imgRef The image on which to draw the line.
 *\param The X component of the first coordinate.
 *\param The Y component of the first coordinate.
 *\param the X component of the second coordinate.
 *\param the Y component of the second coordinate.
 *\param c The color with which to draw the line.
 *\param width The width of the line.*/
inline void drawLine(Image &imgRef, int x1, int y1, int x2, int y2,
                     const Color &c, int width = 1) {
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
