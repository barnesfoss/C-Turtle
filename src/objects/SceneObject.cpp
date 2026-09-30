// Copyright 2021 Jesse W. Walker
//
// Licensed under the MIT License.
// See LICENSE for details.
#include "CTurtle/objects/SceneObject.hpp"

#include "CTurtle/geometry/Transform.hpp"

namespace cturtle {
SceneObject::SceneObject(AbstractDrawableObject* geom, const Transform& t,
                         int stampid)
    : geom(geom), transform(t), stamp(stampid > -1), stampid(stampid) {}
}  // namespace cturtle
