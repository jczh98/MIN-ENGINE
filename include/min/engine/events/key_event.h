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

class KeyEvent : public Event {
 public:
  KeyEvent(int keycode) : key_code(keycode) {}
  EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
  int key_code;
};

class KeyPressedEvent : public KeyEvent {
 public:
  KeyPressedEvent(int keycode, int repeat_count) : KeyEvent(keycode), repeat_count(repeat_count) {}
  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyPressedEvent: " << key_code << " (" << repeat_count << " repeats)";
    return ss.str();
  }
  EVENT_CLASS_TYPE(KeyPressed)
  int repeat_count;
};

class KeyReleasedEvent : public KeyEvent {
 public:
  KeyReleasedEvent(int keycode)
      : KeyEvent(keycode) {}

  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyReleasedEvent: " << key_code;
    return ss.str();
  }

  EVENT_CLASS_TYPE(KeyReleased)
};

class KeyTypedEvent : public KeyEvent {
 public:
  KeyTypedEvent(int keycode)
      : KeyEvent(keycode) {}

  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyTypedEvent: " << key_code;
    return ss.str();
  }

  EVENT_CLASS_TYPE(KeyTyped)
};

}
}

