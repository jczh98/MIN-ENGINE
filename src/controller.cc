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
#include "controller.h"

namespace min::engine {

Controller::Controller(float aspect_ration)
    : camera(aspect_ration, {0.0f, 0.0f, 6.0f}) {
}
void Controller::OnUpdate(TimeStep ts) {
  using namespace nf::math;
  if (Input::IsKeyPressed(MIN_KEY_A)) {
    camera.ProcessKeyboard(Direction::LEFT, ts);
  } else if (Input::IsKeyPressed(MIN_KEY_D)) {
    camera.ProcessKeyboard(Direction::RIGHT, ts);
  } else if (Input::IsKeyPressed(MIN_KEY_W)) {
    camera.ProcessKeyboard(Direction::FORWARD, ts);
  } else if (Input::IsKeyPressed(MIN_KEY_S)) {
    camera.ProcessKeyboard(Direction::BACKWARD, ts);
  }
}
void Controller::OnEvent(Event &e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<MouseScrolledEvent>(std::bind(&Controller::OnMouseScrolled, this, std::placeholders::_1));
  dispatcher.Dispatch<WindowResizeEvent>(std::bind(&Controller::OnWindowResized, this, std::placeholders::_1));
  //dispatcher.Dispatch<MouseMovedEvent>(std::bind(&Controller::OnMouseMoved, this, std::placeholders::_1));
}
bool Controller::OnMouseMoved(MouseMovedEvent &e) {
  camera.ProcessMouseMovement(e.mouse_x, e.mouse_y);
  return false;
}
bool Controller::OnMouseScrolled(MouseScrolledEvent &e) {
  camera.ProcessMouseScroll(e.offset_y);
  return false;
}
bool Controller::OnWindowResized(WindowResizeEvent &e) {
  aspect_ration_ = (float) e.width/(float) e.height;
  camera.aspect = aspect_ration_;
  return false;
}


}
