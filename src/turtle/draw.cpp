// Copyright 2021 Jesse W. Walker
//
// Licensed under the MIT License.
// See LICENSE for details.
// File : draw.cpp
// Definitions for the `Turtle` class drawing methods

#include <list>
#include <string>

#include "CTurtle.hpp"
#include "CTurtle/font.hpp"
#include "CTurtle/objects/Circle.hpp"
#include "CTurtle/objects/Text.hpp"
namespace cturtle {
void Turtle::circle(int radius, int steps, const Color& color) {
    pushGeometry(*transform, new Circle(radius, steps, color));
    updateParent(false, true);
}

void Turtle::circle(const Color& color) { circle(30, 15, color); }

void Turtle::dot(const Color& color, int size) { circle(size / 2, 4, color); }

void Turtle::fill(bool val) {
    if (state->filling && !val) {
        // Add the fill polygon
        screen->getScene().emplace_back(
            new Polygon(fillAccum.points, state->fillColor), Transform());
        objects.push_back(std::prev(screen->getScene().end(), 1));

        // Add all trace lines created when tracing out the fill polygon.
        if (!fillLines.empty()) {
            // for each line we've created when having the pen down, and have
            // been tracing a shape
            for (Line& lineInfo : fillLines) {
                screen->getScene().emplace_back(lineInfo.copy(), Transform());
                objects.push_back(std::prev(screen->getScene().end(), 1));
            }
            fillLines.clear();
        }

        fillAccum.points.clear();
        updateParent(false, false);
    }
    state->filling = val;
}

bool Turtle::filling() const { return penstate().filling; }

void Turtle::begin_fill() { fill(true); }

void Turtle::end_fill() { fill(false); }

void Turtle::fillcolor(const Color& c) {
    pushState();
    state->fillColor = c;
    updateParent(false, false);
}

Color Turtle::fillcolor() { return state->fillColor; }

void Turtle::write(const std::string& text) {
    if (text.empty()) return;
    pushText(*transform, state->fillColor, screen->font(DEFAULT_FONT), text,
             1.0f);
    updateParent(false, false);
}

void Turtle::write(const std::string& text, const std::string& font,
                   const Color& color, float scale, TextAlign alignment) {
    if (text.empty()) return;
    pushText(*transform, color, screen->font(font), text, scale, alignment);
    updateParent(false, false);
}

int Turtle::stamp() {
    pushStamp(*transform, state->cursor->copy());
    return state->curStamp;
}
void Turtle::clearstamp(int stampid) {
    auto iter = objects.begin();  // iterator which holds an iterator to the
                                  // screen's scene list.

    while (iter != objects.end()) {
        auto& objIter = *iter;
        if (objIter->stamp && objIter->stampid == stampid) {
            break;
        }
        iter++;
    }

    if (iter != objects.end()) {
        objects.erase(iter);

        if (screen != nullptr) {
            screen->getScene().erase(*iter);
        }
    }

    updateParent(true, false);
}

void Turtle::clearstamps(int stampid) {
    typedef decltype(objects.begin()) iter_t;

    std::list<iter_t> removals;

    auto iter = objects.begin();
    while (iter != objects.end()) {
        auto& objIter = *iter;
        if (stampid < 0 ? objIter->stamp
                        : (objIter->stamp && objIter->stampid <= stampid)) {
            removals.push_back(iter);
        }
        iter++;
    }

    for (auto& iter : removals) {
        screen->getScene().erase(*iter);
        objects.erase(iter);
    }

    updateParent(true, false);
}

bool Turtle::undo(bool try_redraw) {
    // total objects on the state stack prior to
    const uint32_t totalBefore = state->objectsBefore;

    if (stateStack.size() >= 2) travelBack();  // Travel back if stack size >= 2

    // If we can't pop the state, break early.
    if (!popState()) {
        return false;
    }

    auto begin = std::prev(objects.end(), (totalBefore - state->objectsBefore));
    auto iter = begin;

    while (iter != objects.end()) {
        screen->getScene().erase(*iter);
        iter++;
    }

    objects.erase(begin, objects.end());

    // Will invalidate the whole screen due to object removal, but we allow the
    // option to not.
    updateParent(try_redraw, false);
    return true;
}

void Turtle::setundobuffer(unsigned int size) {
    if (size < 1)  // clamp lower bound to 1
        size = 1;

    undoStackSize = size;
    while (stateStack.size() > size) {
        stateStack.pop_front();
    }
}

unsigned int Turtle::undobufferentries() {
    return static_cast<unsigned int>(stateStack.size());
}

void Turtle::draw(const Transform& screenTransform, Image& canvas) {
    if (this->screen == nullptr) return;

    if (!state->visible) return;

    // Draw all lines queued during filling a shape.
    // This is only populated when the turtle moves between a beginfill
    // and endfill while the pen is down.
    for (const Line& line : fillLines) line.draw(screenTransform, canvas);

    if (traveling && state->tracing) {
        // Draw the "Travel-Line" when in the middle of the travelTo func
        travelPoints[0] = screenTransform(travelPoints[0]);
        travelPoints[1] = screenTransform(travelPoints[1]);
        drawLine(canvas, travelPoints[0].x, travelPoints[0].y,
                 travelPoints[1].x, travelPoints[1].y, state->penColor,
                 state->penWidth);
    }

    // Add the extra rotate to start cursor facing right :)
    const float cursorRot =
        this->screen->mode() == SM_STANDARD ? 1.5708f : -3.1416f;
    Transform cursorTransform = screenTransform.copyConcatenate(*transform)
                                    .rotate(cursorRot + state->cursorTilt);
    state->cursor->fillColor = state->fillColor;
    state->cursor->outlineWidth = 1;
    state->cursor->outlineColor = state->penColor;
    state->cursor->draw(cursorTransform, canvas);
}

bool Turtle::pushGeometry(const Transform& t, AbstractDrawableObject* geom) {
    if (screen != nullptr) {
        pushState();
        screen->getScene().emplace_back(geom, t);
        objects.push_back(std::prev(screen->getScene().end()));
        return true;
    }
    return false;
}

bool Turtle::pushStamp(const Transform& t, AbstractDrawableObject* geom) {
    if (screen != nullptr) {
        pushState();
        const float cursorRot =
            this->screen->mode() == SM_STANDARD ? 1.5708f : -3.1416f;

        Transform trans(t);
        trans.rotate(cursorRot + state->cursorTilt);

        geom->outlineWidth = 1;
        geom->outlineColor = state->penColor;

        screen->getScene().emplace_back(geom, trans, state->curStamp++);
        SceneObject& _ = screen->getScene().back();

        objects.push_back(std::prev(screen->getScene().end()));
        return true;
    }
    return false;
}

bool Turtle::pushText(const Transform& t, const Color& color,
                      const BitmapFont& font, const std::string& text,
                      float scale, TextAlign alignment) {
    if (screen != nullptr) {
        pushState();
        screen->getScene().emplace_back(
            new Text(text, font, color, scale, alignment), t);
        objects.push_back(std::prev(screen->getScene().end()));
        return true;
    }
    return false;
}

bool Turtle::pushTraceLine(Point a, Point b) {
    if (screen != nullptr) {
        screen->getScene().emplace_back(
            new Line(a, b, state->penColor, state->penWidth), Transform());
        objects.push_back(std::prev(screen->getScene().end()));
        // Trace lines do NOT push a state->
        // Their state is encompassed by movement,
        // and these lines are only added when moving the turtle
        // while the pen is down.
        return true;
    }
    return false;
}

}  // namespace cturtle
