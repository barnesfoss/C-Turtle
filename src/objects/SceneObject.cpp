#include "CTurtle/objects/SceneObject.hpp"
namespace cturtle {
SceneObject::SceneObject(AbstractDrawableObject *geom, const Transform &t,
                         int stampid)
    : geom(geom), transform(t), stamp(stampid > -1), stampid(stampid) {}
} // namespace cturtle
