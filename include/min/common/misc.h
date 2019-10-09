/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef MIN_INCLUDE_MIN_COMMON_MISC_H_
#define MIN_INCLUDE_MIN_COMMON_MISC_H_

#include "util.h"

MIN_NAMESPACE_BEGIN

extern std::vector<std::string> tokenize(const std::string &string,
                                         const std::string &delim = ", ",
                                         bool include_empty = false) {
  std::string::size_type last_pos = 0, pos = string.find_first_of(delim, last_pos);
  std::vector<std::string> tokens;

  while (last_pos!=std::string::npos) {
    if (pos!=last_pos || include_empty) {
      tokens.emplace_back(string.substr(last_pos, pos - last_pos));
    }
    last_pos = pos;
    if (last_pos!=std::string::npos) {
      last_pos += 1;
      pos = string.find_first_of(delim, last_pos);
    }
  }

  return tokens;
}

extern Float ToFloat(const std::string &str) {
  char *end_ptr = nullptr;
  auto result = (Float) strtof(str.c_str(), &end_ptr);
  if (*end_ptr != '\0')
    throw std::runtime_error(fmt::format("Could not parse floating point value \"%s\"", str));
  return result;
}

extern Eigen::Vector3f ToVector3f(const std::string &str) {
  std::vector<std::string> tokens = min::tokenize(str);
  if (tokens.size() != 3) {
    throw std::runtime_error("Excepted 3 values");
  }
  Eigen::Vector3f result;
  for (int i = 0; i < 3; i++) {
    result[i] = ToFloat(tokens[i]);
  }
  return result;
}

MIN_NAMESPACE_END

#endif //MIN_INCLUDE_MIN_COMMON_MISC_H_
