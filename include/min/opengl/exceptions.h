/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#pragma once

#include <min/common/util.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

MIN_NAMESPACE_BEGIN
namespace gl {
class OpenGLException : public std::runtime_error {
 public:
  OpenGLException(const std::string msg) : runtime_error(msg) {}
};
}
MIN_NAMESPACE_END