// File: movement.cpp
// Definitions for the `Turtle` class's movement methods

#include "CTurtle.hpp"
namespace cturtle {

void Turtle::forward(int pixels) {
  if (screen == nullptr)
    return;
  travelTo(Transform(*transform).forward(static_cast<float>(pixels)));
}

void Turtle::fd(int pixels) { forward(pixels); }

void Turtle::backward(int pixels) {
  if (screen == nullptr)
    return;
  travelTo(Transform(*transform).backward(static_cast<float>(pixels)));
}

void Turtle::bk(int pixels) { backward(pixels); }

void Turtle::back(int pixels) { backward(pixels); }

void Turtle::right(float amt) {
  amt = state->angleMode ? -amt : -toRadians(amt);
  // Flip angle orientation based on screen mode.
  travelTo(Transform(*transform).rotate(amt));
}

void Turtle::rt(float angle) { right(angle); }

void Turtle::left(float amt) {
  amt = state->angleMode ? amt : toRadians(amt);
  // Flip angle orientation based on screen mode.
  travelTo(Transform(*transform).rotate(amt));
}

void Turtle::lt(float angle) { left(angle); }

void Turtle::goTo(int x, int y) {
  travelTo(Transform(*transform).setTranslation(x, y));
}

void Turtle::goTo(const Point &pt) { goTo(pt.x, pt.y); }

void Turtle::setpos(int x, int y) { goTo(x, y); }

void Turtle::setpos(const Point &pt) { goTo(pt.x, pt.y); }

void Turtle::setposition(int x, int y) { goTo(x, y); }

void Turtle::setposition(const Point &pt) { goTo(pt.x, pt.y); }

void Turtle::setx(int x) { travelTo(Transform(*transform).setTranslationX(x)); }

void Turtle::sety(int y) { travelTo(Transform(*transform).setTranslationY(y)); }

int Turtle::xcor() const {
  return static_cast<int>(transform->getTranslateX());
}

int Turtle::ycor() const {
  return static_cast<int>(transform->getTranslateY());
}

Point Turtle::getpos() const { return transform->getTranslation(); }

void Turtle::shift(int x, int y) { goTo(getpos() + Point(x, y)); }

void Turtle::setheading(float amt) {
  // Swap to correct unit if necessary.
  amt = state->angleMode ? amt : toRadians(amt);
  // Flip angle orientation based on screen mode.
  amt = (screen != nullptr) ? screen->mode() == SM_STANDARD ? amt : -amt : amt;
  travelTo(Transform(*transform).setRotation(amt));
}

void Turtle::face(int x, int y) { setheading(towards(x, y) - heading()); }

void Turtle::face(const Point &pt) { setheading(towards(pt) - heading()); }

void Turtle::seth(float angle) { setheading(angle); }

float Turtle::heading() {
  return state->angleMode ? transform->getRotation()
                          : toDegrees(transform->getRotation());
}

void Turtle::home() {
  travelTo(Transform()); // set transform to identity, more-or-less...
}

void Turtle::speed(float val) {
  pushState();
  state->moveSpeed = val;
}

float Turtle::speed() { return state->moveSpeed; }

void Turtle::tilt(float amt) {
  amt = state->angleMode ? amt : toRadians(amt);
  // Flip angle orientation based on screen mode.
  amt = screen->mode() == SM_STANDARD ? amt : -amt;
  pushState();
  state->cursorTilt += amt;
  updateParent(false, false);
}

float Turtle::tilt() const {
  return state->angleMode ? state->cursorTilt : toDegrees(state->cursorTilt);
}

void Turtle::travelBetween(Transform src, const Transform &dest,
                           bool doPushState) {
  if (dest == src)
    return;

  // Set the "traveling" state for screen drawing. Indicates when to draw
  // travel lines (e.g, when pen is down).
  traveling = true;

  const auto duration = static_cast<float>(getAnimMS());
  if ((screen ? !screen->isclosed() : false) &&
      duration > 0) { // no point in animating with no screen
    const unsigned long startTime = detail::epochTime();

    float progress = 0;
    while (progress < 1.0f) {
      const unsigned long curTime = detail::epochTime();

      transform->assign(src.lerp(dest, progress));
      travelPoints[0] = src.getTranslation();
      travelPoints[1] = transform->getTranslation();

      updateParent(false, false);

      progress = (static_cast<float>(curTime - startTime) / duration);
    }
  }

  if (doPushState) {
    if (state->tracing && !state->filling) {
      pushTraceLine(src.getTranslation(), dest.getTranslation());
    } else if (state->filling) {
      fillAccum.points.push_back(dest.getTranslation());
      if (state->tracing) {
        fillLines.emplace_back(src.getTranslation(), dest.getTranslation(),
                               state->penColor, state->penWidth);
      }
    }

    transform->assign(src);
    pushState();
  }

  transform->assign(dest);
  traveling = false;
  updateParent(false, false);
}

} // namespace cturtle
