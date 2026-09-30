#include "CTurtle/objects/CompoundPolygon.hpp"
#include "CTurtle/objects/AbstractDrawableObject.hpp"
namespace cturtle {
CompoundPolygon::CompoundPolygon(const CompoundPolygon &copy)
    : AbstractDrawableObject(copy) {
  for (const component_t &component : copy.components)
    components.emplace_back(component.first, component.second->copy());
}
void CompoundPolygon::addcomponent(const AbstractDrawableObject &obj,
                                   const Transform &transform) {
  components.emplace_back(transform, obj.copy());
}

AbstractDrawableObject *CompoundPolygon::copy() const {
  return new CompoundPolygon(*this);
}

void CompoundPolygon::draw(const Transform &t, Image &imgRef) const {
  for (const component_t &comp : components) {
    comp.second->draw(t.copyConcatenate(comp.first), imgRef);
  }
}

} // namespace cturtle
