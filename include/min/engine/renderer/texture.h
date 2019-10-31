/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#pragma once

#include <min/engine/core/core.h>

namespace min::engine {

class Texture {
 public:
  virtual ~Texture() = default;
  virtual uint GetWidth() const = 0;
  virtual uint GetHeight() const = 0;
  virtual void Bind(uint slot = 0) const = 0;
};

class Texture2D : public Texture {
 public:
  static std::shared_ptr<Texture2D> Create(const std::string& path);
};


}
