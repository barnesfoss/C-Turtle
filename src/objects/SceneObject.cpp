// Copyright 2021 Jesse W. Walker
//
// Licensed under the MIT License.
// See LICENSE for details.
#include "objects/SceneObject.hpp"

#include "geometry/Transform.hpp"

namespace cturtle {
class AbstractDrawableObject;

SceneObject::SceneObject(AbstractDrawableObject *geom, const Transform &t, int stampid)
    : geom(geom), transform(t), stamp(stampid > -1), stampid(stampid) {}
} // namespace cturtle
