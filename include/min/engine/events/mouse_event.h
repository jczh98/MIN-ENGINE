/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#pragma once

#include <min/common/util.h>
#include "event.h"

namespace min {
namespace engine {

class MouseMoveEvent : public Event {
 public:
  MouseMoveEvent(float x, float y) : mouse_x(x), mouse_y(y) {}
  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseMovedEvent: " << mouse_x << ", " << mouse_y;
    return ss.str();
  }
  EVENT_CLASS_TYPE(MouseMoved)
  EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
  float32 mouse_x, mouse_y;
};
class MouseScrolledEvent : public Event {
 public:
  MouseScrolledEvent(float x, float y) : offset_x(x), offset_y(y) {}
  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseScrolledEvent: " << offset_x << ", " << offset_y;
    return ss.str();
  }

  EVENT_CLASS_TYPE(MouseScrolled)
  EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
  float offset_x, offset_y;
};

class MouseButtonEvent : public Event {
 public:
  MouseButtonEvent(int button) : button(button) {}
  EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
  int button;
};

class MouseButtonPressedEvent : public MouseButtonEvent {
 public:
  MouseButtonPressedEvent(int button)
      : MouseButtonEvent(button) {}

  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseButtonPressedEvent: " << button;
    return ss.str();
  }

  EVENT_CLASS_TYPE(MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
 public:
  MouseButtonReleasedEvent(int button)
      : MouseButtonEvent(button) {}

  std::string ToString() const override {
    std::stringstream ss;
    ss << "MouseButtonReleasedEvent: " << button;
    return ss.str();
  }

  EVENT_CLASS_TYPE(MouseButtonReleased)
};

}
}
