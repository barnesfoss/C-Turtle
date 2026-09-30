#pragma once
#include "AbstractDrawableObject.hpp"
#include <list>
#include <memory>
namespace cturtle {
/**
 * \brief a Compound Polygon instance is composed from a number of smaller
 * parts, which are each derived from AbstractDrawableObject. Compound Polygons
 * can have a variety of attachments. After the parts are assembled, the polygon
 * is essentially read-only. These can be used to assemble several pieces of
 * geometry into one object. These objects are self-contained and have ownership
 * of all AbstractDrawableObject instances they contain.
 * */
class CompoundPolygon : public AbstractDrawableObject {
public:
  // Compound Polygon components are pairs of transforms and unique pointers to
  // other drawable objects..
  typedef std::pair<Transform, std::unique_ptr<AbstractDrawableObject>>
      component_t;

  CompoundPolygon() = default;

  CompoundPolygon(const CompoundPolygon &copy);

  ~CompoundPolygon() override = default;

  /**
   * \brief Adds a component to this compound polygon.
   * @param obj Object to copy and add.
   * @param transform relative to root transform.
   */
  void addcomponent(const AbstractDrawableObject &obj,
                    const Transform &transform = Transform());

  /**
   * Creates a copy of this Compound Polygon allocated with the new keyword.
   * This must be deleted at the responsibility of the invoker.
   */
  AbstractDrawableObject *copy() const override;

  /**Draws this CompoundPolygon.
   * Disregards the Color attribute in favor of the components' colors*/
  void draw(const Transform &t, Image &imgRef) const override;

protected:
  std::list<component_t> components;
};

} // namespace cturtle
