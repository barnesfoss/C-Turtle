#include "CTurtle/turtle/PenState.hpp"
namespace cturtle {
PenState::PenState(const PenState &copy) {
  transform = copy.transform;
  moveSpeed = copy.moveSpeed;
  tracing = copy.tracing;
  angleMode = copy.angleMode;
  penWidth = copy.penWidth;
  filling = copy.filling;
  penColor = copy.penColor;
  fillColor = copy.fillColor;
  cursor.reset(copy.cursor ? copy.cursor->copy() : nullptr);
  curStamp = copy.curStamp;
  visible = copy.visible;
  cursorTilt = copy.cursorTilt;
  objectsBefore = copy.objectsBefore;
}
PenState &PenState::operator=(const PenState &copy) {
  transform = copy.transform;
  moveSpeed = copy.moveSpeed;
  tracing = copy.tracing;
  angleMode = copy.angleMode;
  penWidth = copy.penWidth;
  filling = copy.filling;
  penColor = copy.penColor;
  fillColor = copy.fillColor;
  cursor.reset(copy.cursor ? copy.cursor->copy() : nullptr);
  curStamp = copy.curStamp;
  visible = copy.visible;
  cursorTilt = copy.cursorTilt;
  objectsBefore = copy.objectsBefore;
  return *this;
}
}; // namespace cturtle
