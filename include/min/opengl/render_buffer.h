/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#pragma once

#include "exceptions.h"

MIN_NAMESPACE_BEGIN

namespace gl {

class RenderBuffer {
 public:
  RenderBuffer() {
    glGenRenderBuffers(1, &id);
    if (!id) {
      throw OpenGLException("Failed to create texture2d");
    }
  }
  ~RenderBuffer() {
    if (id) {
      glDeleteRenderbuffers(1, &id);
    }
  }
  void Bind() noexcept {
    glBindRenderbuffer(GL_RENDERBUFFER, id);
  }
  void SetFormat(GLenum format, int width, int height) {
    glRenderbufferStorage(GL_RENDERBUFFER, format, width, height);
  }

  uint id;
};

}
MIN_NAMESPACE_END
