/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#include "hitable_list.h"

CHIHAYA_NAMESPACE_BEGIN

bool HitableList::hit(const chihaya::Ray &ray,
                      chihaya::Float t_min,
                      chihaya::Float t_max,
                      chihaya::HitRecord &rec) const {
  HitRecord temp_rec;
  bool hit = false;
  Float closest = t_max;
  for (int i = 0; i < list_size; ++i) {
    if (list[i]->hit(ray, t_min, closest, temp_rec)) {
      hit = true;
      closest = temp_rec.t;
      rec = temp_rec;
    }
  }
  return hit;
}
CHIHAYA_NAMESPACE_END
