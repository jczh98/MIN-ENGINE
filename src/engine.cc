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

#include "engine.h"

namespace min::engine {

Engine::Engine() {
  if (!Initialize()) {
    log::Log("Unable to create window engine.\n");
    return;
  }
}

Engine::~Engine() {
  Shutdown();
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
bool Engine::InitializeDisplay() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
  window_ = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "MIN", NULL, NULL);
  if (window_ == nullptr) {
    log::Log("Failed to create GLFW window\n");
    glfwTerminate();
    return false;
  }
  glfwMakeContextCurrent(window_);
  glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    log::Log("Failed to initialize GLAD\n");
    return false;
  }
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
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
  ImGui_ImplGlfw_InitForOpenGL(window_, true);
  ImGui_ImplOpenGL3_Init(glsl_version);
  return true;
}

bool Engine::Initialize() {
  if (!InitializeDisplay()) {
    log::Log("Unable to create window.\n");
    return false;
  }
  input_ = std::make_unique<Input>();
  if (!input_->Initialize(window_)) {
    log::Log("Unable to create input manager.\n");
    return false;
  }
  renderer_ = std::make_unique<Renderer>();
  if (!renderer_->Initialize()) {
    log::Log("Unable to initialize renderer.");
    return false;
  }
  return true;
}
void Engine::Shutdown() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwDestroyWindow(window_);
  glfwTerminate();
}
void Engine::Run() {
  last_frame_time_ = last_frame_time_fps_ = glfwGetTime();
  bool show_demo = false;
  while (!glfwWindowShouldClose(window_)) {
    // Update FPS
    const auto current_time = glfwGetTime();
    delta_time_ = current_time - last_frame_time_;
    last_frame_time_ = current_time;
    next_fps_++;
    if (current_time - last_frame_time_fps_ > 1.0) {
      last_frame_time_fps_ = current_time;
      fps_ = next_fps_;
      next_fps_ = 0;
    }
    // std::cout << "FPS: " << fps_ << std::endl;
    // Setup imgui
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    renderer_->OnGUI();
    // Start Render
    renderer_->Render();
    // ImGui swap data
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window_, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImGuiIO &io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
      GLFWwindow *backup_current_context = glfwGetCurrentContext();
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      glfwMakeContextCurrent(backup_current_context);
    }

    glfwSwapBuffers(window_);
    glfwPollEvents();
    input_->ProcessInput();
  }
}

}