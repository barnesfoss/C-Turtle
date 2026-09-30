// Copyright 2021 Jesse W. Walker
//
// Licensed under the MIT License.
// See LICENSE for details.
// File: pen.cpp
// Definitions for the `Turtle` class pen methods

#include <CTurtle.hpp>
namespace cturtle {

const PenState& Turtle::penstate() const { return *state; }

void Turtle::setpenstate(bool down) {
    pushState();
    state->tracing = down;
}

void Turtle::penup() { setpenstate(false); }

void Turtle::pendown() { setpenstate(true); }

void Turtle::pencolor(const Color& c) {
    pushState();
    state->penColor = c;
    updateParent(false, false);
}

Color Turtle::pencolor() const { return state->penColor; }

void Turtle::width(int pixels) {
    pushState();
    state->penWidth = pixels;
}

int Turtle::width() const { return state->penWidth; }

void Turtle::pushState() {
    if (stateStack.size() + 1 > undoStackSize) stateStack.pop_front();

    stateStack.push_back(
        stateStack.back());  // Push a copy of the back-most pen state.
    state = &stateStack.back();
    transform = &state->transform;
    state->objectsBefore = objects.size();
}

bool Turtle::popState() {
    if (stateStack.size() == 1) return false;
    stateStack.pop_back();
    state = &stateStack.back();
    transform = &state->transform;
    return true;
}

}  // namespace cturtle
