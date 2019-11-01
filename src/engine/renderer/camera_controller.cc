/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#include <min/engine/renderer/camera_controller.h>
#include <min/engine/core/input.h>
#include <min/engine/core/keycodes.h>

namespace min::engine {

CameraController::CameraController(float aspect_ration, bool rotation) : aspect_ration_(aspect_ration),
                                                                         camera(-aspect_ration*zoom_level,
                                                                                aspect_ration*zoom_level,
                                                                                -zoom_level,
                                                                                zoom_level) {
}

void CameraController::OnUpdate(TimeStep ts) {
  if (Input::IsKeyPressed(MIN_KEY_A)) {
    camera_position_.x() -= std::cos(math::radians(camera_rotation_)) * camera_translation_speed_ * ts;
    camera_position_.y() -= std::sin(math::radians(camera_rotation_)) * camera_translation_speed_ * ts;
  } else if (Input::IsKeyPressed(MIN_KEY_D)) {
    camera_position_.x() += std::cos(math::radians(camera_rotation_)) * camera_translation_speed_ * ts;
    camera_position_.y() += std::sin(math::radians(camera_rotation_)) * camera_translation_speed_ * ts;
  } else if (Input::IsKeyPressed(MIN_KEY_W)) {
    camera_position_.x() -= std::sin(math::radians(camera_rotation_)) * camera_translation_speed_ * ts;
    camera_position_.y() += std::cos(math::radians(camera_rotation_)) * camera_translation_speed_ * ts;
  } else if (Input::IsKeyPressed(MIN_KEY_S)) {
    camera_position_.x() += std::sin(math::radians(camera_rotation_)) * camera_translation_speed_ * ts;
    camera_position_.y() -= std::cos(math::radians(camera_rotation_)) * camera_translation_speed_ * ts;
  }
  if (rotation_) {
    if (Input::IsKeyPressed(MIN_KEY_Q)) {
      camera_rotation_ += camera_rotation_speed_ * ts;
    }
    if (Input::IsKeyPressed(MIN_KEY_E)) {
      camera_rotation_ -= camera_rotation_speed_ * ts;
    }
    if (camera_rotation_ > 180.0f) camera_rotation_ -= 360.0f;
    else if (camera_rotation_ <= -180.0f) camera_rotation_ += 360.0f;
  }
  camera.SetPosition(camera_position_);
  camera_translation_speed_ = zoom_level;
}

void CameraController::OnEvent(Event& e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<MouseScrolledEvent>(std::bind(&CameraController::OnMouseScrolled, this, std::placeholders::_1));
  dispatcher.Dispatch<WindowResizeEvent>(std::bind(&CameraController::OnWindowResized, this, std::placeholders::_1));
}

bool CameraController::OnMouseScrolled(MouseScrolledEvent &e) {
  zoom_level -= e.offset_y * 0.25f;
  zoom_level = std::max(zoom_level, 0.25f);
  camera.SetProjection(-aspect_ration_ * zoom_level, aspect_ration_ * zoom_level, -zoom_level, zoom_level);
  return false;
}
bool CameraController::OnWindowResized(WindowResizeEvent &e) {
  aspect_ration_ = (float) e.width / (float) e.height;
  camera.SetProjection(-aspect_ration_ * zoom_level, aspect_ration_ * zoom_level, -zoom_level, zoom_level);
  return false;
}

}
