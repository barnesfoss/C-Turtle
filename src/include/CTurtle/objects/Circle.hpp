// Copyright 2021 Jesse W. Walker
//
// Licensed under the MIT License.
// See LICENSE for details.
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
     * The higher this number is, the more "high-quality" it can be
     * considered.*/
    int steps = 10;

    /**\brief Empty constructor.*/
    Circle() = default;

    /**\brief Radius and step assignment constructor.
     *\param radius The radius, in pixels, of this circle.
     *\param steps The number of vertices used by this circle.*/
    Circle(int radius, int steps, const Color& fillColor, int outlineWidth = 0,
           const Color& outlineColor = Color());

    /**\brief Copy constructor.
     *\param other Another instance of a circle from which to derive value.*/
    Circle(const Circle& other) = default;

    AbstractDrawableObject* copy() const override;

    void draw(const Transform& t, Image& imgRef) const override;
};

}  // namespace cturtle
