/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#pragma once

#include "exceptions.h"
#include "render_buffer.h"

MIN_NAMESPACE_BEGIN
namespace gl {

class FrameBuffer {
 public:
  FrameBuffer() {
    glGenFramebuffers(1, &id);
    glGenRenderbuffers(1, &rbo);
    if (!id)
      throw OpenGLException("Failed to create framebuffer");
  }
  ~FrameBuffer() {
    if (id) {
      glDeleteFramebuffers(1, &id);
    }
  }
  void Attach(GLenum attachment, uint texture) noexcept {
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE0, texture, 0);
  }
  void Attach(GLenum attachment, RenderBuffer &rbo) noexcept {
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, rbo.id);
  }

  void Bind() noexcept {
    glBindFramebuffer(GL_FRAMEBUFFER, id);
  }

  void Unbind() noexcept {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }
  bool IsValid() const noexcept {
    return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
  }

  uint id, rbo;
};

}
MIN_NAMESPACE_END
