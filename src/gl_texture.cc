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

#include "gl_texture.h"
#include "stb_image.h"

namespace min::engine {

GLTexture::GLTexture(const std::string &path) : path_(path){
  int width, height, channels;
  stbi_set_flip_vertically_on_load(1);
  stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

  this->width = width;
  this->height = height;
  GLenum internal_format = 0, data_format = 0;
  if (channels == 4) {
    internal_format = GL_RGBA8;
    data_format = GL_RGBA;
  } else if (channels == 3) {
    internal_format = GL_RGB8;
    data_format = GL_RGB;
  }
  glCreateTextures(GL_TEXTURE_2D, 1, &id_);
  glTextureStorage2D(id_, 1, internal_format, width, height);
  glTextureParameteri(id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(id_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTextureSubImage2D(id_, 0, 0, 0, width, height, data_format, GL_UNSIGNED_BYTE, data);
  stbi_image_free(data);
}
GLTexture::~GLTexture() {
  glDeleteTextures(1, &id_);
}
void GLTexture::SetData(void *data, uint size) {
  uint32_t bpp = data_format_ == GL_RGBA ? 4 : 3;
  if (width * height * bpp != size) {
    log::Log("Data must be entire texture!");
    return;
  }
  glTextureSubImage2D(id_, 0, 0, 0, width, height, data_format_, GL_UNSIGNED_BYTE, data);
}
void GLTexture::Bind(uint slot) const {
  glBindTextureUnit(slot, id_);
}

}