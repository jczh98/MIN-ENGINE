/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#include <min/core/object.h>

MIN_NAMESPACE_BEGIN

void MinObject::AddChild(MinObject *) {
  throw std::runtime_error(fmt::format(
      "MinObject::addChild() is not implemented for objects of type '%s'!",
      ClassType(GetClassType())));
}

void MinObject::Activate() { /* Do nothing */ }
void MinObject::SetParent(MinObject *) { /* Do nothing */ }

std::map<std::string, MinObjectFactory::Constructor> *MinObjectFactory::constructors_ = nullptr;

void MinObjectFactory::RegisterClass(const std::string &name, const Constructor &constr) {
  if (!constructors_)
    constructors_ = new std::map<std::string, MinObjectFactory::Constructor>();
  (*constructors_)[name] = constr;
}

MIN_NAMESPACE_END

