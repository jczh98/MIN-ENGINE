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

#include <vector>
#include "gl_shader.h"

namespace min::engine {

GLShader::GLShader(const std::string &vert_path, const std::string &frag_path) {
  std::string vert_source = Process(vert_path);
  std::string frag_source = Process(frag_path);
  if (vert_source.empty() || frag_source.empty()) {
    log::Log("Read file filed.");
    return;
  }
  const GLchar* vertex_source_c = vert_source.c_str();
  const GLchar* fragment_source_c = frag_source.c_str();
  // Compile shaders
  uint vertex, fragment;
  // Vertex shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vertex_source_c, nullptr);
  glCompileShader(vertex);
  if (!CheckCompileErrors(vertex, CompileType::VERTEX)) {
    log::Log("{} Compile error.", vert_path);
    return;
  }
  // Fragment shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fragment_source_c, nullptr);
  glCompileShader(fragment);
  if (!CheckCompileErrors(fragment, CompileType::FRAGMENT)) {
    log::Log("{} Compile error.", frag_path);
    return;
  }
  // Program
  id_ = glCreateProgram();
  glAttachShader(id_, vertex);
  glAttachShader(id_, fragment);
  glLinkProgram(id_);
  if (!CheckCompileErrors(id_, CompileType::PROGRAM)) {
    log::Log("Link error.");
    return;
  }
  // Delete shaders
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

GLShader::~GLShader() {

}

void GLShader::Use() {
  glUseProgram(id_);
}

void GLShader::UploadUniformFloat(const std::string &name, float value) {
  glUniform1f(glGetUniformLocation(id_, name.c_str()), value);
}

void GLShader::UploadUniformFloat2(const std::string &name, const Vector2f &value) {
  glUniform2f(glGetUniformLocation(id_, name.c_str()), value.x(), value.y());
}

void GLShader::UploadUniformFloat3(const std::string &name, const Vector3f &value) {
  glUniform3f(glGetUniformLocation(id_, name.c_str()), value.x(), value.y(), value.z());
}

void GLShader::UploadUniformMat3(const std::string &name, const Matrix3f &mat) {
  glUniformMatrix3fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, mat.data());
}

void GLShader::UploadUniformMat4(const std::string &name, const Matrix4f &mat) {
  glUniformMatrix4fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, mat.data());
}

std::string GLShader::Process(const std::string &path) {
  std::string result;
  std::ifstream in(path, std::ios::in | std::ios::binary);
  if (in) {
    in.seekg(0, std::ios::end);
    result.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&result[0], result.size());
    in.close();
  } else {
    log::Log("Could not open file {}", path);
  }
  return result;
}

int GLShader::CheckCompileErrors(uint shader, CompileType type) {
  GLint success;
  GLint max_length = 0;
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);
  std::vector<GLchar> info_log(max_length);
  switch (type) {
    case CompileType::VERTEX:
    case CompileType::FRAGMENT: {
      glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
      if (!success) {
        glGetShaderInfoLog(shader, max_length, &max_length, &info_log[0]);
        log::Log(info_log.data());
      }
      break;
    }
    case CompileType::PROGRAM: {
      glGetProgramiv(shader, GL_LINK_STATUS, &success);
      if (!success) {
        glGetProgramInfoLog(shader, max_length, &max_length, &info_log[0]);
        log::Log(info_log.data());
      }
      break;
    }
  }
  return success;
}

}