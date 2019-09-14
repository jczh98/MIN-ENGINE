/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef CHIHAYA_SRC_CORE_HITABLE_LIST_H_
#define CHIHAYA_SRC_CORE_HITABLE_LIST_H_

#include "common.h"
#include "hitable.h"

MIN_NAMESPACE_BEGIN

class HitableList: public Hitable {
 public:
  HitableList(Hitable **l, int n) : list{l}, list_size{n} {}

  virtual bool hit(const Ray &ray, Float t_min, Float t_max, HitRecord &rec) const;

  Hitable **list;
  int list_size;
};
MIN_NAMESPACE_END

#endif //CHIHAYA_SRC_CORE_HITABLE_LIST_H_
