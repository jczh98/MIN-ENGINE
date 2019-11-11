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
#include "gl_context.h"
#include "events/event.h"

namespace min::engine {

struct WindowProps {
  std::string title;
  unsigned int width;
  unsigned int height;

  WindowProps(const std::string &title = "Min Engine",
              unsigned int width = 1280,
              unsigned int height = 720)
      : title(title), width(width), height(height) {
  }
};

// Interface representing a desktop system based Window
class Window {
 public:
  using EventCallbackFn = std::function<void(Event & )>;

  Window(const WindowProps &props);
  virtual ~Window();

  virtual void OnUpdate();

  virtual unsigned int GetWidth() const { return data_.width; }
  virtual unsigned int GetHeight() const { return data_.height; }

  // Window attributes
  virtual void SetEventCallback(const EventCallbackFn &callback) { data_.event_callback_fn = callback; }
  virtual void SetVSync(bool enabled);
  virtual bool IsVSync() const;

  virtual void *GetNativeWindow() const { return window_; }

  static std::unique_ptr<Window> Create(const WindowProps &props = WindowProps());
 private:
  virtual void Init(const WindowProps &props);
  virtual void Shutdown();
  GLFWwindow *window_;
  std::unique_ptr<GLContext> context_;
  struct WindowData {
    std::string title;
    uint width, height;
    bool vsync;
    EventCallbackFn event_callback_fn;
  };
  WindowData data_;
};

}