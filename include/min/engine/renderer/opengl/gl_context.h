/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../graphics_context.h"

MIN_ENGINE_NAMESPACE_BEGIN

class OpenGLContext : public GraphicsContext {
 public:
  OpenGLContext(GLFWwindow* window);
  virtual void Init() override ;
  virtual void SwapBuffers() override ;
 private:
  GLFWwindow* window_;
};


MIN_ENGINE_NAMESPACE_END

