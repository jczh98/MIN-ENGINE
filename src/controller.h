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
#pragma once

#include "common.h"
#include "time_step.h"
#include "events/mouse_event.h"
#include "events/application_event.h"
#include "input.h"
#include "keycodes.h"
#include "camera.h"
#include "application.h"

namespace min::engine {

class Controller {
 public:
  Controller(float aspect_ration);
  void OnUpdate(TimeStep ts);
  void OnEvent(Event& e);

  Camera camera;
 private:
  void UpdateVectors();
  bool OnMouseScrolled(MouseScrolledEvent& e);
  bool OnMouseMoved(MouseMovedEvent& e);
  bool OnWindowResized(WindowResizeEvent& e);
  float aspect_ration_;
  Vector3f camera_position_ = {0.0f, 0.0f, 3.0f};
  Vector3f world_up_ = {0.0f, 1.0f, 0.0f};
  Vector3f direction_ = {0.0f, 0.0f, -1.0f};
};

}

