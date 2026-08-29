#pragma once
#include <math.h>
namespace cturtle {
/**\brief Represents a coordinate pair (e.g, x & y)
 * This class is represented as a low-precision point, because
 * this data type tends to be most easily drawn to a simple canvas.*/
struct ivec2 {
  union {
    struct {
      int x, y;
    };
    int data[2];
  };

  /**\brief Empty constructor. Initializes X and Y to both equal 0.*/
  ivec2() : x(0), y(0) {}

  /**\brief Assignment cons tructor.
   *\param x The X value of this ivec2.
   *\param y The Y value of this ivec2.*/
  ivec2(int x, int y) : x(x), y(y) {}

  /*Array access operator overload.*/

  /**\brief Array access operator overload. Useful for convenience.
   *\param index The index of one of the components of this ivec2 (0..1)
   *\return A reference to the index */
  inline int &operator[](int index) { return data[index]; }

  /**\brief Array access operator overload. Useful for convenience.
   *\param index The index of one of the components of this ivec2 (0..1)
   *\return A reference to the index */
  inline int operator[](int index) const { return data[index]; }

  ivec2 operator+(const ivec2 &other) const {
    return {x + other.x, y + other.y};
  }

  ivec2 &operator+=(const ivec2 &other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  ivec2 operator-(const ivec2 &other) const {
    return {x - other.x, y - other.y};
  }

  ivec2 &operator-=(const ivec2 &other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  /**\brief Comparison operator between this vector and the other specified.*/
  bool operator==(const ivec2 &other) const {
    return x == other.x && y == other.y;
  }
};

/**\brief Returns the distance between the two specified points.
 *\param a The first point.
 *\param b The second point.
 *\return The distance, in nondescript units, between the first and second
 * points.*/
inline int distance(const ivec2 &a, const ivec2 &b) {
  return static_cast<int>(
      std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2)));
}

/**\brief Finds the point that lies in the middle of the two specified.
 *\param a The first point.
 *\param b The second point.
 *\return The point between the first and second points.*/
inline ivec2 middle(const ivec2 &a, const ivec2 &b) {
  return {(a.x + b.x) / 2, (a.y + b.y) / 2};
}

/**\brief Performs a linear interpolation between the two specified points.
 *\param a The first point.
 *\param b The second point.
 *\param progress A float between 0...1; 0 is to A, 1 is to B, 0..1 is between.
 *\return A point between A and B.
 */
inline ivec2 lerp(const ivec2 &a, const ivec2 &b, float progress) {
  if (progress <= 0)
    return a;
  else if (progress >= 1)
    return b;
  return {
      static_cast<int>(std::round(progress * static_cast<float>(b.x - a.x))) +
          a.x,
      static_cast<int>(std::round(progress * static_cast<float>(b.y - a.y))) +
          a.y};
}

/**\brief An alias for ivec2. Strictly for convenience and clarity.*/
typedef ivec2 Point;
} // namespace cturtle
