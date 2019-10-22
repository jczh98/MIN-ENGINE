/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#pragma once

#include <min/engine/core/core.h>

MIN_ENGINE_NAMESPACE_BEGIN


class GraphicsContext {
 public:
  virtual void Init() = 0;
  virtual void SwapBuffers() = 0;
};



MIN_ENGINE_NAMESPACE_END
