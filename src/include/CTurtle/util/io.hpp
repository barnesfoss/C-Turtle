// Copyright 2021 Jesse W. Walker
//
// Licensed under the MIT License.
// See LICENSE for details.
#ifndef CTURTLE_UTIL_IO_HPP
#define CTURTLE_UTIL_IO_HPP

#include <functional>
#include <string>
#include <unordered_map>

namespace cturtle {
/*Mouse event callback type.*/
typedef std::function<void(int, int)> MouseFunc;

/*Keyboard event callback type.*/
typedef std::function<void()> KeyFunc;

/*Timer event callback type.*/
typedef std::function<void(void)> TimerFunc;

/**\brief The KeyboardKey Enumeration contains declarations for all
 *        accepted keyboard input keys.
 * \see keyFromName()*/
enum KeyboardKey {
  KEY_ESC,
  KEY_F1,
  KEY_F2,
  KEY_F3,
  KEY_F4,
  KEY_F5,
  KEY_F6,
  KEY_F7,
  KEY_F8,
  KEY_F9,
  KEY_F10,
  KEY_F11,
  KEY_F12,
  KEY_PAUSE,
  KEY_1,
  KEY_2,
  KEY_3,
  KEY_4,
  KEY_5,
  KEY_6,
  KEY_7,
  KEY_8,
  KEY_9,
  KEY_0,
  KEY_BACKSPACE,
  KEY_INSERT,
  KEY_HOME,
  KEY_PAGEUP,
  KEY_TAB,
  KEY_Q,
  KEY_W,
  KEY_E,
  KEY_R,
  KEY_T,
  KEY_Y,
  KEY_U,
  KEY_I,
  KEY_O,
  KEY_P,
  KEY_DELETE,
  KEY_END,
  KEY_PAGEDOWN,
  KEY_CAPSLOCK,
  KEY_A,
  KEY_S,
  KEY_D,
  KEY_F,
  KEY_G,
  KEY_H,
  KEY_J,
  KEY_K,
  KEY_L,
  KEY_ENTER,
  KEY_SHIFTLEFT,
  KEY_Z,
  KEY_X,
  KEY_C,
  KEY_V,
  KEY_B,
  KEY_N,
  KEY_M,
  KEY_SHIFTRIGHT,
  KEY_ARROWUP,
  KEY_CTRLLEFT,
  KEY_APPLEFT,
  KEY_ALT,
  KEY_SPACE,
  KEY_ALTGR,
  KEY_APPRIGHT,
  KEY_MENU,
  KEY_CTRLRIGHT,
  KEY_ARROWLEFT,
  KEY_ARROWDOWN,
  KEY_ARROWRIGHT,
  KEY_PAD0,
  KEY_PAD1,
  KEY_PAD2,
  KEY_PAD3,
  KEY_PAD4,
  KEY_PAD5,
  KEY_PAD6,
  KEY_PAD7,
  KEY_PAD8,
  KEY_PAD9,
  KEY_PADADD,
  KEY_PADSUB,
  KEY_PADMUL,
  KEY_PADDIV
};

const std::unordered_map<std::string, KeyboardKey> NAMED_KEYS = {{"ESC", KEY_ESC},
                                                                 {"F1", KEY_F1},
                                                                 {"F2", KEY_F2},
                                                                 {"F3", KEY_F3},
                                                                 {"F4", KEY_F4},
                                                                 {"F5", KEY_F5},
                                                                 {"F6", KEY_F6},
                                                                 {"F7", KEY_F7},
                                                                 {"F8", KEY_F8},
                                                                 {"F9", KEY_F9},
                                                                 {"F10", KEY_F10},
                                                                 {"F11", KEY_F11},
                                                                 {"F12", KEY_F12},
                                                                 {"PAUSE", KEY_PAUSE},
                                                                 {"1", KEY_1},
                                                                 {"2", KEY_2},
                                                                 {"3", KEY_3},
                                                                 {"4", KEY_4},
                                                                 {"5", KEY_5},
                                                                 {"6", KEY_6},
                                                                 {"7", KEY_7},
                                                                 {"8", KEY_8},
                                                                 {"9", KEY_9},
                                                                 {"0", KEY_0},
                                                                 {"BACKSPACE", KEY_BACKSPACE},
                                                                 {"INSERT", KEY_INSERT},
                                                                 {"HOME", KEY_HOME},
                                                                 {"PAGEUP", KEY_PAGEUP},
                                                                 {"TAB", KEY_TAB},
                                                                 {"Q", KEY_Q},
                                                                 {"W", KEY_W},
                                                                 {"E", KEY_E},
                                                                 {"R", KEY_R},
                                                                 {"T", KEY_T},
                                                                 {"Y", KEY_Y},
                                                                 {"U", KEY_U},
                                                                 {"I", KEY_I},
                                                                 {"O", KEY_O},
                                                                 {"P", KEY_P},
                                                                 {"DELETE", KEY_DELETE},
                                                                 {"END", KEY_END},
                                                                 {"PAGEDOWN", KEY_PAGEDOWN},
                                                                 {"CAPSLOCK", KEY_CAPSLOCK},
                                                                 {"A", KEY_A},
                                                                 {"S", KEY_S},
                                                                 {"D", KEY_D},
                                                                 {"F", KEY_F},
                                                                 {"G", KEY_G},
                                                                 {"H", KEY_H},
                                                                 {"J", KEY_J},
                                                                 {"K", KEY_K},
                                                                 {"L", KEY_L},
                                                                 {"ENTER", KEY_ENTER},
                                                                 {"SHIFTLEFT", KEY_SHIFTLEFT},
                                                                 {"Z", KEY_Z},
                                                                 {"X", KEY_X},
                                                                 {"C", KEY_C},
                                                                 {"V", KEY_V},
                                                                 {"B", KEY_B},
                                                                 {"N", KEY_N},
                                                                 {"M", KEY_M},
                                                                 {"SHIFTRIGHT", KEY_SHIFTRIGHT},
                                                                 {"ARROWUP", KEY_ARROWUP},
                                                                 {"CTRLLEFT", KEY_CTRLLEFT},
                                                                 {"APPLEFT", KEY_APPLEFT},
                                                                 {"ALT", KEY_ALT},
                                                                 {"SPACE", KEY_SPACE},
                                                                 {"ALTGR", KEY_ALTGR},
                                                                 {"APPRIGHT", KEY_APPRIGHT},
                                                                 {"MENU", KEY_MENU},
                                                                 {"CTRLRIGHT", KEY_CTRLRIGHT},
                                                                 {"ARROWLEFT", KEY_ARROWLEFT},
                                                                 {"ARROWDOWN", KEY_ARROWDOWN},
                                                                 {"ARROWRIGHT", KEY_ARROWRIGHT},
                                                                 {"PAD0", KEY_PAD0},
                                                                 {"PAD1", KEY_PAD1},
                                                                 {"PAD2", KEY_PAD2},
                                                                 {"PAD3", KEY_PAD3},
                                                                 {"PAD4", KEY_PAD4},
                                                                 {"PAD5", KEY_PAD5},
                                                                 {"PAD6", KEY_PAD6},
                                                                 {"PAD7", KEY_PAD7},
                                                                 {"PAD8", KEY_PAD8},
                                                                 {"PAD9", KEY_PAD9},
                                                                 {"PADADD", KEY_PADADD},
                                                                 {"PADSUB", KEY_PADSUB},
                                                                 {"PADMUL", KEY_PADMUL},
                                                                 {"PADDIV", KEY_PADDIV}};

/**\brief The MouseButton Enumeration holds all accepted mouse
 *        input buttons.
 *  These button enumerations are represented as bitwise flags.*/
enum MouseButton { // Stored as bitwise flags from CImgDisplay
  MOUSEB_LEFT,     // Left Mouse Button
  MOUSEB_RIGHT,    // Right Mouse Button
  MOUSEB_MIDDLE    // Middle Mouse Button
};

/**
 * \brief The internally-used representation of an Input Event.
 * Contains information pertaining to keyboard and mouse events, as well as
 * callback pointers for either case.
 */
struct InputEvent {
  // True for keyboard, false for mouse
  bool type = false;
  // mouseX, mouseY
  int mX = 0;
  int mY = 0;
  /*void callback pointer. cast and called when processed.*/
  void *cbPointer = nullptr;
};

/**
 * Returns a keyboard key enumeration when given its name as a string.
 * @param name
 * @return
 */
KeyboardKey keyFromName(const std::string &name);

unsigned int toCImgKey(KeyboardKey key);
} // namespace cturtle
#endif
