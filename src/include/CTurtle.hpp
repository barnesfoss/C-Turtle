// Copyright 2021 Jesse W. Walker
//
// Licensed under the MIT License.
// See LICENSE for details.

// This is an "Amalgam" header that includes everything for convenience
#ifndef CTURTLE_CTURTLE_HPP
#define CTURTLE_CTURTLE_HPP
#include "CTurtle/font.hpp"
#include "CTurtle/font/BitmapFont.hpp"
#include "CTurtle/font/TextAlign.hpp"
#include "CTurtle/geometry/Transform.hpp"
#include "CTurtle/geometry/ivec2.hpp"
#include "CTurtle/objects/AbstractDrawableObject.hpp"
#include "CTurtle/objects/Circle.hpp"
#include "CTurtle/objects/CompoundPolygon.hpp"
#include "CTurtle/objects/Line.hpp"
#include "CTurtle/objects/Polygon.hpp"
#include "CTurtle/objects/SceneObject.hpp"
#include "CTurtle/objects/Sprite.hpp"
#include "CTurtle/objects/Text.hpp"
#include "CTurtle/turtle/AbstractTurtleScreen.hpp"
#include "CTurtle/turtle/HeadlessTurtleScreen.hpp"
#include "CTurtle/turtle/InteractiveTurtleScreen.hpp"
#include "CTurtle/turtle/PenState.hpp"
#include "CTurtle/turtle/ScreenMode.hpp"
#include "CTurtle/turtle/Turtle.hpp"
#include "CTurtle/turtle/TurtleSpeed.hpp"
#include "CTurtle/types/Color.hpp"
#include "CTurtle/types/Image.hpp"
#include "CTurtle/util/base64.hpp"
#include "CTurtle/util/io.hpp"
#include "CTurtle/util/jo_gif.hpp"
#include "CTurtle/version.h"
#endif
