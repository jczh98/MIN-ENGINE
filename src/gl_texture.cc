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
  glGenTextures(1, &id);
  if (data) {
    GLenum internal_format = 0, data_format = 0;
    if (channels == 4) {
      internal_format = GL_RGBA8;
      data_format = GL_RGBA;
    } else if (channels == 3) {
      internal_format = GL_RGB8;
      data_format = GL_RGB;
    } else if (channels == 1) {
      internal_format = GL_RED;
      data_format = GL_RED;
    }
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, data_format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  } else {
    log::Log("Texture failed to load at path {}", path);
  }
  stbi_image_free(data);
}
GLTexture::~GLTexture() {
  glDeleteTextures(1, &id);
}
void GLTexture::SetData(void *data, uint size) {
}
void GLTexture::Bind(uint unit) const {
  glActiveTexture(unit);
  glBindTexture(GL_TEXTURE_2D, id);
}
void GLTexture::Bind(uint slot, GLint id) {
  glActiveTexture(slot);
  glBindTexture(GL_TEXTURE_2D, id);
}

}