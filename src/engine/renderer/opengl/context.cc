/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#include <min/engine/renderer/opengl/context.h>

MIN_ENGINE_NAMESPACE_BEGIN

OpenGLContext::OpenGLContext(GLFWwindow *window) : window_(window) {
  if (window ==nullptr) {
    MIN_CORE_ERROR("Window handle is null");
  }
}

void OpenGLContext::Init() {
  glfwMakeContextCurrent(window_);
  if (glewInit() != GLEW_OK) {
    MIN_CORE_ERROR("Failed to initialize glew");
    return;
  }
  MIN_CORE_INFO("OpenGL Info:");
  MIN_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
  MIN_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
  MIN_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
}
void OpenGLContext::SwapBuffers() {
  glfwSwapBuffers(window_);
}

MIN_ENGINE_NAMESPACE_END