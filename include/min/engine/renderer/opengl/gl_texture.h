/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#pragma once

#include <GL/glew.h>
#include "../texture.h"

namespace min::engine {

class OpenGLTexture2D : public Texture2D {
 public:
  OpenGLTexture2D(const std::string& path);
  virtual ~OpenGLTexture2D();
  virtual uint GetWidth() const override { return width_; }
  virtual uint GetHeight() const override { return height_; }
  virtual void Bind(uint slot = 0) const override ;
 private:
  std::string path_;
  uint width_, height_;
  uint id_;
};


}

