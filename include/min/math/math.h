/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#pragma once

#include <min/common/util.h>
#include "linalg.h"

MIN_NAMESPACE_BEGIN

namespace math {

extern Float radians(Float deg);

extern Matrix4 Perspective(Float fovy, Float aspect, Float z_near, Float z_far);

extern Matrix4 LookAt(const Vector3 &eye, const Vector3 &center, const Vector3 &up);

extern Matrix4 Ortho(const Float left, const Float right, const Float bottom, const Float top, const Float zNear, const Float zFar);

}

MIN_NAMESPACE_END

