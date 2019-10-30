/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#pragma once

#include <min/engine/core/core.h>
#include <min/engine/renderer/shader.h>
#include <GL/glew.h>

MIN_ENGINE_NAMESPACE_BEGIN


class OpenGLShader : public Shader {
 public:
  OpenGLShader(const std::string& vert_path, const std::string& frag_path);
  OpenGLShader(const std::string& name, const std::string& vert, const std::string& frag);
  virtual ~OpenGLShader();

  virtual void Bind();
  virtual void Unbind();

  void UploadUniformInt(const std::string& name, int value);

  void UploadUniformFloat(const std::string& name, float value);
  void UploadUniformFloat2(const std::string& name, const Vector2f& value);
  void UploadUniformFloat3(const std::string& name, const Vector3f& value);
  void UploadUniformFloat4(const std::string& name, const Vector4f& value);

  void UploadUniformMat3(const std::string& name, const Matrix3f& matrix);
  void UploadUniformMat4(const std::string& name, const Matrix4f& matrix);
 private:
  std::string ReadFile(const std::string& filepath);
  void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
  uint id_;
  std::string name_;
};

MIN_ENGINE_NAMESPACE_END

