/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#include "gui.h"

using namespace min::gui;

int main(int argc, char **argv) {
  try {
    std::unique_ptr<GUI> gui = std::make_unique<GUI>(GUI());
    gui->Show();
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
