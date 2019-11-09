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
#include "input.h"

namespace min::engine {

class Engine {
 public:
  const static int SCREEN_WIDTH = 800;
  const static int SCREEN_HEIGHT = 600;
  constexpr static float SCREEN_ASPECT_RATIO = SCREEN_WIDTH / (float) SCREEN_HEIGHT;

#ifdef __APPLE__
  const char* glsl_version = "#version 150";
#else
  const char *glsl_version = "#version 130";
#endif

  Engine();
  ~Engine();

  bool Initialize();
  void Shutdown();
  void Run();
 private:
  bool InitializeDisplay();
  GLFWwindow* window_;
  std::unique_ptr<Input> input_;
  double last_frame_time_fps_ = 0.0;
  double last_frame_time_ = 0.0;
  double delta_time_ = 0.0;
  int fps_ = 0;
  int next_fps_ = 0;
};

}