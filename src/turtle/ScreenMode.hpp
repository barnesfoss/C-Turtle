#pragma once
namespace cturtle {
/**\brief ScreenMode Enumeration, used to decide orientation of the drawing
 * calls on TurtleScreens.
 *\sa TurtleScreen::mode(ScreenMode)*/
enum ScreenMode {
  SM_STANDARD,
  SM_LOGO //,
          //        SM_WORLD
};
} // namespace cturtle
// I'm leaving out SM_WORLD. Adding it would really require more work than I
// have time for./ namespace cturtle
