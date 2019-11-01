/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#include <min/engine/core/application.h>
#include "gui.h"
#include "sandbox2d.h"

using namespace min::gui;

class Sandbox : public min::engine::Application {
 public:
  Sandbox() {
    PushLayer(new Sandbox2D());
  }
};

int main(int argc, char **argv) {
  auto app = new Sandbox();
  app->Run();
  delete app;
  //try {
  //  std::unique_ptr<GUI> gui = std::make_unique<GUI>(GUI());
  //  gui->Show();
  //} catch (std::exception &e) {
  //  std::cerr << e.what() << std::endl;
  //}
  return 0;
}
