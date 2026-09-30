// Copyright 2021 Jesse W. Walker
//
// Licensed under the MIT License.
// See LICENSE for details.
// File: turtle.cpp
// Unclassified method definitions for the `Turtle` class
#include <CTurtle.hpp>
#include <string>

namespace cturtle {
Turtle::Turtle(AbstractTurtleScreen& scr) {
    screen = &scr;
    screen->add(*this);
    reset();
}

void Turtle::shape(const AbstractDrawableObject& p) {
    pushState();
    state->cursor.reset(p.copy());
    updateParent(false, false);
}

void Turtle::shape(const std::string& name) {
    pushState();
    state->cursor.reset((screen->shape(name).copy()));
    updateParent(false, false);
}

const AbstractDrawableObject& Turtle::shape() { return *state->cursor; }

void Turtle::setshowturtle(bool val) {
    pushState();
    state->visible = val;
    updateParent(false, false);
}

void Turtle::showturtle() { setshowturtle(true); }

void Turtle::hideturtle() { setshowturtle(false); }

void Turtle::reset() {
    // Reset objects, transforms, trace lines, state, etc.

    // Note to self, clearing the list, appending a new transform,
    // then reassigning the transform reference just didn't want to work.
    // I have no idea why. Therefore, we're resetting it in the same
    // manner we initially construct it.
    stateStack = {PenState()};
    state = &stateStack.back();

    transform = &state->transform;
    const auto numItems = objects.size();

    if (screen != nullptr) {
        // Re-assign cursor on reset, derived from parent screen.
        state->cursor.reset(screen->shape("indented triangle").copy());
        // Erase all objects
        while (!objects.empty()) {
            screen->getScene().erase(objects.front());
            objects.pop_front();
        }

        // Alter cursor tilt and default transform
        // when operating under SM_LOGO mode.
        // This is to bring it up-to-par with Python's
        // implementation of screen modes.
        if (screen->mode() == SM_LOGO) {
            state->cursorTilt = (-1.5708f);
            transform->rotate(1.5708f);
        }
    }

    updateParent(numItems > 0, false);
}

void Turtle::setScreen(AbstractTurtleScreen* scr) { screen = scr; }

Turtle::~Turtle() {
    // remove itself from its parent screen...
    if (screen != nullptr) screen->remove(*this);
}

uint32_t Turtle::getAnimMS() {
    if (screen == nullptr) return 0;

    // 300 is the "scale" animations adhere to.
    // The longest animation is 300 milliseconds, shortest is 0.
    // This was an arbitrary choice, trying to match the speed of the Python
    // implementation.
    if (!screen->supports_live_animation() || state->moveSpeed < 0)
        return 0;  // no animation means no time spent animating...
    return uint32_t((state->moveSpeed / 10.0f) * 300);  //<----
}

void Turtle::updateParent(bool invalidate, bool input) {
    if (screen != nullptr) screen->update(invalidate, input);
}

void Turtle::travelTo(const Transform& dest) {
    travelBetween(*transform, dest, true);
}

void Turtle::travelBack() {
    travelBetween(*transform, std::prev(stateStack.end(), 2)->transform, false);
}

}  // namespace cturtle
