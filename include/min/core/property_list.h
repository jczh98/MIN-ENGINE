/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef MIN_INCLUDE_MIN_CORE_PROPERTY_LIST_H_
#define MIN_INCLUDE_MIN_CORE_PROPERTY_LIST_H_

#include <min/min.h>
#include <map>

MIN_NAMESPACE_BEGIN

class PropertyList {
 public:
  void SetBoolean(const std::string &name, const bool &value);

  bool GetBoolean(const std::string &name, const bool &default_value);
 private:
  struct Property {
    enum {
      boolean_type
    } type;

    struct Value {
      bool boolean_value;
    } value;
  };

  std::map<std::string, Property> properties_;
};

MIN_NAMESPACE_END

#endif //MIN_INCLUDE_MIN_CORE_PROPERTY_LIST_H_
