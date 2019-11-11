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
#include "application.h"

namespace min::engine {

std::unique_ptr<Input> Input::instance = std::make_unique<Input>();

bool Input::IsKeyPressedImpl(int keycode) {
  auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
  auto state = glfwGetKey(window, keycode);
  return state==GLFW_PRESS || state==GLFW_REPEAT;
}
bool Input::IsMouseButtonPressedImpl(int button) {
  auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
  auto state = glfwGetMouseButton(window, button);
  return state==GLFW_PRESS;
}
std::pair<float, float> Input::GetMousePositionImpl() {
  auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);

  return {(float) xpos, (float) ypos};
}
float Input::GetMouseXImpl() {
  auto[x, y] = GetMousePositionImpl();
  return x;
}
float Input::GetMouseYImpl() {
  auto[x, y] = GetMousePositionImpl();
  return y;
}

}
