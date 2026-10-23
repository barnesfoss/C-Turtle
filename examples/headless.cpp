// Copyright 2021 Jesse W. Walker
//
// Licensed under the MIT License.
// See LICENSE for details.
// Make special note of these defines prior to usage.
#define CTURTLE_HEADLESS // Define to configure CTurtle for Headless mode.
#include "CTurtle.hpp"

namespace ct = cturtle;

int main(int argc, char **argv) {
  ct::TurtleScreen scr(800, 600, "./test.gif");
  ct::Turtle rt(scr);

  for (int i = 0; i < 4; i++) {
    rt.forward(50);
    rt.right(90);
  }

  scr.bye();
  return 0;
}
