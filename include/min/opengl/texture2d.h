/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#pragma once

#include <min/math/math.h>
#include "exceptions.h"

MIN_NAMESPACE_BEGIN
namespace gl {

class Texture2D {
 public:
  Texture2D() {
    glGenTextures(1, &id);
    if (!id) {
      throw OpenGLException("Failed to create texture.");
    }
  }
  void InitData(const uchar *data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_RGB, GL_UNSIGNED_BYTE, data);
  }
  void SetParam(GLenum param_name, GLint param_value) {
    glTextureParameteri(GL_TEXTURE_2D, param_name, param_value);
  }
  void Bind() {
    glBindTexture(GL_TEXTURE_2D, id);
  }
  ~Texture2D() {
    if (id) {
      glDeleteTextures(1, &id);
    }
  }
  uint id;
};

}
MIN_NAMESPACE_END
