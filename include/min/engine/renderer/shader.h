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
  static std::shared_ptr<Shader> Create(const std::string &filepath);
  static std::shared_ptr<Shader> Create(const std::string &name,
                                        const std::string &vertex,
                                        const std::string &frag);
};

MIN_ENGINE_NAMESPACE_END

