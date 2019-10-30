/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#pragma once

#include <min/engine/core/core.h>
#include "renderer_api.h"

MIN_ENGINE_NAMESPACE_BEGIN

class Renderer {
 public:
  static void Init();
  static void OnWindowResize(uint width, uint height);
  inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
 private:

};


MIN_ENGINE_NAMESPACE_END

