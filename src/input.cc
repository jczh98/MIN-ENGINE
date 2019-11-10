// MIT License
// 
// Copyright (c) 2018-2019, neverfelly <neverfelly@gmail.com>
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#include "input.h"
#include "engine.h"

#include <utility>

namespace min::engine {

Input::Input() {

}
Input::~Input() {

}
bool Input::Initialize(GLFWwindow* window, std::shared_ptr<Camera> camera) {
  window_ = window;
  if (window_ == nullptr) {
    return false;
  }
  camera_ = std::move(camera);
  return true;
}

void Input::ProcessInput() {
  if (KeyPressedOnce(GLFW_KEY_ESCAPE)) {
    glfwSetWindowShouldClose(window_, true);
  }
}

bool Input::KeyPressed(int key_code) {
  return glfwGetKey(window_, key_code) == GLFW_PRESS;
}

bool Input::KeyPressedOnce(int key_code) {
  bool result = false;
  if (KeyPressed(key_code)) {
    if (!key_pressed_[key_code]) {
      result = true;
    }
    key_pressed_[key_code] = true;
  } else {
    key_pressed_[key_code] = false;
  }
  return result;
}
void Input::MouseCallback(GLFWwindow *window, double xpos, double ypos) {
  static bool first_mouse = true;
  static float last_x = Engine::SCREEN_WIDTH / 2.0f;
  static float last_y = Engine::SCREEN_HEIGHT / 2.0f;
  if (first_mouse) {
    last_x = xpos;
    last_y = ypos;
    first_mouse = false;
  }
  float xoffset = xpos - last_x;
  float yoffset = last_y - ypos; // reversed since y-coordinates go from bottom to top
  last_x = xpos;
  last_y = ypos;
  camera_->ProcessMouseMovement(xoffset, yoffset);
}
void Input::ScrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
  camera_->ProcessMouseScroll(yoffset);
}
}
