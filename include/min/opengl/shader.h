/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#pragma once

#include <min/common/util.h>
#include <min/math/math.h>
#include <GL/glew.h>

MIN_NAMESPACE_BEGIN
namespace gl {

class Shader {
 public:
  Shader(std::string vertex_path, std::string frag_path, std::string geo_path = "") {
    std::string vertex_code, frag_code, geo_code;
    std::ifstream v_shader, f_shader, g_shader;
    v_shader.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    f_shader.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    g_shader.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
      v_shader.open(vertex_path);
      f_shader.open(frag_path);
      std::stringstream v_shader_stream, f_shader_stream;
      v_shader_stream << v_shader.rdbuf();
      f_shader_stream << f_shader.rdbuf();
      v_shader.close();
      f_shader.close();
      vertex_code = v_shader_stream.str();
      frag_code = f_shader_stream.str();
      if (!geo_path.empty()) {
        g_shader.open(geo_path);
        std::stringstream g_shader_stream;
        g_shader_stream << g_shader.rdbuf();
        g_shader.close();
        geo_code = g_shader_stream.str();
      }
    } catch (std::ifstream::failure &e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    // compile shaders
    const char *vertex_code_c = vertex_code.c_str();
    const char *fragment_code_c = frag_code.c_str();
    unsigned vertex, fragment;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertex_code_c, NULL);
    glCompileShader(vertex);
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragment_code_c, NULL);
    glCompileShader(fragment);
    unsigned int geometry;
    if (!geo_path.empty()) {
      const char *geo_code_c = geo_code.c_str();
      geometry = glCreateShader(GL_GEOMETRY_SHADER);
      glShaderSource(geometry, 1, &geo_code_c, NULL);
      glCompileShader(geometry);
    }
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    if (!geo_path.empty()) {
      glAttachShader(ID, geometry);
    }
    glLinkProgram(ID);
    // delete shaders
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if (!geo_path.empty()) {
      glDeleteShader(geometry);
    }
  }
  void Use() { glUseProgram(ID); }
  void SetBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
  }
  void SetInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
  }
  void SetFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
  }
  void SetVec3(const std::string &name, const Vector3f &vec) const {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, vec.data());
  }
  void SetMat4(const std::string &name, const Matrix4f &mat) {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, mat.data());
  }
  unsigned int ID;
 private:
};

}
MIN_NAMESPACE_END


