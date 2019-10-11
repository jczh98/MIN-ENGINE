/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#pragma once

#include <min/min.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

MIN_NAMESPACE_BEGIN

namespace gui {

class GUI {
 public:
  GUI();
  ~GUI();
  void Show();
 private:
  void Close();
  void SetUpDockSpace();
  void ViewportWindow();
  void ConsoleWindow();
  void LogWindow();
  void ExplorerWindow();
  void MenuBar();
  void MainLoop();
  void Update();
  GLFWwindow *window_ = nullptr;
};

}

MIN_NAMESPACE_END

