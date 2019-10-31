/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#pragma once

#include <min/engine/core/core.h>
#include "renderer.h"

MIN_ENGINE_NAMESPACE_BEGIN

class Shader {
 public:
  virtual ~Shader() = default;
  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;
  virtual const std::string &GetName() const = 0;
  static std::shared_ptr<Shader> Create(const std::string &vert_path,
                                        const std::string &frag_path);
  static std::shared_ptr<Shader> Create(const std::string &name,
                                        const std::string &vertex,
                                        const std::string &frag);
};

class ShaderLibrary {
 public:
  void Add(const std::string &name, const std::shared_ptr<Shader> &shader);
  void Add(const std::shared_ptr<Shader> &shader);
  std::shared_ptr<Shader> Load(const std::string &vert_path, const std::string &frag_path);
  std::shared_ptr<Shader> Load(const std::string &name, const std::string &vert_path, const std::string &frag_path);
  std::shared_ptr<Shader> Get(const std::string &name);
  bool Exists(const std::string &name) const;
 private:
  std::unordered_map<std::string, std::shared_ptr<Shader>> shaders_;
};
MIN_ENGINE_NAMESPACE_END

