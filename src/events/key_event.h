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
