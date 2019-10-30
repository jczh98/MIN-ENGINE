/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#include <min/engine/renderer/opengl/gl_shader.h>

MIN_ENGINE_NAMESPACE_BEGIN


OpenGLShader::OpenGLShader(const std::string &vert_path, const std::string &frag_path) {
  std::string vertex_source = ReadFile(vert_path);
  std::string fragment_source = ReadFile(frag_path);
  std::unordered_map<GLenum, std::string> sources;
  sources[GL_VERTEX_SHADER] = vertex_source;
  sources[GL_FRAGMENT_SHADER] = fragment_source;
  Compile(sources);
  // extract name from filepath
  auto last_slash = vert_path.find_last_of("/\\");
  last_slash = last_slash == std::string::npos ? 0 : last_slash + 1;
  auto last_dot = vert_path.rfind('.');
  auto count = last_dot == std::string::npos ? vert_path.size() - last_slash : last_dot - last_slash;
  name_ = vert_path.substr(last_slash, count);
}
OpenGLShader::OpenGLShader(const std::string &name, const std::string &vert, const std::string &frag) : name_(name) {
  std::unordered_map<GLenum, std::string> sources;
  sources[GL_VERTEX_SHADER] = vert;
  sources[GL_FRAGMENT_SHADER] = frag;
  Compile(sources);
}
OpenGLShader::~OpenGLShader() {
  glDeleteProgram(id_);
}
void OpenGLShader::Bind() {
  glUseProgram(id_);
}
void OpenGLShader::Unbind() {
  glUseProgram(0);
}
void OpenGLShader::UploadUniformInt(const std::string &name, int value) {
  GLint location = glGetUniformLocation(id_, name.c_str());
  glUniform1i(location, value);
}
void OpenGLShader::UploadUniformFloat(const std::string &name, float value) {
  GLint location = glGetUniformLocation(id_, name.c_str());
  glUniform1i(location, value);
}
void OpenGLShader::UploadUniformFloat2(const std::string &name, const Vector2f &value) {
  GLint location = glGetUniformLocation(id_, name.c_str());
  glUniform2f(location, value.x(), value.y());
}
void OpenGLShader::UploadUniformFloat3(const std::string &name, const Vector3f &value) {
  GLint location = glGetUniformLocation(id_, name.c_str());
  glUniform3f(location, value.x(), value.y(), value.z());
}
void OpenGLShader::UploadUniformFloat4(const std::string &name, const Vector4f &value) {
  GLint location = glGetUniformLocation(id_, name.c_str());
  glUniform4f(location, value.x(), value.y(), value.z(), value.w());
}
void OpenGLShader::UploadUniformMat3(const std::string &name, const Matrix3f &matrix) {
  GLint location = glGetUniformLocation(id_, name.c_str());
  glUniformMatrix3fv(location, 1, GL_FALSE, matrix.data());
}
void OpenGLShader::UploadUniformMat4(const std::string &name, const Matrix4f &matrix) {
  GLint location = glGetUniformLocation(id_, name.c_str());
  glUniformMatrix4fv(location ,1, GL_FALSE, matrix.data());
}

std::string OpenGLShader::ReadFile(const std::string &filepath) {
  std::string result;
  std::ifstream in(filepath, std::ios::in | std::ios::binary);
  if (in) {
    in.seekg(0, std::ios::end);
    result.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&result[0], result.size());
    in.close();
  } else {
    MIN_CORE_ERROR("Could not open file '{0}'", filepath);
  }
  return result;
}

void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string> &shader_sources) {
  GLuint program = glCreateProgram();
  if (shader_sources.size() > 2) {
    MIN_CORE_ERROR("We only support 2 shaders");
    return;
  }
  std::array<GLenum, 2> glShaderIDs;
  int glShaderIDIndex = 0;
  for (auto& kv : shader_sources) {
    GLenum type = kv.first;
    const std::string& source = kv.second;
    GLuint shader = glCreateShader(type);
    const GLchar* source_c = source.c_str();
    glShaderSource(shader, 1, &source_c, 0);
    glCompileShader(shader);
    GLint is_compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);
    if (is_compiled == GL_FALSE) {
      GLint max_length = 0;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);
      std::vector<GLchar> info_log(max_length);
      glGetShaderInfoLog(shader, max_length, &max_length, &info_log[0]);
      glDeleteShader(shader);
      MIN_CORE_ERROR("{0}", info_log.data());
      break;
    }
    glAttachShader(program, shader);
    glShaderIDs[glShaderIDIndex++] = shader;
  }
  id_ = program;
  // Link program
  glLinkProgram(program);

  GLint is_linked = 0;
  glGetProgramiv(program, GL_LINK_STATUS, (int*)&is_linked);
  if (is_linked == GL_FALSE) {
    GLint max_length = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &max_length);
    std::vector<GLchar> info_log(max_length);
    glGetProgramInfoLog(program, max_length, &max_length, &info_log[0]);
    glDeleteProgram(program);
    for (auto id : glShaderIDs) {
      glDeleteShader(id);
    }
    MIN_CORE_ERROR("{0}", info_log.data());
    return;
  }
  for (auto id : glShaderIDs) {
    glDetachShader(program, id);
    glDeleteShader(id);
  }
}

MIN_ENGINE_NAMESPACE_END
