/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#include "stb_image.h"
#include <min/engine/renderer/opengl/gl_texture.h>
#include <gsl/gsl_assert>

namespace min::engine {

OpenGLTexture2D::OpenGLTexture2D(const std::string &path) : path_(path) {
  int width, height, channels;
  stbi_set_flip_vertically_on_load(1);
  stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

  width_ = width;
  height_ = height;
  GLenum internal_format = 0, data_format = 0;
  if (channels == 4) {
    internal_format = GL_RGBA8;
    data_format = GL_RGBA;
  } else if (channels == 3) {
    internal_format = GL_RGB8;
    data_format = GL_RGB;
  }
  glCreateTextures(GL_TEXTURE_2D, 1, &id_);
  glTextureStorage2D(id_, 1, internal_format, width_, height_);
  glTextureParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(id_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTextureSubImage2D(id_, 0, 0, 0, width_, height_, data_format, GL_UNSIGNED_BYTE, data);
  stbi_image_free(data);
}
OpenGLTexture2D::~OpenGLTexture2D() {
  glDeleteTextures(1, &id_);
}
void OpenGLTexture2D::Bind(uint slot) const {
  glBindTextureUnit(slot, id_);
}

}
