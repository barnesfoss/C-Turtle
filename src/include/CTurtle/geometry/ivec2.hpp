// Copyright 2021 Jesse W. Walker
//
// Licensed under the MIT License.
// See LICENSE for details.
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
    ivec2();

    /**\brief Assignment cons tructor.
     *\param x The X value of this ivec2.
     *\param y The Y value of this ivec2.*/
    ivec2(int x, int y);

    /*Array access operator overload.*/

    /**\brief Array access operator overload. Useful for convenience.
     *\param index The index of one of the components of this ivec2 (0..1)
     *\return A reference to the index */
    int& operator[](int index);

    /**\brief Array access operator overload. Useful for convenience.
     *\param index The index of one of the components of this ivec2 (0..1)
     *\return A reference to the index */
    int operator[](int index) const;

    ivec2 operator+(const ivec2& other) const;

    ivec2& operator+=(const ivec2& other);

    ivec2 operator-(const ivec2& other) const;

    ivec2& operator-=(const ivec2& other);

    /**\brief Comparison operator between this vector and the other specified.*/
    bool operator==(const ivec2& other) const;
};

/**\brief Returns the distance between the two specified points.
 *\param a The first point.
 *\param b The second point.
 *\return The distance, in nondescript units, between the first and second
 * points.*/
int distance(const ivec2& a, const ivec2& b);

/**\brief Finds the point that lies in the middle of the two specified.
 *\param a The first point.
 *\param b The second point.
 *\return The point between the first and second points.*/
ivec2 middle(const ivec2& a, const ivec2& b);

/**\brief Performs a linear interpolation between the two specified points.
 *\param a The first point.
 *\param b The second point.
 *\param progress A float between 0...1; 0 is to A, 1 is to B, 0..1 is between.
 *\return A point between A and B.
 */
ivec2 lerp(const ivec2& a, const ivec2& b, float progress);

/**\brief An alias for ivec2. Strictly for convenience and clarity.*/
typedef ivec2 Point;
}  // namespace cturtle
