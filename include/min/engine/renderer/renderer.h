/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#pragma once

#include <min/engine/core/core.h>

MIN_ENGINE_NAMESPACE_BEGIN

class Renderer {
 public:
  static void Init();
  static void OnWindowResize(uint width, uint height);
 private:

};


MIN_ENGINE_NAMESPACE_END

