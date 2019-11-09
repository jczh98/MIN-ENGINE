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

#include "display.h"

namespace min::engine {

Display::Display() {

}
Display::~Display() {

}
bool Display::Initialize() {
  if (!InitializeGLFW()) {
    return false;
  }
  if (!CreateWindow()) {
    return false;
  }
  if (!CreateImGuiContext()) {
    return false;
  }
  return true;
}
void Display::Shutdown() {
  ImGui::EndFrame();
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwDestroyWindow(window_.get());
  glfwTerminate();
}
void Display::Bind() {

}
void Display::SwapBuffer() {

}
bool Display::InitializeGLFW() {
  if (glfwInit() == GLFW_TRUE) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
    return true;
  } else {
    log::Log("Unable to intialize GLFW.");
    return false;
  }
}

bool Display::InitializeGL() {
  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    log::Log("Failed to initialize GLAD");
    return false;
  }
  return true;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

bool Display::CreateWindow() {
  window_ = std::make_unique<GLFWwindow>(glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "MIN", NULL, NULL));
  if (window_ == nullptr) {
    log::Log("Failed to create GLFW window");
    glfwTerminate();
    return false;
  }
  glfwMakeContextCurrent(window_.get());
  glfwSetFramebufferSizeCallback(window_.get(), framebuffer_size_callback);
  return true;
}

bool Display::CreateGLContext() {
  return false;
}

bool Display::CreateImGuiContext() {
  IMGUI_CHECKVERSION();
  ImGuiContext *imgui_context = ImGui::CreateContext();
  if (imgui_context == nullptr) {
    log::Log("Could not load IMGUI context!");
    return false;
  }
  ImGuiIO &io = ImGui::GetIO();
  (void) io;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
  ImGui::StyleColorsDark();
  ImGuiStyle &style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }
  ImGui_ImplGlfw_InitForOpenGL(window_.get(), true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  // ImGui first frame setup
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  return true;
}

}