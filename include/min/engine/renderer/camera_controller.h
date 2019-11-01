/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#pragma once

#include <min/engine/core/core.h>
#include <min/engine/events/mouse_event.h>
#include <min/engine/events/application_event.h>
#include <min/engine/core/timestep.h>
#include "camera.h"

namespace min::engine {

class CameraController {
 public:
  CameraController(float aspect_ration, bool rotation = false);
  void OnUpdate(TimeStep ts);
  void OnEvent(Event& e);

  float zoom_level = 1.0f;
  Camera camera;
 private:
  bool OnMouseScrolled(MouseScrolledEvent& e);
  bool OnWindowResized(WindowResizeEvent& e);
  bool rotation_;
  float aspect_ration_;
  Vector3f camera_position_ = {0.0f, 0.0f, 0.0f};
  float camera_rotation_ = 0.0f;
  float camera_translation_speed_ = 5.0f;
  float camera_rotation_speed_ = 180.0f;
};

}

