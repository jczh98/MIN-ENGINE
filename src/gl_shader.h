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

#pragma once

#include "common.h"

namespace min::engine {

enum CompileType {
  PROGRAM = 0, VERTEX, FRAGMENT
};

class GLShader {
 public:
  GLShader(const std::string &vert_path, const std::string &frag_path);
  virtual ~GLShader();
  virtual void Use();
  void UploadUniformInt(const std::string &name, int value);
  void UploadUniformFloat(const std::string &name, float value);
  void UploadUniformFloat2(const std::string &name, const Vector2f &value);
  void UploadUniformFloat3(const std::string &name, const Vector3f &value);
  void UploadUniformMat3(const std::string &name, const Matrix3f &mat);
  void UploadUniformMat4(const std::string &name, const Matrix4f &mat);
 private:
  std::string Process(const std::string &path);
  int CheckCompileErrors(uint shader, CompileType type);
  uint id_;
};

}