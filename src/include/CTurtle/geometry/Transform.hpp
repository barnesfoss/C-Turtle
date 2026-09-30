// Copyright 2021 Jesse W. Walker
//
// Licensed under the MIT License.
// See LICENSE for details.
#pragma once
#include <math.h>

#include <array>

#include "CTurtle/geometry/ivec2.hpp"
#include "CTurtle/types/Color.hpp"
#include "CTurtle/types/Image.hpp"
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
    Transform();

    /**\brief Copy constructor.
     *\param other The other transform from which to derive value.*/
    Transform(const Transform& other);

    /**\brief Point and rotattypesconstructor.
     * Initializes a transform with the specified rotation, a translation
     * matching the specified point.
     * \param point The translation of this newly constructed transform.
     * \param rotation The rotation of this newly constructed transform.
     */
    Transform(const ivec2& point, float rotation);

    /**\brief Sets this transform to an identity.
     * When you concatenate an identity transform onto another object,
     * The resulting point is the same as it would have been pre-concatenation.
     * Such is the point of an identity transform, and is why Transforms
     * are initialized to have this value.
     *\return A reference to this transform. (e.g, *this)*/
    Transform& identity();

    /**\brief Returns a boolean indicating if this transform
     *        is equivalent in value to the one specified.*/
    bool operator==(const Transform& other) const;

    /**\brief Returns the X scale of this transform.
     *\return Returns the X scale of this transform.*/
    float getScaleX() const;

    /**\brief Returns the Y scale of this transform.
     *\return Returns the Y scale of this transform.*/
    float getScaleY() const;

    /**\brief Returns the X translation of this transform.
     *\return Returns the X translation of this transform.*/
    float getTranslateX() const;

    /**\brief Returns the Y translation of this transform.
     *\return Returns the Y translation of this transform.*/
    float getTranslateY() const;

    /**\brief Returns rotation of this transform, in radians.
     *\return The rotation of this transform, in radians.*/
    float getRotation() const;

    /**Moves this transform "forward" according to its rotation.*/
    Transform& forward(float distance);

    /*Backwards function.
      Just negates the input of a forward function call.*/
    Transform& backward(float distance);

    /**\brief Sets the translation of this transform.
     *\param x The number of units, or pixels, to transform on the X axis.
     *\param y The number of units, or pixels, to transform on the Y axis.
     *\return A reference to this transform. (e.g, *this)*/
    Transform& setTranslation(int x, int y);

    /**\brief Returns the translation of this transform as a point.
     *\return The point which represents the transform.*/
    Point getTranslation() const;

    /**\brief Sets the X axis translation of this transform.
     *\param x The number of units, or pixels, to transform on the X axis.
     *\return A reference to this transform. (e.g, *this)*/
    Transform& setTranslationX(int x);

    /**\brief Set the Y axis translation of this transform.
     *\param y The number of units, or pixels, to transform on the Y axis.
     *\return A reference to this transform. (e.g, *this)*/
    Transform& setTranslationY(int y);

    /**\brief Translates this transform.
     *\param x The number of units, or pixels, to transform on the X axis.
     *\param y The number of units, or pixels, to transform on the Y axis.
     *\return A reference to this transform. (e.g, *this)*/
    Transform& translate(int x, int y);

    /**\brief Rotates this transform.
     *\param theta The angle at which to rotate, in radians
     *\return A reference to this transform. (e.g, *this)*/
    Transform& rotate(float theta);

    /**\brief Sets the rotation of this transform.
     *\param val The angle at which to rotate, in radians.
     *\return A reference to this transform. (e.g, *this)*/
    Transform& setRotation(float val);

    /**\brief Rotates this transform around a specified point.
     *\param x The X coordinate to rotate around.
     *\param y The Y coordinate to rotate around.
     *\param theta The angle at which to rotate, in radians
     *\return A reference to this transform. (e.g, *this)*/
    Transform& rotateAround(int x, int y, float theta);

    /**\brief Applies a scale transformation to this transform.
     *\param sx The X axis scale factor.
     *\param sy The Y axis scale factor.*/
    Transform& scale(float sx, float sy);

    /**\brief Concatenates this Transform with another.
     *\param t The other Transform to concatenate with.
     *\return A reference to this transform. (e.g, *this)*/
    Transform& concatenate(const Transform& t);

    /**\brief Creates a copy of this transform, concatenates the input, and
     * returns it.
     *\param t The input to concatenate onto the copy of this transform.
     *\return Returns the concatenated copy of this transform.*/
    Transform copyConcatenate(const Transform& t) const;

    /**\brief Interpolates between this and the specified transform.
     *        Progress is a float in range of 0 to 1.
     *\param t The destination transform.
     *\param progress A progress float in range of 0 to 1.
     *\return The resulting interpolated transform.*/
    Transform lerp(const Transform& t, float progress) const;

    /**\brief Assigns the value of this transform to that of another.
     *\param t The other transform to derive value from.*/
    void assign(const Transform& t);

    /**\brief Transforms a point according to this transform.
     *\param in The input point.
     *\param dst The destination pointer to store the value. Can be same as
     * input..
     *\return Returns the translated point.
     *\return Also assigns the value of dst pointer to the result.*/
    Point transform(Point in, Point* dst = nullptr) const;

    /**\brief Transforms a set of points given a begin and end iterator.
     *\param cur The beginning iterator of a set.
     *\param end The ending iterator of a set.*/
    template <typename ITER_T>
    void transformSet(ITER_T cur, ITER_T end) const {
        while (cur != end) {
            transform(&(*cur), &(*cur));
            cur++;
        }
    }

    /*Operator overload to transform a single point, for convenience.*/

    /**\brief Operator overload to transform a single point.
     *\param in The point to transform.*/
    Point operator()(Point in) const;

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
    float& at(int row, int col);

    /**\brief Returns a copy of the float at the specified coordinate.
     *\param row The specified row from which to get a component.
     *\param col The specified column from which to get a component.*/
    float at(int row, int col) const;
};

/**\brief Converts degrees to radians.
 * A generic toRadians function. Performs
 * the following: val*(PI/180.0)
 * \param val The value to convert from degress to radians.
 * \return A value of the same type as val, converted to radians.*/
template <typename T>
T toRadians(T val) {
    return T(val * (M_PI / 180.0));
}

/**\brief Converts radians to degrees.
 * A generic toDegrees function. Performs
 * the following: val*(180.0/PI)
 * \param val The value to convert from radians to degrees.
 * \return A value of the same type as val, converted to degrees.*/
template <typename T>
T toDegrees(T val) {
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
void drawLine(Image& imgRef, int x1, int y1, int x2, int y2, const Color& c,
              int width = 1);
}  // namespace cturtle
