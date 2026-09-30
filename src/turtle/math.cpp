// Copyright 2021 Jesse W. Walker
//
// Licensed under the MIT License.
// See LICENSE for details.
// File: math.cpp
// Definitions for the `Turtle` class arithmetic functions

#include <CTurtle.hpp>
#include <cmath>
namespace cturtle {
int Turtle::distance(int x, int y) {
    return cturtle::distance(transform->getTranslation(), {x, y});
}

int Turtle::distance(const Point& pt) {
    return cturtle::distance(transform->getTranslation(), pt);
}

float Turtle::towards(int x, int y) {
    float amt = std::atan2(static_cast<float>(y) - transform->getTranslateY(),
                           static_cast<float>(x) - transform->getTranslateX());

    // 6.28319 is a full rotation in radians...
    if (toDegrees(amt) < 0) amt = 6.28319f + amt;

    // convert to degrees if necessary.
    amt = state->angleMode ? amt : toDegrees(amt);
    return amt + heading();
}

float Turtle::towards(const Point& pt) { return towards(pt.x, pt.y); }

void Turtle::degrees() {
    pushState();
    state->angleMode = false;
}

void Turtle::radians() {
    pushState();
    state->angleMode = true;
}

}  // namespace cturtle
