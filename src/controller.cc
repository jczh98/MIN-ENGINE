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

Controller::Controller(float aspect_ration, float yaw, float pitch)
    : camera(45.0f, aspect_ration, 0.1f, 100.0f) {
  UpdateVectors();
}
void Controller::OnUpdate(TimeStep ts) {
  using namespace nf::math;
  if (Input::IsKeyPressed(MIN_KEY_A)) {
    camera_position_ -= right_ * movement_speed_ * ts;
  } else if (Input::IsKeyPressed(MIN_KEY_D)) {
    camera_position_ += right_ * movement_speed_ * ts;
  } else if (Input::IsKeyPressed(MIN_KEY_W)) {
    camera_position_ += direction_ * movement_speed_ * ts;
  } else if (Input::IsKeyPressed(MIN_KEY_S)) {
    camera_position_ -= direction_ * movement_speed_ * ts;
  }
  if (rotation_) {
    if (Input::IsKeyPressed(MIN_KEY_Q)) {
      camera_rotation_ += camera_rotation_speed_*ts;
    }
    if (Input::IsKeyPressed(MIN_KEY_E)) {
      camera_rotation_ -= camera_rotation_speed_*ts;
    }
    if (camera_rotation_ > 180.0f) camera_rotation_ -= 360.0f;
    else if (camera_rotation_ <= -180.0f) camera_rotation_ += 360.0f;
  }
  camera.SetPosition(camera_position_);
  camera.SetVectorUp(vector_up_);
  camera.SetDirection(direction_);
}
void Controller::OnEvent(Event &e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<MouseScrolledEvent>(std::bind(&Controller::OnMouseScrolled, this, std::placeholders::_1));
  dispatcher.Dispatch<WindowResizeEvent>(std::bind(&Controller::OnWindowResized, this, std::placeholders::_1));
}
bool Controller::OnMouseScrolled(MouseScrolledEvent &e) {
  //zoom_level -= e.offset_y*0.25f;
  //zoom_level = std::max(zoom_level, 0.25f);
  //camera.SetProjection(-aspect_ration_ * zoom_level, aspect_ration_ * zoom_level, -zoom_level, zoom_level);
  return false;
}
bool Controller::OnWindowResized(WindowResizeEvent &e) {
  //aspect_ration_ = (float) e.width/(float) e.height;
  //camera.SetProjection(-aspect_ration_ * zoom_level, aspect_ration_ * zoom_level, -zoom_level, zoom_level);
  return false;
}

void Controller::UpdateVectors() {
  using namespace nf::math;
  Vector3f front;
  front.x() = std::cos(radians(yaw_)) * std::cos(radians(pitch_));
  front.y() = std::sin(radians(pitch_));
  front.z() = std::sin(radians(yaw_)) * std::cos(radians(pitch_));
  direction_ = front.normalized();
  right_ = direction_.cross(world_up_).normalized();
  vector_up_ = right_.cross(direction_).normalized();
  camera.SetPosition(camera_position_);
  camera.SetVectorUp(vector_up_);
  camera.SetDirection(direction_);
}

}
