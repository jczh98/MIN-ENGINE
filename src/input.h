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

namespace min::engine {

class Input {
 public:
  Input(const Input&) = default;
  Input&operator=(const Input&) = default;
  inline static bool IsKeyPressed(int keycode) { return instance->IsKeyPressedImpl(keycode); }
  inline static bool IsMouseButtonPressed(int button) { return instance->IsMouseButtonPressedImpl(button); }
  inline static std::pair<float, float> GetMousePosition() { return instance->GetMousePositionImpl(); }
  inline static float GetMouseX() { return instance->GetMouseXImpl(); }
  inline static float GetMouseY() { return instance->GetMouseYImpl(); }
 private:
  virtual bool IsKeyPressedImpl(int keycode);
  virtual bool IsMouseButtonPressedImpl(int button);
  virtual std::pair<float, float> GetMousePositionImpl();
  virtual float GetMouseXImpl();
  virtual float GetMouseYImpl();
  static std::unique_ptr<Input> instance;
};
}
