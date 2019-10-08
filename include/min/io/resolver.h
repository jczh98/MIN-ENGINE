/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef MIN_INCLUDE_MIN_SYSTEM_RESOLVER_H_
#define MIN_INCLUDE_MIN_SYSTEM_RESOLVER_H_

#include <min/min.h>

MIN_NAMESPACE_BEGIN

class Resolver {
 public:
  Resolver() {
    paths_.emplace_back(fs::current_path());
  }

  size_t size() const { return paths_.size(); }
  auto begin() { return paths_.begin(); }
  auto end() { return paths_.end(); }

  auto begin() const { return paths_.begin(); }
  auto end() const { return paths_.end(); }

  void Erase(std::vector<fs::path>::iterator it) { paths_.erase(it); }
  void Prepend(const fs::path &path) { paths_.insert(paths_.begin(), path); }
  void Append(const fs::path &path) { paths_.emplace_back(path); }

  const fs::path &operator[](size_t index) const { return paths_[index]; }
  fs::path &operator[](size_t index) { return paths_[index]; }

  fs::path resolve(const fs::path &value) const {
    for (const auto & it : paths_) {
      fs::path combined = it / value;
      if (fs::exists(combined)) {
        return combined;
      }
    }
    return value;
  }

  friend std::ostream &operator<<(std::ostream &os, const Resolver &r) {
    os << "Resolver[" << std::endl;
    for (size_t i = 0; i < r.paths_.size(); i++) {
      os << " \"" << r.paths_[i] << "\"";
      if (i + 1 < r.paths_.size()) os << ",";
      os << std::endl;
    }
    os << "]";
    return os;
  }
 private:
  std::vector<fs::path> paths_;
};

std::shared_ptr<Resolver> GetFileResolver() {
  static std::shared_ptr<Resolver> resolver = std::make_shared<Resolver>(Resolver());
  return resolver;
}

MIN_NAMESPACE_END

#endif //MIN_INCLUDE_MIN_SYSTEM_RESOLVER_H_
